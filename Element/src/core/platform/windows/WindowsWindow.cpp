#include "pch.h"
#ifdef ELM_PLATFORM_WINDOWS
#include "../renderer/RenderContext.h"
#include "../renderer/opengl/GLContext.h"
#include "../exception/Exception.h"
#include "WindowsWindow.h"
#include <sstream>


namespace elm { namespace core
{
#pragma region WindowsWindowMembers

	WindowsWindow::WindowsWindow(const WindowAttributes& attrib, const std::string& title)
		: Window{attrib.api},
		  m_pHandle{nullptr},
		  m_pRenderContext(nullptr),
		  m_Title{title},
		  m_Width{attrib.width},
		  m_Height{attrib.height},
		  m_WindowMode{attrib.mode}
	{
	}

	WindowsWindow::~WindowsWindow()
	{
		if (m_pRenderContext)
		{
			delete m_pRenderContext;
		}
		Destroy();
	}

	volatile void WindowsWindow::Init()
	{
		if (!s_Initialized)
		{
			InitGLFW();
			s_Initialized = true;
		}
		PrepareContext();
		m_pHandle.glfw = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);
		if (!m_pHandle.glfw)
		{
			throw std::runtime_error("failed to create GLFWwindow");
		}
		++s_NrWindows;
		glfwSetKeyCallback(m_pHandle.glfw, KeyCallback);
		glfwMakeContextCurrent(m_pHandle.glfw);
		ELM_INFO("Created " + ToString());

		m_pRenderContext = renderer::RenderContext::Create<GraphicsAPI::opengl>(m_pHandle, GetAPIVersion());
		if (!m_pRenderContext)
		{
			throw exception::Exception{"RenderContext is nullptr"};
		}
		m_pRenderContext->Init();
	}


	void WindowsWindow::PrepareContext()
	{
		glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GetAPIVersion().versionMajor);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GetAPIVersion().versionMinor);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
		ELM_DEBUG_ONLY(glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE));
	}

	void WindowsWindow::SetTitle(const std::string& title)
	{
		if (m_pHandle.glfw)
		{
			m_Title = title;
			glfwSetWindowTitle(m_pHandle.glfw, title.c_str());
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
		if (m_pHandle.glfw)
		{
			glfwDestroyWindow(m_pHandle.glfw);
			m_pHandle.glfw = nullptr;
			--s_NrWindows;
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
		return new WindowsWindow(attributes, title);
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
		if (s_Initialized && s_NrWindows == 0)
		{
			glfwTerminate();
			s_Initialized = false;
		}
	}

	bool WindowsWindow::s_Initialized{false};
	int WindowsWindow::s_NrWindows{0};
#pragma endregion StaticMembers
}}
#endif
