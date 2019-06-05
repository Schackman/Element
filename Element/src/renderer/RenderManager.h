#pragma once
#include "RenderTypes.h"
#include "opengl/GLRenderer.h"

namespace elm { namespace renderer
{
	class Renderer;

	class RenderManager final
	{
	public:
		template <RenderTypes T = RenderTypes::none>
		void CreateSystem() {}

		RenderManager();
		~RenderManager();
		void Shutdown();
	private:
		static constexpr size_t s_NrRenderTypes = static_cast<size_t>(RenderTypes::count);
		//std::array<Renderer, > m_Renderers;
		RenderManager(const RenderManager&) = delete;
		RenderManager(RenderManager&&) = delete;
		RenderManager operator=(const RenderManager&) = delete;
		RenderManager operator=(RenderManager&&) = delete;
	};
}}
