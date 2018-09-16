#pragma once
#include "ISystem.h"

namespace elm
{
	namespace sys
	{
		class VulkanSystem final : public ISystem
		{
		public:
			VulkanSystem(SDL_Window* pWindow);
			virtual ~VulkanSystem();
			virtual void Init() override;
			virtual void ShutDown() override;

			std::vector<vk::PhysicalDeviceProperties> GetPhysicalDeviceProperties() const;
			void LogPhysicalDeviceProperties() const;

			

		private:
			std::unique_ptr<vk::Instance> m_pInstance;
			SDL_Window* m_pWindow;
			SDL_vulkanSurface m_Surface;
			vk::DebugUtilsMessengerEXT m_DebugMessengerCallBack;

			void CreateInstance();
			std::vector<const char*> GetRequiredExtensions() const;
			void SetupDebugCallback();
			
			static 	PFN_vkDebugUtilsMessengerCallbackEXT DebugCallback(vk::DebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
				vk::DebugUtilsMessageTypeFlagsEXT messageType, const vk::DebugUtilsMessengerCallbackDataEXT* pCallbackData,	void* pUserData);
		};
	}
}
