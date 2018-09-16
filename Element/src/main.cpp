#include "stdafx.h"
#include <iostream>
#include "core/platform/windows/WindowsWindow.h"
#include "system\VulkanSystem.h"

int main(int argc, char** argv) {
	if (SDL_VideoInit(nullptr) == -1)
	{
		std::cout << SDL_GetError() << std::endl;
	}
	
	elm::core::WindowsWindow window{ "", elm::core::IWindow::WindowMode::WINDOWED, 1280, 720 };
	elm::sys::VulkanSystem vkSys{window.GetHandle()};
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
	std::cin.get();
	return 0;
}