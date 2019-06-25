#include "pch.h"
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#include "core/Window.h"
#include "entity/Entity.h"
#include "component/Transform.h"


int main(int argc, char** argv)
{
	ELM_DEBUG_ONLY
	(
		elm::log::Logger::Init();
		ELM_DEBUG("logger initialized");
	)
	elm::Entity e{5};
	std::stringstream s{};
	s << e.GetComponent<elm::comp::Transform>();
	ELM_DEBUG(s.str());
	using namespace elm::core;
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
