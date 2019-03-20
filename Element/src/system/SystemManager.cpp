#include "pch.h"
#include "SystemManager.h"
#include "vulkan/VulkanSystem.h"


void elm::sys::SystemManager::CreateSystem(SystemType systemType)
{
	std::unique_ptr<ISystem> pSys;
	switch (systemType)
	{
	case SystemType::renderer_vk:
		//pSys = std::make_unique<VulkanSystem>();
		break;
	default: ;
	}
}
