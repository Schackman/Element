#include <pch.h>
#include "../renderer/opengl/GLContext.h"
#include "../exception/Exception.h"
#ifdef ELM_PLATFORM_WINDOWS
#include "WindowsWindow.h"
#include <sstream>


namespace elm { namespace core
{
#pragma region WindowsWindowMembers
	WindowsWindow::WindowsWindow(const std::string& title, uint32_t width, uint32_t height,
	                             WindowMode windowMode)
		: Window(),
		  m_pWindow(nullptr),
		  m_pRenderContext(nullptr),
		  m_Title(title),
		  m_Width(width),
		  m_Height(height),
		  m_WindowMode(windowMode)
	{
	}

	WindowsWindow::~WindowsWindow()
	{
		if(m_pRenderContext)
		{
			delete m_pRenderContext;
		}
		Destroy();
	}

	void WindowsWindow::Init()
	{
		if (!s_Initialized)
		{
			InitGLFW();
		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		GLFWwindow* window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);
		if (!window)
		{
			throw std::runtime_error("failed to create GLFWwindow");
		}
		m_pWindow = window;
		glfwSetKeyCallback(m_pWindow, KeyCallback);
		glfwMakeContextCurrent(m_pWindow);
		ELM_INFO("Created " + ToString());

		m_pRenderContext = new renderer::GLContext(m_pWindow);
		if (!m_pRenderContext)
		{
			throw exception::Exception{"RenderContext is nullptr"};
		}
		m_pRenderContext->Init();
	}

	void WindowsWindow::SetTitle(const std::string& title)
	{
		if (m_pWindow)
		{
			m_Title = title;
			glfwSetWindowTitle(m_pWindow, title.c_str());
		}
	}

	void WindowsWindow::OnFrameEnd()
	{
		m_pRenderContext->SwapBuffers();
	}

	void WindowsWindow::ErrorCallback(int error, const char* message)
	{
		std::stringstream s{};
		s << "GLFW Error: (" << error << ") " << message;
		ELM_ERROR(s.str());
	}

	void WindowsWindow::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GLFW_TRUE);
	}

	void WindowsWindow::Destroy()
	{
		if (m_pWindow)
		{
			glfwDestroyWindow(m_pWindow);
			m_pWindow = nullptr;
			ELM_INFO("Destroyed window " + m_Title);
		}
	}

	ELM_DEBUG_ONLY
	(
		std::string WindowsWindow::ToString() const
		{
			std::stringstream s{};
		s << "Window{title=\"" << m_Title << "\", size=(" << m_Width << "x" << m_Height << ")}";
		return s.str();
		}
	)


#pragma endregion WindowsWindowMembers

#pragma region StaticMembers
	Window* Window::Create(const WindowAttributes& attributes, const std::string& title)
	{
		return new WindowsWindow(title, attributes.width, attributes.height, attributes.mode);
	}

	void WindowsWindow::InitGLFW()
	{
		glfwSetErrorCallback(ErrorCallback);
		if (!glfwInit())
		{
			throw std::runtime_error("failed to Initialize GLFW");
		}
	}

	void WindowsWindow::ShutdownGLFW() noexcept
	{
		if (s_Initialized)
		{
			glfwTerminate();
		}
	}

	bool WindowsWindow::s_Initialized{false};
#pragma endregion StaticMembers
}}
#endif
