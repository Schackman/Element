#pragma once

namespace elm { namespace renderer
{

	enum class GraphicsAPI : unsigned
	{
		none = 0, opengl, direct3d, vulkan
	};

	class RenderContext
	{
	public:
		virtual ~RenderContext() = default;
		explicit RenderContext() = default;
		virtual void Init() = 0;
		virtual void Destroy() noexcept = 0;
		virtual void SwapBuffers() = 0;
	};
}}
