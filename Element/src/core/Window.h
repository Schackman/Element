#pragma once

namespace elm {namespace renderer {
	class RenderContext;
}}

namespace elm { namespace core
{
	enum class ELM_EXPORT WindowMode : unsigned
	{
		undefined = 0, windowed, fullscreen, fullscreen_borderless
	};

	enum class ELM_EXPORT GraphicsAPI : unsigned
	{
		none = 0, opengl, direct3d, vulkan
	};

	struct ELM_EXPORT APIVersion final
	{
		GraphicsAPI api;
		int versionMajor;
		int versionMinor;
	};

	struct ELM_EXPORT WindowAttributes final
	{
		APIVersion api;
		WindowMode mode;
		uint32_t width;
		uint32_t height;
	};

	class ELM_EXPORT Window
	{
	public:
		Window(const APIVersion& api)
			: m_API(api)
		{
		}

		virtual ~Window() = default;

		virtual volatile void Init() = 0;
		virtual void Destroy() = 0;
		virtual void SetTitle(const std::string& title) = 0;
		virtual void* GetNativeHandle() = 0;
		virtual void OnFrameEnd() = 0;
		static Window* Create(const WindowAttributes& attributes, const std::string& title = "Element Engine");
		const APIVersion& GetAPIVersion() const { return m_API; }
		union Handle;
	protected:
		renderer::RenderContext* CreateRenderContext();
	private:
		const APIVersion m_API;
	};
}}


#ifdef ELM_PLATFORM_WINDOWS
#include "platform/windows/WindowsWindow.h"
#endif
