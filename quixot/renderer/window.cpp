#include "window.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>
#include <mutex>
#include <magic_enum.hpp>

DECLARE_LOG_CATEGORY(LogWindow)

namespace Quixot::Renderer {
	Quixot::Renderer::Window::Window(std::string_view title, int width, int height, int deviceId) {
		m_deviceIndex = deviceId;
		m_width = width;
		m_height = height;

		if (!glfwInit())
			LOG(Critical, LogWindow, "Failed to initialize GLFW");

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // no OpenGL context

		m_window = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);

		if (!m_window) {
			LOG(Critical, LogWindow, "Failed to create GLFW window {}");
			glfwTerminate();
		}
	}

	Quixot::Renderer::Window::~Window() {
		StopRenderLoop();

		if (m_renderThread.joinable())
			m_renderThread.join();

		glfwDestroyWindow(m_window);
		glfwTerminate();
	}

	void Quixot::Renderer::Window::SetupVulkan(int width, int height)
	{
		CreateAppInstance()
			.and_then([this](auto&& instance) {
				m_instance = std::move(instance);
				return FindFirstCapableDevice();
			})
			.and_then([this](auto&& device) {
				m_device = std::move(device);
				return CreateSurface();
			})
			.and_then([=](auto&& surface) {
				m_surface = std::move(surface);
				return CreateSwapchain(width, height);
			})
			.and_then([=](auto&& swapchain) {
				m_swapchain = std::move(swapchain);
				return;
			})
			.or_else([](auto&& error) {
				LOG(Critical, LogWindow, "Failed to setup Vulkan: {}", error);
			});
	}

	either<vk::UniqueSurfaceKHR, string_view> Window::CreateSurface()
	{
		VkSurfaceKHR tmpSurface;
		VkResult createSurfaceResult = glfwCreateWindowSurface(m_instance.get(), m_window, nullptr, &tmpSurface);

		if (createSurfaceResult != VK_SUCCESS) {
			return unexpected(string(magic_enum::enum_name(createSurfaceResult)));
		}

		return vk::UniqueSurfaceKHR(tmpSurface, m_instance.get());
	}

	either<vk::UniqueSwapchainKHR, string_view> Window::CreateSwapchain(int width, int height)
	{
		vk::SurfaceFormatKHR surfaceFormat = vk::SurfaceFormatKHR(vk::Format::eB8G8R8A8Unorm, vk::ColorSpaceKHR::eSrgbNonlinear);
		vk::SwapchainCreateInfoKHR swapchainCreateInfo({}, *m_surface, 2, surfaceFormat.format, surfaceFormat.colorSpace,
			vk::Extent2D(width, height), 1, vk::ImageUsageFlagBits::eColorAttachment);

		auto [result, swapchain] = m_device->createSwapchainKHRUnique(swapchainCreateInfo);
		if (result != vk::Result::eSuccess)
			return unexpected(magic_enum::enum_name(result));
		
		return swapchain;
	}

	either<vk::UniqueInstance, string_view> Window::CreateAppInstance()
	{
		if (!glfwVulkanSupported())
			return unexpected("Vulkan is not supported.");

		vk::ApplicationInfo appInfo(
			"Quixot",
			EngineVersion,
			"Quixot",
			EngineVersion,
			VK_API_VERSION_1_3
		);
		vk::InstanceCreateInfo createInfo({}, &appInfo);

		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;

		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
		if (glfwExtensions == nullptr)
			return unexpected("Failed to get required instance extensions. Vulkan is likely unsupported.");

		createInfo.enabledExtensionCount = glfwExtensionCount;
		createInfo.ppEnabledExtensionNames = glfwExtensions;

		auto [result, instance] = vk::createInstanceUnique(createInfo);
		if (result != vk::Result::eSuccess)
			return unexpected(magic_enum::enum_name(result));

		return instance;
	}

	either<vk::UniqueDevice, string_view> Quixot::Renderer::Window::FindFirstCapableDevice()
	{
		auto [result, physicalDevices] = m_instance->enumeratePhysicalDevices();
		if (result != vk::Result::eSuccess)
			return unexpected(std::format("Could not enumerate physical devices: {}", magic_enum::enum_name(result)));

		if (physicalDevices.empty()) {
			return unexpected("No physical device was found.");
		}

		uint32_t queueFamilyIndex = -1;

#if WITH_DEBUG
		for (const auto& physicalDevice : physicalDevices) {
			auto properties = physicalDevice.getProperties();
			LOG(Info, LogWindow, "Found device: {}", std::string_view(properties.deviceName));
		}
#endif

		if (m_deviceIndex < 0 || m_deviceIndex > physicalDevices.size())
			return unexpected(std::format("Device index #{} is invalid.", m_deviceIndex));

		vk::PhysicalDevice physicalDevice = physicalDevices[m_deviceIndex];
		string deviceName = physicalDevice.getProperties().deviceName;
		auto queueFamilyProperties = physicalDevice.getQueueFamilyProperties();
		for (size_t i = 0; i < queueFamilyProperties.size(); ++i) {
			if (queueFamilyProperties[i].queueFlags & vk::QueueFlagBits::eGraphics)
			{
				queueFamilyIndex = i;
				break;
			}
		}

		if (queueFamilyIndex == -1) {
			return unexpected(std::format("Physical device '{}' does not support graphics.", "deviceName.c_str()"));
		}

		vk::DeviceQueueCreateInfo queueCreateInfo({}, 0, 1);
		vk::DeviceCreateInfo deviceCreateInfo({}, 1, &queueCreateInfo);

		auto [result, device] = physicalDevice.createDeviceUnique(deviceCreateInfo);
		if (result != vk::Result::eSuccess)
			return unexpected(std::format("Failed to create device: {}", magic_enum::enum_name(result)));

		LOG(Info, LogWindow, "Using physical device '{}'.", deviceName);
		return device;
	}

	void Quixot::Renderer::Window::CleanupVulkan()
	{

	}

	void Quixot::Renderer::Window::BeginRenderLoop(const std::function<void()>& renderCallback) {
		m_renderThread = std::thread([this, renderCallback]() {
			SetupVulkan(m_width, m_height);

			while (!m_isRendering && !glfwWindowShouldClose(m_window)) {
				renderCallback();
				glfwSwapBuffers(m_window);
				glfwPollEvents();
			}

			CleanupVulkan();
		});
	}

	void Quixot::Renderer::Window::StopRenderLoop()
	{
		m_isRendering = false;
	}
}
