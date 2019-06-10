#pragma once
#include "RenderTypes.h"
#include "../util/macro.h"

namespace elm { namespace renderer
{
	class RenderContext;
	class Renderer;

	class RenderManager final
	{
	public:
		explicit RenderManager(const RenderContext* context);
		~RenderManager();
		void Shutdown();
		bool CreateRenderer(RenderTypes renderType);
		void InitRenderer();
		void Update();
		void CurrentRenderer(RenderTypes renderType);
	private:
		static constexpr size_t s_NrRenderTypes = static_cast<size_t>(RenderTypes::count);
		std::array<Renderer*, s_NrRenderTypes> m_Renderers;
		Renderer* m_pCurrentRenderer;
		RenderManager(const RenderManager&) = delete;
		RenderManager(RenderManager&&) = delete;
		RenderManager operator=(const RenderManager&) = delete;
		RenderManager operator=(RenderManager&&) = delete;
	};
}}
