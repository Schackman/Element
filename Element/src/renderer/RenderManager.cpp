#include "pch.h"
#include <sstream>
#include "RenderManager.h"
#include "RenderTypes.h"
#include "renderer.h"
#include "opengl/GLRenderer.h"
#ifdef ELM_VULKAN_ENABLED
#include "vulkan/VulkanSystem.h"
#endif

namespace elm {namespace renderer
{
	RenderManager::RenderManager(const WindowContext* context)
		: m_Renderers{nullptr},
		  m_pCurrentRenderer{nullptr},
		  m_pWindowContext{context}
	{
		if (!context)
		{
			m_pCurrentRenderer = m_Renderers[0];
			ELM_WARNING("Can't create RenderManager, no WindowContext provided.");
		}
	}

	RenderManager::~RenderManager()
	{
		Shutdown();
	}

	void RenderManager::Shutdown()
	{
		for (auto& renderer : m_Renderers)
		{
			if (renderer)
			{
				delete renderer;
				renderer = nullptr;
			}
		}
	}

	bool RenderManager::CreateRenderer(const RenderTypes renderType)
	{
		if (renderType == RenderTypes::opengl)
		{
			auto& renderer = m_Renderers[Index(renderType)];
			if (!renderer)
				renderer = new GLRenderer{*m_pWindowContext};
			return true;
		}
		return false;
	}

	void RenderManager::InitRenderer()
	{
		auto& renderer = m_pCurrentRenderer;
		if (!renderer)
		{
			throw std::runtime_error("Renderer is nullptr, use OpenGL for now");
		}
		renderer->Init();
		std::stringstream s{};
		s << "Renderer " + renderer->GetName() << " initialized.";
		ELM_INFO(s.str());
	}

	void RenderManager::Update()
	{
	}

	void RenderManager::CurrentRenderer(RenderTypes renderType)
	{
		m_pCurrentRenderer = m_Renderers[Index(renderType)];
#ifdef _DEBUG
		if (!m_pCurrentRenderer)
		{
			ELM_WARNING("Set Current renderer to nullptr");
		}
#endif}
	}
}}
