#include "pch.h"
#include "GLContext.h"
#include "../error/RenderException.h"

namespace elm { namespace renderer
{
	GLContext::GLContext(const core::Window::Handle& w, const core::APIVersion& api)
		: m_pWindow(w.glfw),
		  m_Version(api)
	{
		assert(api.api == core::GraphicsAPI::opengl);
	}

	void GLContext::Init()
	{
		if (!m_pWindow)
		{
			throw exception::RenderException{err::Error::null_ptr, "Window is nullptr"};
		}
		glfwMakeContextCurrent(GetHandle());
		int succeeded = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		if (!succeeded)
		{
			throw exception::RenderException{err::Error::opengl, "Glad failed to load."};
		}
		ELM_DEBUG_ONLY
		(		
			int major = glfwGetWindowAttrib(GetHandle(), GLFW_CONTEXT_VERSION_MAJOR);
			int minor = glfwGetWindowAttrib(GetHandle(), GLFW_CONTEXT_VERSION_MINOR);
			std::stringstream s{};
			s << "Glad successfully loaded OpenGL version " << major << "." << minor;
			ELM_INFO(s.str());
		)
	}
	size_t g_Frames{0};
	void GLContext::SwapBuffers()
	{
		glfwMakeContextCurrent(GetHandle());
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwSwapBuffers(GetHandle());
	}

	void GLContext::Destroy() noexcept
	{
	}

	GLContext::~GLContext()
	{
	}
}}
