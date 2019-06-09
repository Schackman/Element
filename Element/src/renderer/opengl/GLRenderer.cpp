#include "pch.h"
#include "GLRenderer.h"
#include "../../core/Context.h"
#include <string>

namespace elm { namespace renderer{

	GLRenderer::GLRenderer(){}

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
}}
