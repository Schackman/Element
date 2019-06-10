#pragma once
namespace elm {
	struct WindowContext;
}

namespace elm { namespace renderer
{

	enum class GraphicsAPI : unsigned
	{
		none = 0, opengl, direct3d, vulkan
	};

	class RenderContext
	{
	public:
		/**
		 * \brief 
		 * \tparam R has to have elm::renderer::RenderContext as base, 
		 * \return Pointer to created context
		 */
		template<typename R>
		[[nodiscard]]
		static R* CreateContext(const WindowContext& window);
		explicit RenderContext() = default;
		virtual ~RenderContext() = default;
		virtual void Init() = 0;
		virtual void Destroy() noexcept = 0;
		virtual void SwapBuffers() = 0;
	};

	template <typename R>
	R* RenderContext::CreateContext(const WindowContext& window)
	{
		static_assert(std::is_base_of_v<RenderContext, R>);
		return new R(window);
	}
}}
