#include "pch.h"
#include "VulkanSystem.h"
#include <stdlib.h>

namespace elm{namespace sys{

#ifdef _DEBUG
	std::shared_ptr<log::Log<VulkanSystem>> VulkanSystem::s_pLogger{ elm::log::Log<VulkanSystem>::Get() };
#endif

	VulkanSystem::VulkanSystem(SDL_Window* pWindow):
		m_pInstance{nullptr},
		m_pWindow{pWindow},
		m_Surface(nullptr),
		m_PhysicalDevice{nullptr}
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
		InitPhysicalDevice();
		CreateLogicalDevice();
	}

	void VulkanSystem::Update(float deltaTime)
	{
		
	}

	void VulkanSystem::CreateInstance()
	{
#ifdef _DEBUG
		m_Layers.push_back("VK_LAYER_LUNARG_standard_validation");
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

		createInfo.enabledLayerCount = (uint32_t)m_Layers.size();
		createInfo.ppEnabledLayerNames = m_Layers.data();

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
			m_Device.destroy();
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
		switch (messageSeverity)
		{
		case vk::DebugUtilsMessageSeverityFlagBitsEXT::eError:
			s_pLogger->Error(pCallbackData->pMessage);
			break;
		case vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo:
			s_pLogger->Info(pCallbackData->pMessage);
			break;
		case vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose:
			s_pLogger->Fatal(pCallbackData->pMessage);
			break;
		case vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning:
			s_pLogger->Warning(pCallbackData->pMessage);
			break;
		}
		// ReSharper disable once CppZeroConstantCanBeReplacedWithNullptr
		return VK_FALSE;
	}

	void VulkanSystem::InitPhysicalDevice() 
	{
		const auto physicalDevices{ m_pInstance->enumeratePhysicalDevices() };
		// Look for suitable device
		for (const auto device : physicalDevices)
		{
			vk::PhysicalDeviceProperties deviceProperties;
			vk::PhysicalDeviceFeatures deviceFeatures;
			device.getProperties(&deviceProperties);
			device.getFeatures(&deviceFeatures);
			//Todo:: determine when device is suitable
			if (deviceProperties.deviceType == vk::PhysicalDeviceType::eDiscreteGpu)
			{
				m_PhysicalDevice = device;
				break;
			}
		}
		if (!m_PhysicalDevice)
		{
			throw std::runtime_error("Could not find a suitable GPU");
		}

		auto queueFamilies{m_PhysicalDevice.getQueueFamilyProperties()};
		std::vector<vk::QueueFamilyProperties>::iterator queueFamily;
		int i{};
		for (auto iterator = queueFamilies.cbegin(); iterator != queueFamilies.cend(); ++iterator)
		{
			if (iterator->queueCount > 0 && iterator->queueFlags & vk::QueueFlagBits::eGraphics)
			{
				break;
			}

			if (iterator == queueFamilies.cend())
			{
				throw std::runtime_error("Could not find a suitable GPU");
			}
			i++;
		}
		vk::DeviceQueueCreateInfo queueCreateInfo{};
		queueCreateInfo.queueFamilyIndex = i;
		queueCreateInfo.queueCount = 1;
		float queuePriority = 1.0f;
		queueCreateInfo.pQueuePriorities = &queuePriority;

		vk::PhysicalDeviceFeatures deviceFeatures{};
		//auto extensions{GetRequiredExtensions()};
		vk::DeviceCreateInfo deviceCreateInfo{};
		deviceCreateInfo.pQueueCreateInfos = &queueCreateInfo;
		deviceCreateInfo.queueCreateInfoCount = 1;
		deviceCreateInfo.pEnabledFeatures = &deviceFeatures;		
		//deviceCreateInfo.enabledExtensionCount = extensions.size();
		//deviceCreateInfo.ppEnabledExtensionNames = extensions.data();

#ifdef _DEBUG
		//deviceCreateInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		//deviceCreateInfo.ppEnabledLayerNames = validationLayers.data();
#endif

		m_Device = m_PhysicalDevice.createDevice(deviceCreateInfo);
	}

	void VulkanSystem::CreateLogicalDevice()
	{
		
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

