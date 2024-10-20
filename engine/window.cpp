#include "window.h"

DECLARE_LOG_CATEGORY(LogWindow)

Erhion::Engine::Window::Window(std::string_view title, int width, int height) {
    InitWindow(title.data(), width, height);
}

Erhion::Engine::Window::~Window() {
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void Erhion::Engine::Window::InitWindow(const char* title, int width, int height) {
    if (!glfwInit())
        LOG(Critical, LogWindow, "Failed to initialize GLFW");

    m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);

    if (!m_window) {
        LOG(Critical, LogWindow, "Failed to create GLFW window {}");
        glfwTerminate();
    }

    glfwMakeContextCurrent(m_window);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        LOG(Critical, LogWindow, "Failed to initialize GLAD");
    }
}

void Erhion::Engine::Window::BeginRenderLoop(const std::function<void()>& renderCallback) const {
    glfwMakeContextCurrent(m_window);

    while (!glfwWindowShouldClose(m_window)) {
        renderCallback();

        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }

    glfwTerminate();
}
