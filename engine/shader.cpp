#include "shader.h"
#include "io.h"
#include "logging.h"
#include <cassert>

DECLARE_LOG_CATEGORY(LogShader)

using namespace Erhion::Utils;

Erhion::Engine::Shader::Shader(const std::string& FilePath, ShaderType Type) : type(Type)
{
	const FileReader::ReadStringResult& ReadResult = FileReader::ReadString(FilePath);
	assert(ReadResult.has_value());

	const GLchar* source = ReadResult.value().c_str();

	data = glCreateShader(Type);
	glShaderSource(data, 1, &source, nullptr);
	glCompileShader(data);

	GLint success;
	glGetShaderiv(data, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(data, 512, nullptr, infoLog);
		LOG(Error, LogShader, "Failed to compile shader", infoLog);
		throw std::runtime_error("Shader compilation failed");
	}
}

Erhion::Engine::Shader::~Shader()
{
	glDeleteShader(data);
}

Erhion::Engine::ShaderProgram::ShaderProgram(const Shader & vertexShader, const Shader & fragmentShader)
{
	program = glCreateProgram();

	glAttachShader(program, vertexShader.data);
	glAttachShader(program, fragmentShader.data);
	glLinkProgram(program);

	GLint success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		GLchar infoLog[512];
		glGetProgramInfoLog(program, 512, nullptr, infoLog);
		//LogError("Shader program linking failed: %s", infoLog);
	}
}
