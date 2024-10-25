#include <cmath>

#include <quixot/renderer/window.h>

using namespace Quixot::Renderer;

DECLARE_LOG_CATEGORY(App)

int main() {
    const Window w("My Super Window", 800, 600);

    constexpr float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };

    constexpr unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

   /* const Mesh mesh(vertices, sizeof(vertices), indices, sizeof(indices));

    const Shader vertexShader("simple.vs", ShaderType::Vertex);
	const Shader fragmentShader("simple.fs", ShaderType::Fragment);
	const ShaderProgram shaderProgram(vertexShader, fragmentShader);
    shaderProgram.use();*/

    w.BeginRenderLoop([&]() {
       /* glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);*/

        //const auto time = static_cast<float>(glfwGetTime());
        //constexpr float duration = 10.0f;
        //const float R = std::fmod(time, duration) / duration;

        /*shaderProgram.setUniform("outColor", glm::vec3(R, 0.3f, 0.1f));

		mesh.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);*/
    });

    return EXIT_SUCCESS;
}