#include "core/logging.h"

#include <iostream>
#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>

DECLARE_LOG_CATEGORY(LogShader)

namespace Quixot::Renderer {
	enum ShaderType {
		Vertex = GL_VERTEX_SHADER,
		Fragment = GL_FRAGMENT_SHADER,
	};

	struct Shader {
		Shader(const std::string& FilePath, ShaderType Type);
		~Shader();

		const ShaderType type;

		bool isValid() const { return m_shader != 0; }

		GLuint get() const { return m_shader; }
	private:
		GLuint m_shader = 0;
	};

	class ShaderProgram {
	public:
		ShaderProgram(const Shader& vertexShader, const Shader& fragmentShader);
		~ShaderProgram();

		void use() const { glUseProgram(m_program); }

		template<typename T>
		void setUniform(const char* name, const T& value) const {
			const GLint location = glGetUniformLocation(m_program, name);
			if (location == -1) {
				LOG(Error, LogShader, "Cannot find uniform {} in shader program {}", name, m_program);
				return;
			}

			setUniformImpl(location, value);
		}

	private:
		static void setUniformImpl(const GLint location, const float value) {
			glUniform1f(location, value);
		}

		static void setUniformImpl(const GLint location, const int value) {
			glUniform1i(location, value);
		}

		static void setUniformImpl(const GLint location, const glm::vec2& value) {
			glUniform2fv(location, 1, glm::value_ptr(value));
		}

		static void setUniformImpl(const GLint location, const glm::vec3& value) {
			glUniform3fv(location, 1, glm::value_ptr(value));
		}

		static void setUniformImpl(const GLint location, const glm::vec4& value) {
			glUniform4fv(location, 1, glm::value_ptr(value));
		}

		GLuint m_program = 0;
	};
}