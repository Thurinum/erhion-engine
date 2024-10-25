#include "window.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>
#include <mutex>
#include <magic_enum.hpp>

DECLARE_LOG_CATEGORY(LogWindow)

namespace Quixot::Renderer {
	Quixot::Renderer::Window::Window(std::string_view title, int width, int height, int deviceId) {
		InitWindow(title.data(), width, height, deviceId);
	}

	Quixot::Renderer::Window::~Window() {
		StopRenderLoop();

		if (m_renderThread.joinable())
			m_renderThread.join();

		glfwDestroyWindow(m_window);
		glfwTerminate();
	}

	void Quixot::Renderer::Window::InitWindow(const char* title, int width, int height, int deviceIndex) {
		m_deviceIndex = deviceIndex;

		if (!glfwInit())
			LOG(Critical, LogWindow, "Failed to initialize GLFW");

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // no OpenGL context

		m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);

		if (!m_window) {
			LOG(Critical, LogWindow, "Failed to create GLFW window {}");
			glfwTerminate();
		}
	}

	void Quixot::Renderer::Window::SetupVulkan()
	{
		CreateAppInstance();

		// find a device to render with
		auto maybeDevice = FindFirstCapableDevice();
		if (!maybeDevice.has_value())
		{
			LOG(Critical, LogWindow, "Failed to configure capable device: {}", maybeDevice.error());
			return;
		}
		m_device = std::move(maybeDevice.value());

		// create a surface to render to
		VkSurfaceKHR tmpSurface;
		VkResult createSurfaceResult = glfwCreateWindowSurface(m_instance.get(), m_window, nullptr, &tmpSurface);
		if (createSurfaceResult != VK_SUCCESS) {
			LOG(Critical, LogWindow, "Failed to create window surface, because {}", magic_enum::enum_name(createSurfaceResult));
			return;
		}
		m_surface = vk::UniqueSurfaceKHR(tmpSurface, m_instance.get());
	}

	void Window::CreateAppInstance()
	{
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
		createInfo.enabledExtensionCount = glfwExtensionCount;
		createInfo.ppEnabledExtensionNames = glfwExtensions;
		m_instance = vk::createInstanceUnique(createInfo);
	}

	result<vk::UniqueDevice, string> Quixot::Renderer::Window::FindFirstCapableDevice()
	{
		std::vector<vk::PhysicalDevice> physicalDevices = m_instance->enumeratePhysicalDevices();
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

		LOG(Info, LogWindow, "Using physical device '{}'.", deviceName);
		return physicalDevice.createDeviceUnique(deviceCreateInfo);
	}

	void Quixot::Renderer::Window::CleanupVulkan()
	{

	}

	void Quixot::Renderer::Window::BeginRenderLoop(const std::function<void()>& renderCallback) {
		m_renderThread = std::thread([this, renderCallback]() {
			SetupVulkan();

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
