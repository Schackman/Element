#include "stdafx.h"
#include "VulkanSystem.h"
namespace elm{namespace sys{

	VulkanSystem::VulkanSystem(SDL_Window* pWindow):
		m_pWindow{pWindow},
		m_pInstance{nullptr}
	{
	}

	VulkanSystem::~VulkanSystem()
	{
		ShutDown();
	}

	void VulkanSystem::Init()
	{
		CreateInstance();
		if (!SDL_Vulkan_CreateSurface(m_pWindow, *m_pInstance, &m_Surface))
		{
			std::cout << "[SDL] " << SDL_GetError() << std::endl;
		}

		SetupDebugCallback();
	}

	void VulkanSystem::CreateInstance()
	{
		std::vector<const char*> layers{};
#ifdef _DEBUG
		layers.push_back("VK_LAYER_LUNARG_standard_validation");
#endif

		vk::ApplicationInfo appInfo = vk::ApplicationInfo()
			.setPApplicationName("Element")
			.setApplicationVersion(1)
			.setPEngineName("SDLV")
			.setEngineVersion(1)
			.setApiVersion(VK_API_VERSION_1_1);

		vk::InstanceCreateInfo createInfo{};
		createInfo.pApplicationInfo = &appInfo;

		auto extensions{ GetRequiredExtensions() };
		createInfo.ppEnabledExtensionNames = extensions.data();
		createInfo.enabledExtensionCount = (uint32_t)extensions.size();

		createInfo.enabledLayerCount = (uint32_t)layers.size();
		createInfo.ppEnabledLayerNames = layers.data();

		try
		{
			m_pInstance = std::make_unique<vk::Instance>(vk::createInstance(createInfo));
		}
		catch (const std::runtime_error& e)
		{
			std::cout << "[VULKAN] " << e.what() << std::endl;
		}

		auto supportedExtensions{ vk::enumerateInstanceExtensionProperties() };
		std::for_each(supportedExtensions.begin(), supportedExtensions.end(), [](auto e)->void
		{
			std::cout << e.extensionName << std::endl;
		});
	}

	void VulkanSystem::ShutDown()
	{
		if (m_pInstance)
		{
			m_pInstance->destroySurfaceKHR(m_Surface);
			auto DestroyMessengerCallback = (PFN_vkDestroyDebugUtilsMessengerEXT)m_pInstance->getProcAddr("vkDestroyDebugUtilsMessengerEXT");
			DestroyMessengerCallback((VkInstance)*m_pInstance, m_DebugMessengerCallBack, nullptr);
			m_pInstance->destroy();
		}
		m_pInstance = nullptr;
	}

	std::vector<const char*> VulkanSystem::GetRequiredExtensions() const
	{
		std::vector<const char*> extensions{};

		uint32_t sdlExtensionCount{};
		if (!SDL_Vulkan_GetInstanceExtensions(m_pWindow, &sdlExtensionCount, nullptr))
		{
			std::cout << "[SDL] " << SDL_GetError() << std::endl;
		}

		const char** pExtensionNames = (const char**)malloc(sizeof(const char*) * sdlExtensionCount);
		if (!SDL_Vulkan_GetInstanceExtensions(m_pWindow, &sdlExtensionCount, pExtensionNames))
		{
			std::cout << "[SDL] " << SDL_GetError() << std::endl;
		}

		for (size_t i{}; i < sdlExtensionCount; ++i)
		{
			extensions.push_back(std::move(pExtensionNames[i]));
		}
		free(pExtensionNames);
		pExtensionNames = nullptr;

	#ifdef _DEBUG
		extensions.push_back("VK_EXT_debug_utils");
		extensions.push_back("VK_EXT_debug_report");
	#endif

		return extensions;
	}

	void VulkanSystem::SetupDebugCallback()
	{
		vk::DebugUtilsMessengerCreateInfoEXT messengerCreateInfo{};
		messengerCreateInfo.setMessageSeverity(
			vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo
			| vk::DebugUtilsMessageSeverityFlagBitsEXT::eError
			| vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose
			| vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning
		);
		messengerCreateInfo.setMessageType(vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation | vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral | vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance);
		messengerCreateInfo.setPfnUserCallback((PFN_vkDebugUtilsMessengerCallbackEXT) DebugCallback);		
		auto CreateDebugUtilsMessengerCallback{ (PFN_vkCreateDebugUtilsMessengerEXT) m_pInstance->getProcAddr("vkCreateDebugUtilsMessengerEXT") };
		CreateDebugUtilsMessengerCallback((VkInstance)*m_pInstance, &(VkDebugUtilsMessengerCreateInfoEXT)messengerCreateInfo, nullptr,(VkDebugUtilsMessengerEXT*)&m_DebugMessengerCallBack);
	}

	PFN_vkDebugUtilsMessengerCallbackEXT VulkanSystem::DebugCallback(vk::DebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		vk::DebugUtilsMessageTypeFlagsEXT messageType, const vk::DebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData)
	{
		std::cerr << "[VULKAN] " << pCallbackData->pMessage << std::endl;
		return VK_FALSE;
	}

	std::vector<vk::PhysicalDeviceProperties> VulkanSystem::GetPhysicalDeviceProperties() const
	{
		const auto physicalDevices{ m_pInstance->enumeratePhysicalDevices() };
		std::vector<vk::PhysicalDeviceProperties> properties{};		
		std::for_each(physicalDevices.cbegin(), physicalDevices.cend(), [&properties](auto d)->void
		{			
			properties.push_back(d.getProperties());
		});
		return properties;
	}

	void VulkanSystem::LogPhysicalDeviceProperties() const
	{
		auto properties{GetPhysicalDeviceProperties()};

		std::cout << "Physical Devices:" << std::endl;
		std::for_each(properties.cbegin(), properties.cend(), [](auto d) -> void
		{
			std::cout << "Device id: " << d.deviceID << "\tName: " << d.deviceName << std::endl;
			std::cout << "API Version: " << d.apiVersion << std::endl;
			std::cout << "Driver Version" << d.driverVersion << std::endl;
		});
	}
}}

