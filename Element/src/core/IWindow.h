#pragma once

namespace elm { namespace core
{
	enum class WindowMode
	{
		WINDOWED, FULLSCREEN, FULLSCREEN_BORDERLESS
	};
	class IWindow
	{
	public:
		explicit IWindow(std::string title, uint32_t width, uint32_t height, WindowMode windowMode = WindowMode::WINDOWED)
			: m_WindowMode{windowMode},
			  m_Title{title},
			  m_PosX{0},
			  m_PosY{0},
			  m_Width{width},
			  m_Height{height}
		{
		}

		virtual void Init() = 0;
		virtual void Destroy() = 0;
		virtual void SetWindowMode(WindowMode mode) = 0;
		virtual void SetTitle(const std::string& title) = 0;

		virtual ~IWindow() = default;
	protected:
		WindowMode m_WindowMode;
		std::string m_Title;
		uint32_t m_PosX;
		uint32_t m_PosY;
		uint32_t m_Width;
		uint32_t m_Height;
	};
}}
