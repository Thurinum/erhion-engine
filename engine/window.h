#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <functional>

#include "logging.h"

namespace Erhion::Engine {
    class Window {
    public:
        explicit Window(std::string_view title);
        Window(std::string_view title, int width, int height);
        ~Window();

        const int DEFAULT_WIDTH = 800;
        const int DEFAULT_HEIGHT = 600;

        void BeginRenderLoop(const std::function<void()>& renderCallback);
    private:
        GLFWwindow* m_window;

        void InitWindow(const char* title, int width, int height);
    };
}