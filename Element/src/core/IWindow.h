#pragma once

namespace elm
{
	namespace core{
		class IWindow
		{
		public:
			enum class WindowMode
			{
				WINDOWED, FULLSCREEN, FULLSCREEN_BORDERLESS
			};
		protected:
			IWindow(std::string title, uint32_t width, uint32_t height)
				:
				m_Title{title},
				m_PosX{ 0 },
				m_PosY{ 0 },
				m_Width{width},
				m_Height{height}
			{
			}

			virtual ~IWindow() = default;

			virtual void SetTitle(const std::string& title) = 0;
			virtual void Destroy() = 0;
			virtual void Minimize() = 0;
			virtual void Maximize() = 0;
			virtual void Show() = 0;
			virtual void Hide() = 0;
			virtual void Resize(uint32_t w, uint32_t h) = 0;
			virtual void SetWindowMode(WindowMode mode) = 0;
			virtual bool GetWindowMode() = 0;
			virtual bool IsMaximized() = 0;
			virtual bool IsMinimized() = 0;
			virtual bool IsVisible() = 0;
			virtual void SetOpacity(float opacity) = 0;
			virtual bool IsPointInWindow(uint32_t x, uint32_t y) const = 0;


			std::string m_Title;
			uint32_t m_PosX;
			uint32_t m_PosY;
			uint32_t m_Width;
			uint32_t m_Height;
		};

}}