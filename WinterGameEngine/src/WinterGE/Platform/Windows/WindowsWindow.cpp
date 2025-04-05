#include "wgepch.h"

#include "WindowsWindow.h"

namespace WinterGE
{
	static bool s_GLFWInitialized = false;

	Window* Window::Create(const WindowProperties& Properties)
	{
		return new WindowsWindow(Properties);
	}

	WindowsWindow::WindowsWindow(const WindowProperties& Properties)
	{
		Init(Properties);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProperties& Properties)
	{
		m_Data.Title = Properties.Title;
		m_Data.Width = Properties.Width;
		m_Data.Height = Properties.Height;

		LOG_CORE_INFO("Creating window {0} ({1}, {2})", Properties.Title, Properties.Width, Properties.Height);

		if (!s_GLFWInitialized)
		{
			// TODO glfwTerminate on system shutdown
			int success = glfwInit();
			WGE_CORE_ASSERT(success, "Could not initialize GLFW!");

			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)Properties.Width, (int)Properties.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(bool bEnabled)
	{
		if (bEnabled)
		{
			glfwSwapInterval(1);
		}
		else
		{
			glfwSwapInterval(0);
		}

		m_Data.VSync = bEnabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}
}