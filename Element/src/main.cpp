#include "pch.h"
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#include <time.h>
#include "core/platform/windows/WindowsWindow.h"
#include "system/vulkan/VulkanSystem.h"


int main(int argc, char** argv) {
	elm::log::Logger::Init();
	ELM_DEBUG("Default logger initialized");

	srand((unsigned int)time(nullptr));
	if (SDL_VideoInit(nullptr) == -1)
	{
		ELM_CRITICAL(SDL_GetError());
		return -1;
	}
	ELM_DEBUG("SDL_VideoInit() succeeded");

	elm::core::WindowsWindow window{ "Element Engine", elm::core::IWindow::WindowMode::WINDOWED, 1280, 720 };

	elm::sys::VulkanSystem vkSys{ window.GetHandle() };
	vkSys.Init();
	vkSys.LogPhysicalDeviceProperties();

	bool running{ true };
	while (running)
	{
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT:
				running = false;
			default:
				break;
			}
		}

	}
	vkSys.ShutDown();
	SDL_VideoQuit();
	return 0;
}