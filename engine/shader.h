#include <iostream>
#include <glad/glad.h>
#include <glm/ext/vector_float3.hpp>

namespace Erhion::Engine {
	enum ShaderType {
		Vertex = GL_VERTEX_SHADER,
		Fragment = GL_FRAGMENT_SHADER,
	};

	struct Shader {
		Shader(const std::string& FilePath, ShaderType Type);
		~Shader();

		const ShaderType type;

		GLuint get() const { return m_shader; }
	private:
		GLuint m_shader;
	};

	class ShaderProgram {
	public:
		ShaderProgram(const Shader& vertexShader, const Shader& fragmentShader);
		~ShaderProgram();

		void use() const { glUseProgram(m_program); }
		void setUniformVec3(const char* name, const glm::vec3& value) const;

	private:
		GLuint m_program;
	};
}