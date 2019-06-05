#include "pch.h"
#include "RenderManager.h"
#include "RenderTypes.h"
#include "error/RenderError.h"

#ifdef ELM_VULKAN_ENABLED
#include "vulkan/VulkanSystem.h"
#endif

namespace elm {namespace renderer
{

	RenderManager::RenderManager()
	{
	}

	RenderManager::~RenderManager()
	{
	}

	void RenderManager::Shutdown()
	{

	}
}}
