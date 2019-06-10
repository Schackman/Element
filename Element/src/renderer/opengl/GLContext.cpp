#include "pch.h"
#include "GLContext.h"
#include "../error/RenderException.h"

namespace elm { namespace renderer
{
	GLContext::GLContext(GLFWwindow* w)
		: m_pWindow(w)
	{
	}

	void GLContext::Init()
	{
		if (!glfwInit())
		{
			throw exception::RenderException(err::Error::glfw, "failed to Initialize GLFW");
		}
		if (!m_pWindow)
		{
			throw exception::RenderException{err::Error::null_ptr, "Window is nullptr"};
		}
		glfwMakeContextCurrent(m_pWindow);
		int succeeded = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		if (!succeeded)
		{
			throw exception::RenderException{err::Error::opengl, "Glad failed to load."};
		}
		ELM_DEBUG_ONLY
		(
			int major = glfwGetWindowAttrib(m_pWindow, GLFW_CONTEXT_VERSION_MAJOR);
			int minor = glfwGetWindowAttrib(m_pWindow, GLFW_CONTEXT_VERSION_MINOR);
			std::stringstream s{};
			s << "Glad successfully loaded OpenGL version " << major << "." << minor;
			ELM_INFO(s.str());
		)
	}

	void GLContext::SwapBuffers()
	{
		glfwMakeContextCurrent(m_pWindow);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwSwapBuffers(m_pWindow);
	}

	void GLContext::Destroy() noexcept
	{
	}

	GLContext::~GLContext()
	{
	}
}}
