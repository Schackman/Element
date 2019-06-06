#include <pch.h>
#include "WindowsWindow.h"
#include <sstream>

void ErrorCallback(int error, const char* message)
{
	std::stringstream s{};
	s << "GLFW Error: (" << error << ") " << message;
	ELM_ERROR(s. str());
}

elm::core::WindowsWindow::WindowsWindow(const std::string& title, uint32_t width, uint32_t height, WindowMode windowMode)
	: IWindow(title, width, height, windowMode),
	  m_pWindow(nullptr)
{
}

void elm::core::WindowsWindow::Init()
{
	glfwSetErrorCallback(ErrorCallback);
	if (!glfwInit())
	{
		throw std::runtime_error("failed to Initialize GLFW");
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	GLFWwindow* window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);
	if (!window)
	{
		throw std::runtime_error("failed to create GLFWwindow");
	}
	m_pWindow = window;
	glfwSetKeyCallback(m_pWindow, KeyCallback);
	glfwMakeContextCurrent(m_pWindow);
	glfwSwapInterval(1);

}

void elm::core::WindowsWindow::SetTitle(const std::string& title)
{
	if (m_pWindow)
	{
		m_Title = title;
		(m_pWindow, title.c_str());
	}
}

void elm::core::WindowsWindow::SwapBuffers()
{
	glfwSwapBuffers(m_pWindow);
}

void elm::core::WindowsWindow::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void elm::core::WindowsWindow::Destroy()
{
	if (m_pWindow)
	{
		glfwTerminate();
	}
}
