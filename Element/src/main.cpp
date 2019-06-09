#include "pch.h"
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#include "core/platform/windows/WindowsWindow.h"
#include "renderer/RenderManager.h"
#include "core/Context.h"
#include "renderer/RenderContext.h"
#include "renderer/opengl/GLContext.h"


int main(int argc, char** argv) {
	using namespace elm;
	log::Logger::Init();
	ELM_DEBUG("logger initialized");
	core::WindowsWindow window{"GLFW", 1280, 720};
	window.Init();
	const auto windowContext = elm::WindowContext{ static_cast<void*>(window.GetHandle()) };
	renderer::RenderContext* renderContext = new renderer::GLContext{ windowContext };
	renderer::RenderManager renderManager(*renderContext);
		
	renderManager.CreateRenderer(renderer::RenderTypes::opengl);
	renderManager.CurrentRenderer(renderer::RenderTypes::opengl);
	renderManager.InitRenderer();
	renderManager.Update();
	while (!glfwWindowShouldClose(window.GetHandle()))
	{
		glfwPollEvents();
		window.SwapBuffers();
	}
	window.Destroy();
	return 0;
}
