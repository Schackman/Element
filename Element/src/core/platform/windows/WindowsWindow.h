#pragma once
#ifdef ELM_PLATFORM_WINDOWS
#include "../../Window.h"
#include <string>

namespace elm {namespace renderer
{
	class RenderContext;
}}

union elm::core::Window::Handle
{
	void* native;
	GLFWwindow* glfw;
};

namespace elm { namespace core
{
	class WindowsWindow final : public Window
	{
	public:

		explicit WindowsWindow(const WindowAttributes& attrib, const std::string& title = "Element");
		virtual ~WindowsWindow();

		ELM_DEBUG_ONLY(std::string ToString() const);

		volatile void Init() override;
		void Destroy() override;
		void SetTitle(const std::string& title) override;
		void* GetNativeHandle() override { return m_pHandle.native; }
		void OnFrameEnd() override;
	private:
		Handle m_pHandle;
		renderer::RenderContext* m_pRenderContext;
		std::string m_Title;
		uint32_t m_Width;
		uint32_t m_Height;
		WindowMode m_WindowMode;
		static void ErrorCallback(int error, const char* message);
		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

		void PrepareContext();

		static void InitGLFW();
		static void ShutdownGLFW() noexcept;
		static bool s_Initialized;
		static int s_NrWindows;
	};
}}
#endif
