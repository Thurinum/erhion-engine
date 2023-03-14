#include "window.h"

Erhion::Engine::Window::Window(const string& title) {
    InitWindow(title, DEFAULT_WIDTH, DEFAULT_HEIGHT);
}

Erhion::Engine::Window::Window(const string &title, int width, int height) {
    InitWindow(title, width, height);
}

void Erhion::Engine::Window::InitWindow(const string& title, int width, int height) {
    if (!glfwInit())
        Log(CRITICAL, "window", "Failed to initialize GLFW");

    m_window = glfwCreateWindow(DEFAULT_WIDTH, DEFAULT_HEIGHT, "Erhion Engine", nullptr, nullptr);

    if (!m_window) {
        Log(CRITICAL, "window", "Failed to create GLFW window");
        glfwTerminate();
    }

    glfwMakeContextCurrent(m_window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        Log(CRITICAL, "window", "Failed to initialize GLAD");
    }
}

void Erhion::Engine::Window::BeginRenderLoop(const std::function<void()>& renderCallback) {
    glfwMakeContextCurrent(m_window);

    while (!glfwWindowShouldClose(m_window)) {
        renderCallback();

        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }

    glfwTerminate();
}
