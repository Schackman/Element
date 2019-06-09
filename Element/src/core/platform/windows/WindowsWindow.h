#pragma once
#include "../../../renderer/RenderContext.h"
#ifdef ELM_PLATFORM_WINDOWS
#include "../../Window.h"
#include <string>

namespace elm { namespace core
{
	class WindowsWindow final : public Window
	{
	public:

		explicit WindowsWindow(const std::string& title, uint32_t width, uint32_t height,
		                       WindowMode windowMode = WindowMode::windowed);
		virtual ~WindowsWindow();

		ELM_DEBUG_ONLY(std::string ToString()) const;

		virtual void Init() override;
		virtual void Destroy() override;
		virtual void SetTitle(const std::string& title) override;
		virtual void* GetNativeHandle() override { return static_cast<void*>(m_pWindow); }
		virtual void OnFrameEnd() override;
	private:
		GLFWwindow* m_pWindow;
		std::unique_ptr<renderer::RenderContext> m_pRenderContext;
		std::string m_Title;
		uint32_t m_Width;
		uint32_t m_Height;
		WindowMode m_WindowMode;
		static void ErrorCallback(int error, const char* message);
		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

		static void InitGLFW();
		static void ShutdownGLFW() noexcept;
		static bool s_Initialized;
	};
}}
#endif
