#include "stdafx.h"
#include <iostream>
#include "core\Window.h"

int main(int argc, char** argv) {
	if (SDL_VideoInit(nullptr) == -1)
	{
		std::cout << SDL_GetError() << std::endl;
	}
	
	elm::core::Window window{ "", elm::core::Window::WindowMode::WINDOWED, 1280, 720 };

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
	SDL_VideoQuit();
	return 0;
}