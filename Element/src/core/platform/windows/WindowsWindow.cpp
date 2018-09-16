#include <stdafx.h>
#include "WindowsWindow.h"

elm::core::WindowsWindow::WindowsWindow(std::string title, IWindow::WindowMode windowMode, size_t width, size_t height):
	IWindow{title, width, height}, m_pWindow{nullptr}
{
	Uint32 flags{ SDL_WINDOW_SHOWN | SDL_WINDOW_VULKAN };
	switch (windowMode)
	{
	case WindowMode::WINDOWED:
		flags |= SDL_WINDOW_RESIZABLE;
		break;
	case WindowMode::FULLSCREEN:
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		break;
	case WindowMode::FULLSCREEN_BORDERLESS:
		flags |= SDL_WINDOW_BORDERLESS;
		break;
	default:
		break;
	}
	
	m_pWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		(int)width, (int)height, flags);
}

elm::core::WindowsWindow::~WindowsWindow()
{
	Destroy();
}

void elm::core::WindowsWindow::SetTitle(const std::string& title)
{
	if (m_pWindow)
	{
		m_Title = title;
		SDL_SetWindowTitle(m_pWindow, title.c_str());
	}
}

void elm::core::WindowsWindow::Destroy()
{
	if (m_pWindow)
	{
		SDL_DestroyWindow(m_pWindow);
	}
}

void elm::core::WindowsWindow::Minimize()
{
	SDL_MinimizeWindow(m_pWindow);
}

void elm::core::WindowsWindow::Maximize()
{
	SDL_MaximizeWindow(m_pWindow);
}

void elm::core::WindowsWindow::Show()
{
	SDL_ShowWindow(m_pWindow);
}

void elm::core::WindowsWindow::Hide()
{
}

void elm::core::WindowsWindow::Resize(size_t w, size_t h)
{
}

void elm::core::WindowsWindow::SetWindowMode(WindowMode mode)
{
}

bool elm::core::WindowsWindow::GetWindowMode()
{
	return false;
}

bool elm::core::WindowsWindow::IsMaximized()
{
	return false;
}

bool elm::core::WindowsWindow::IsMinimized()
{
	return false;
}

bool elm::core::WindowsWindow::IsVisible()
{
	return false;
}

void elm::core::WindowsWindow::SetOpacity(float opacity)
{
}

bool elm::core::WindowsWindow::IsPointInWindow(size_t x, size_t y) const
{
	return false;
}

void * elm::core::WindowsWindow::GetOSWindowHandle() const
{
	return nullptr;
}
