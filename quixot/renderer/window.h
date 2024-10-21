#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <functional>

#include "core/logging.h"

namespace Quixot::Renderer {
    class Window {
    public:
        Window(std::string_view title, int width, int height);
        ~Window();

        void BeginRenderLoop(const std::function<void()>& renderCallback) const;
    private:
        GLFWwindow* m_window = nullptr;

        void InitWindow(const char* title, int width, int height);
    };
}