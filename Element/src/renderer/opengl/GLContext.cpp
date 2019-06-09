#include "pch.h"
#include "GLContext.h"
#include "../error/RenderException.h"

namespace elm { namespace renderer
{
	GLContext::GLContext()
		: m_pWindow(nullptr)
	{
	}

	void GLContext::Init()
	{
		glfwSetErrorCallback(ErrorCallback);
		ELM_DEBUG("Set GLFW error callback");

		if (!glfwInit())
		{
			throw std::runtime_error("failed to Initialize GLFW");
		}
		if (!m_pWindow)
		{
			return throw exception::RenderException{err::Error::null_ptr, "Window is nullptr"};
		}
		glfwMakeContextCurrent(m_pWindow);
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		glfwMakeContextCurrent(nullptr);
	}

	void GLContext::Destroy() noexcept
	{
	}

	GLContext::~GLContext()
	{
	}

	void GLContext::ErrorCallback(int error, const char* message)
	{
		std::stringstream s{};
		s << "GLFW Error: (" << error << ") " << message;
		ELM_ERROR(s.str());
	}
}}
