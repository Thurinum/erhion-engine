#pragma once

namespace Quixot::Renderer {
    class Mesh {
    public:
        Mesh(const float* vertices, GLsizeiptr numVertices, const unsigned int* indices, GLsizeiptr numIndices);
        ~Mesh();

        void Bind() const { glBindVertexArray(VAO); }
        static void Unbind() { glBindVertexArray(0); }

    private:
        GLuint VAO = 0;
        GLuint VBO = 0;
        GLuint EBO = 0;
    };
}

