#include <pch.h>
#include "WindowsWindow.h"

elm::core::WindowsWindow::WindowsWindow(const std::string& title, IWindow::WindowMode windowMode, uint32_t width, uint32_t height):
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
	if (!m_pWindow)
	{
		std::string errorMessage{ SDL_GetError() };
		ELM_CRITICAL(errorMessage);
		throw std::runtime_error{ errorMessage };
	}
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
	SDL_HideWindow(m_pWindow);
}

void elm::core::WindowsWindow::Resize(uint32_t w, uint32_t h)
{
	m_Width = w;
	m_Height = h;
	SDL_SetWindowSize(m_pWindow, m_Width, m_Height);
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
	SDL_SetWindowOpacity(m_pWindow, opacity);
}

bool elm::core::WindowsWindow::IsPointInWindow(uint32_t x, uint32_t y) const
{	
	return (x > m_PosX)
		&& (x < m_PosX + m_Width)
		&& (y > m_PosY - m_Height)
		&& (y < m_PosY);
}
