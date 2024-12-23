#include "shader.h"
#include "io.h"
#include "logging.h"

#include <cassert>
#include <glm/gtc/type_ptr.hpp>

using namespace Quixot::Core;

Quixot::Renderer::Shader::Shader(const std::string& FilePath, ShaderType Type) : type(Type)
{
	const result<string, string>& readResult = FileReader::ReadString(FilePath);
	if (!readResult.has_value()) {
		LOG(Error, LogShader, "Failed to read shader file");
		return;
	} // todo: use std::expected with a factory function

	const GLchar* source = readResult.value().c_str();

	m_shader = glCreateShader(Type);
	glShaderSource(m_shader, 1, &source, nullptr);
	glCompileShader(m_shader);

	GLint success;
	glGetShaderiv(m_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(m_shader, 512, nullptr, infoLog);
		LOG(Error, LogShader, "Failed to compile shader {}", infoLog);
	}
}

Quixot::Renderer::Shader::~Shader()
{
	if (isValid())
		glDeleteShader(m_shader);
}

Quixot::Renderer::ShaderProgram::ShaderProgram(const Shader & vertexShader, const Shader & fragmentShader)
{
	if (vertexShader.type != ShaderType::Vertex || fragmentShader.type != ShaderType::Fragment) {
		LOG(Error, LogShader, "Shader type mismatch");
		return;
	}

	m_program = glCreateProgram();

	glAttachShader(m_program, vertexShader.get());
	glAttachShader(m_program, fragmentShader.get());
	glLinkProgram(m_program);

	GLint success;
	glGetProgramiv(m_program, GL_LINK_STATUS, &success);
	if (!success) {
		GLchar infoLog[512];
		glGetProgramInfoLog(m_program, 512, nullptr, infoLog);
		LOG(Error, LogShader, "Shader program linking failed: {}", infoLog);
	}
}

Quixot::Renderer::ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(m_program);
}