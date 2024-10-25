#pragma once

#include <functional>
#include <vulkan/vulkan.hpp>

class GLFWwindow;

namespace Quixot::Renderer {
    class Window {
    public:
        Window(std::string_view title, int width, int height);
        ~Window();

        void BeginRenderLoop(const std::function<void()>& renderCallback) const;
    private:
        GLFWwindow* m_window = nullptr;

        vk::UniqueDevice* m_device;

        void InitWindow(const char* title, int width, int height);
    };
}