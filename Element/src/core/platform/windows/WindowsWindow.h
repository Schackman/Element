#pragma once
#include "../../IWindow.h"
#include <string>

namespace elm { namespace core
{
	class WindowsWindow final : public IWindow
	{
	public:
		explicit WindowsWindow(const std::string& title, uint32_t width, uint32_t height,
		                       WindowMode windowMode = WindowMode::WINDOWED);

		virtual ~WindowsWindow() = default;

		virtual void Init() override;
		virtual void Destroy() override;
		virtual void SetTitle(const std::string& title) override;
		inline GLFWwindow* GetHandle() const { return m_pWindow; }

		virtual void SetWindowMode(WindowMode mode) override
		{

		}

		void SwapBuffers();
	private:
		GLFWwindow* m_pWindow;

		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	};
}}
