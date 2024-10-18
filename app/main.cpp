#include "window.h"
#include "shader.h"

using namespace Erhion::Engine;

DECLARE_LOG_CATEGORY(App)

int main() {
    Window w("My Super Window");
    
    const float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };

    const unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

	Shader vertexShader("simple.vs", ShaderType::Vertex);
	Shader fragmentShader("simple.fs", ShaderType::Fragment);
	ShaderProgram shaderProgram(vertexShader, fragmentShader);
    shaderProgram.use();

    float PreviousTime = 0.0f;

    w.BeginRenderLoop([&]() {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        float Time = glfwGetTime();
        constexpr float Length = 10.0f;
        float R = std::fmod(Time, Length) / Length;
        
        LOG(Info, App, "{}", R);
        shaderProgram.setUniformVec3("outColor", glm::vec3(R, 0.3f, 0.1f));

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    });

    // do cleanup
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

    return EXIT_SUCCESS;
}