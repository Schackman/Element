#pragma once
#include "../renderer.h"
#include "../opengl/GLRenderer.h"

#define ELM_VK_LOG(...)			(elm::log::Logger::WithLogger(__VA_ARGS__, elm::sys::VulkanSystem::GetLogger()))
#define ELM_VK_TRACE(...)		(ELM_VK_LOG(__VA_ARGS__, elm::log::LogLevel::trace))
#define ELM_VK_CRITICAL(...)	(ELM_VK_LOG(__VA_ARGS__, elm::log::LogLevel::critical))
#define ELM_VK_ERROR(...)		(ELM_VK_LOG(__VA_ARGS__, elm::log::LogLevel::err))
#define ELM_VK_WARNING(...)		(ELM_VK_LOG(__VA_ARGS__, elm::log::LogLevel::warn))
#define ELM_VK_DEBUG(...)		(ELM_VK_LOG(__VA_ARGS__, elm::log::LogLevel::debug))
#define ELM_VK_INFO(...)		(ELM_VK_LOG(__VA_ARGS__, elm::log::LogLevel::info))

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
		class VulkanSystem final : public renderer::Renderer
		{
		public:
			static std::shared_ptr<log::Logger> GetLogger();

			VulkanSystem(SDL_Window* pWindow);
			//virtual ~VulkanSystem();
			//virtual void Init() override;
			//virtual void Update(float deltaTime) override;
			//virtual void ShutDown() override;

			std::vector<vk::PhysicalDeviceProperties> GetPhysicalDeviceProperties() const;
			void LogPhysicalDeviceProperties() const;

			

		private:
			static std::shared_ptr<log::Logger> s_Logger;

			std::unique_ptr<vk::Instance> m_pInstance;
			
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
