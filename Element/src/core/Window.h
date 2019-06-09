#pragma once

namespace elm { namespace core
{
	enum class ELM_EXPORT WindowMode : unsigned
	{
		undefined = 0, windowed, fullscreen, fullscreen_borderless
	};

	struct WindowAttributes final
	{
		WindowMode mode;
		uint32_t width;
		uint32_t height;
	};

	class ELM_EXPORT Window
	{
	public:
		virtual ~Window() = default;

		virtual void Init() = 0;
		virtual void Destroy() = 0;
		virtual void SetTitle(const std::string& title) = 0;
		virtual void* GetNativeHandle() = 0;
		virtual void OnFrameEnd() = 0;
		static Window* Create(const WindowAttributes& attributes, const std::string& title = "Element Engine");
	};
}}
