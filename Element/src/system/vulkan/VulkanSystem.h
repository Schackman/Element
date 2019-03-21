#pragma once
#include "../ISystem.h"

namespace elm
{
	namespace sys
	{
		struct QueueFamilyDevices
		{
			vk::Optional<uint32_t> graphicsFamily;
			vk::Optional<uint32_t> presentFamily;

			bool isComplete()
			{
				return graphicsFamily && presentFamily;
			}
		};
		class VulkanSystem final : public ISystem
		{
		public:
			VulkanSystem(SDL_Window* pWindow);
			virtual ~VulkanSystem();
			virtual void Init() override;
			virtual void Update(float deltaTime) override;
			virtual void ShutDown() override;

			std::vector<vk::PhysicalDeviceProperties> GetPhysicalDeviceProperties() const;
			void LogPhysicalDeviceProperties() const;

			

		private:
			std::unique_ptr<vk::Instance> m_pInstance;
			std::vector<const char*> m_Layers;
			SDL_Window* m_pWindow;
			SDL_vulkanSurface m_Surface;
			vk::DebugUtilsMessengerEXT m_DebugMessengerCallBack;
			vk::PhysicalDevice m_PhysicalDevice;
			vk::Device m_Device;


			void CreateInstance();
			std::vector<const char*> GetRequiredExtensions() const;
			void SetupDebugCallback();
			void InitPhysicalDevice();
			void CreateLogicalDevice();
			
			static PFN_vkDebugUtilsMessengerCallbackEXT DebugCallback(vk::DebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
				vk::DebugUtilsMessageTypeFlagsEXT messageType, const vk::DebugUtilsMessengerCallbackDataEXT* pCallbackData,	void* pUserData);
		};
	}
}
