#include "pch.h"
#include "GLRenderer.h"
#include "../../core/Context.h"
#include <string>

namespace elm { namespace renderer{
	int GLRenderer::Init()
	{
		if (!m_WindowInfo.handle)
		{
			return -1;
		}
		glfwMakeContextCurrent(m_WindowInfo.handle);
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		return 0;
	}

	GLRenderer::GLRenderer(const WindowContext& context)
		: m_pHandle(nullptr),
		  m_WindowInfo{static_cast<GLFWwindow*>(context.handle), "OpenGL"}
	{
	}

	void GLRenderer::Render() const
	{
	}

	void GLRenderer::Clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	int GLRenderer::ShutDown()
	{
		return 0;
	}

	/*const std::string& GLRenderer::GetName() const
	{
		return m_WindowInfo.name;
	}*/
}}
