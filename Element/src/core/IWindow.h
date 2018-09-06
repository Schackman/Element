#pragma once

namespace elm
{
	namespace core{
		class IWindow
		{
		protected:
			enum class WindowMode
			{
				WINDOWED, FULLSCREEN, FULLSCREEN_BORDERLESS
			};

			IWindow() = default;
			virtual ~IWindow() = 0;

			virtual void SetTitle(const std::string& string) = 0;
			virtual void Destroy() = 0;
			virtual void Minimize() = 0;
			virtual void Maximize() = 0;
			virtual void Show() = 0;
			virtual void Hide() = 0;
			virtual void Resize(size_t w, size_t h) = 0;
			virtual void SetWindowMode(WindowMode mode) = 0;
			virtual bool GetWindowMode() = 0;
			virtual bool IsMaximized() = 0;
			virtual bool IsMinimized() = 0;
			virtual bool IsVisible() = 0;
			virtual void SetOpacity(float opacity) = 0;
			virtual bool IsPointInWindow(size_t x, size_t y) const = 0;
			virtual void* GetOSWindowHandle() const = 0;


		private:
			std::string m_Title;
			size_t m_PosX;
			size_t m_Posy;
			size_t m_Width;
			size_t m_Height;
		};

}}