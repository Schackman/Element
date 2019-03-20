#pragma once
#include "../../IWindow.h"
#include <string>
#include "../Platform.h"

namespace elm
{
	namespace core
	{
		class WindowsWindow final : public IWindow
		{

		public:
			WindowsWindow(const std::string& title, WindowMode windowMode, uint32_t width, uint32_t height);
			virtual ~WindowsWindow();

		private:
			SDL_Window* m_pWindow;

		/***********************/
		/* Interface overrides */
		/***********************/
		public:
			virtual void SetTitle(const std::string& title) override;
			virtual void Destroy() override;
			virtual void Minimize() override;
			virtual void Maximize() override;
			virtual void Show() override;
			virtual void Hide() override;
			virtual void Resize(uint32_t w, uint32_t h) override;
			virtual void SetWindowMode(WindowMode mode) override;
			virtual bool GetWindowMode() override;
			virtual bool IsMaximized() override;
			virtual bool IsMinimized() override;
			virtual bool IsVisible() override;
			virtual void SetOpacity(float opacity) override;
			virtual bool IsPointInWindow(uint32_t x, uint32_t y) const override;

			inline SDL_Window* GetHandle() const { return m_pWindow; }
		};
	}
}