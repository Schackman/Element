#include "pch.h"
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#include "core/Window.h"


int main(int argc, char** argv)
{
	elm::log::Logger::Init();
	using namespace elm::core;
	ELM_DEBUG("logger initialized");
	Window* window{
		Window::Create({APIVersion{GraphicsAPI::opengl, 4, 6}, WindowMode::windowed, 1280U, 720U})
	};
	window->Init();
	//renderManager.CreateRenderer(renderer::RenderTypes::opengl);
	//renderManager.CurrentRenderer(renderer::RenderTypes::opengl);
	//renderManager.InitRenderer();
	//renderManager.Update();
	while (!glfwWindowShouldClose(static_cast<GLFWwindow*>(window->GetNativeHandle())))
	{
		glfwPollEvents();
		window->OnFrameEnd();
	}
	window->Destroy();
	delete window;
	return 0;
}
