#include "pch.h"
#include "GLRenderer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace elm {namespace renderer
{
	int GLRenderer::Init(WindowContext* context)
	{
		assert(context);

		if (!context->handle)
		{
			return -1;
		}

		glfwMakeContextCurrent(static_cast<GLFWwindow*>(context->handle));
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		return 0;
	}

	void GLRenderer::Render() const
	{

	}

	void GLRenderer::Clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		m_WindowInfo.windowHandle;
	}

	int GLRenderer::ShutDown()
	{
		return 0;
	}
}}
