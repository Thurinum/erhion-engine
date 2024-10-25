#include "window.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>

DECLARE_LOG_CATEGORY(LogWindow)

Quixot::Renderer::Window::Window(std::string_view title, int width, int height) {
    InitWindow(title.data(), width, height);
}

Quixot::Renderer::Window::~Window() {
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void Quixot::Renderer::Window::InitWindow(const char* title, int width, int height) {
    if (!glfwInit())
        LOG(Critical, LogWindow, "Failed to initialize GLFW");

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // no OpenGL context

    m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);

    if (!m_window) {
        LOG(Critical, LogWindow, "Failed to create GLFW window {}");
        glfwTerminate();
    }

   /* const auto EngineVersion = VK_MAKE_VERSION(QUIXOT_VERSION_MAJOR, QUIXOT_VERSION_MINOR, QUIXOT_VERSION_PATCH);
	vk::ApplicationInfo appInfo(title, EngineVersion, "Quixot", EngineVersion, VK_API_VERSION_1_3);
    vk::InstanceCreateInfo instanceCreateInfo({}, &appInfo);
    vk::UniqueInstance instance = vk::createInstanceUnique(instanceCreateInfo);
    VkSurfaceKHR c_surface;
    glfwCreateWindowSurface(*instance, m_window, nullptr, &c_surface);
    vk::UniqueSurfaceKHR surface(c_surface, *instance);

    auto physicalDevices = instance->enumeratePhysicalDevices();
    vk::PhysicalDevice physicalDevice = physicalDevices[0];

    uint32_t queueFamilyIndex = 0;
    auto properties = physicalDevice.getQueueFamilyProperties();
    for (uint32_t i = 0; i < properties.size(); ++i) {
        if (properties[i].queueFlags & vk::QueueFlagBits::eGraphics) {
            queueFamilyIndex = i;
            break;
        }
    }

    float queuePriority = 1.0f;
    vk::DeviceQueueCreateInfo queueCreateInfo({}, queueFamilyIndex, 1, &queuePriority);
    vk::PhysicalDeviceFeatures deviceFeatures;
    vk::DeviceCreateInfo deviceCreateInfo({}, queueCreateInfo, {}, nullptr, &deviceFeatures);

    auto device = physicalDevice.createDeviceUnique(deviceCreateInfo);
    m_device = &device;

    auto queue = device->getQueue(queueFamilyIndex, 0);

    vk::SurfaceFormatKHR surfaceFormat = physicalDevice.getSurfaceFormatsKHR(*surface).front();
    vk::Extent2D extent(width, height);
    vk::SwapchainCreateInfoKHR swapchainCreateInfo({}, *surface, 2, surfaceFormat.format, surfaceFormat.colorSpace,
        extent, 1, vk::ImageUsageFlagBits::eColorAttachment);

    auto swapchain = device->createSwapchainKHRUnique(swapchainCreateInfo);*/
}

void Quixot::Renderer::Window::BeginRenderLoop(const std::function<void()>& renderCallback) const {
    while (!glfwWindowShouldClose(m_window)) {
        renderCallback();

        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }

    glfwTerminate();
}
