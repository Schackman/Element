#pragma once
#include "../core/Window.h"

namespace elm { namespace renderer
{
	class RenderContext
	{
	public:
		template<core::GraphicsAPI API>
		[[nodiscard]]
		static RenderContext* Create(core::Window::Handle window, const core::APIVersion& apiVersion);
		explicit RenderContext() = default;
		virtual ~RenderContext() = default;
		virtual void Init() = 0;
		virtual void Destroy() noexcept = 0;
		virtual void SwapBuffers() = 0;
	};

	template <>
	inline RenderContext* RenderContext::Create<core::GraphicsAPI::none>(core::Window::Handle, const core::APIVersion&)
	{
		return nullptr;
	}
}}
