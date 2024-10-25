#pragma once

#include <functional>
#include <thread>

#define VULKAN_HPP_NO_EXCEPTIONS
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
		vk::UniqueSwapchainKHR m_swapchain;
		int m_deviceIndex = -1;
		int m_width = 0;
		int m_height = 0;

		void SetupVulkan(int width, int height);
        either<vk::UniqueInstance, string_view> CreateAppInstance();
        either<vk::UniqueDevice, string_view> FindFirstCapableDevice();
        either<vk::UniqueSurfaceKHR, string_view> CreateSurface();
        either<vk::UniqueSwapchainKHR, string_view> CreateSwapchain(int width, int height);
		void CleanupVulkan();
    };
}