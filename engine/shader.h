#include <iostream>
#include <glad/glad.h>

namespace Erhion::Engine {
	enum ShaderType {
		Vertex = GL_VERTEX_SHADER,
		Fragment = GL_FRAGMENT_SHADER,
	};

	struct Shader {
		Shader(const std::string& FilePath, ShaderType Type);
		~Shader();

		const ShaderType type;
		GLuint data;
	};

	class ShaderProgram {
	public:
		ShaderProgram(const Shader& vertexShader, const Shader& fragmentShader);

	private:
		GLuint program;
	};
}