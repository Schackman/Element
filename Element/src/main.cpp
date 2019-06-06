#include "pch.h"
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#include "core/platform/windows/WindowsWindow.h"
#include "renderer/RenderManager.h"


int main(int argc, char** argv) {
	using namespace elm;
	log::Logger::Init();
	ELM_DEBUG("logger initialized");
	core::WindowsWindow window{"GLFW", 1280, 720};
	window.Init();
	//renderer::RenderManager renderManager{};
	//renderManager.CreateSystem();
	while (!glfwWindowShouldClose(window.GetHandle()))
	{
		glfwPollEvents();
		window.SwapBuffers();
	}
	window.Destroy();
	return 0;
}