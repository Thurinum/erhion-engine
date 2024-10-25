#pragma once

#include <functional>
#include <thread>

#include <vulkan/vulkan.hpp>

class GLFWwindow;

constexpr uint32_t EngineVersion = VK_MAKE_VERSION(QUIXOT_VERSION_MAJOR, QUIXOT_VERSION_MINOR, QUIXOT_VERSION_PATCH);

namespace Quixot::Renderer {
    class Window {
    public:
        Window(std::string_view title, int width, int height, int deviceId);
        ~Window();

        void BeginRenderLoop(const std::function<void()>& renderCallback);
		void StopRenderLoop();

    private:
        GLFWwindow* m_window = nullptr;
        std::thread m_renderThread;
		std::atomic<bool> m_isRendering = false;

		vk::ApplicationInfo m_appInfo;
        vk::UniqueInstance m_instance;
		vk::UniqueDevice m_device;
		vk::UniqueSurfaceKHR m_surface;
		int m_deviceIndex = -1;

        void InitWindow(const char* title, int width, int height, int deviceIndex);
		void SetupVulkan();
        void CreateAppInstance();
        result<vk::UniqueDevice, string> FindFirstCapableDevice();
		void CleanupVulkan();
    };
}