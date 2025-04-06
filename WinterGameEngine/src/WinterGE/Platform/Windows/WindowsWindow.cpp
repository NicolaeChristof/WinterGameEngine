#include "wgepch.h"
#include "WindowsWindow.h"

#include "WinterGE/Events/ApplicationEvent.h"
#include "WinterGE/Events/MouseEvent.h"
#include "WinterGE/Events/KeyEvent.h"

namespace WinterGE
{
	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int Error, const char* Description)
	{
		LOG_CORE_ERROR("GLFW Error ({0}): {1}", Error, Description);
	}

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
			glfwSetErrorCallback(GLFWErrorCallback);

			s_GLFWInitialized = true;
		}

		// Create GLFW Window
		m_Window = glfwCreateWindow((int)Properties.Width, (int)Properties.Height, Properties.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		SetGLFWCallback();
	}

	void WindowsWindow::SetGLFWCallback()
	{
		// Application Callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* Window, int Width, int Height)
			{
				WindowData& Data = *(WindowData*)glfwGetWindowUserPointer(Window);
				Data.Width = Width;
				Data.Height = Height;

				WindowResizeEvent Event(Width, Height);
				Data.EventCallback(Event);
			}
		);

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* Window)
			{
				WindowData& Data = *(WindowData*)glfwGetWindowUserPointer(Window);

				WindowCloseEvent Event;
				Data.EventCallback(Event);
			}
		);

		// Keyboard Callbacks
		glfwSetKeyCallback(m_Window, [](GLFWwindow* Window, int Key, int Scancode, int Action, int Mods)
			{
				WindowData& Data = *(WindowData*)glfwGetWindowUserPointer(Window);

				switch (Action)
				{
					case GLFW_PRESS:
					{
						KeyPressedEvent Event(Key, 0);
						Data.EventCallback(Event);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleasedEvent Event(Key);
						Data.EventCallback(Event);
						break;
					}
					case GLFW_REPEAT:
					{
						KeyPressedEvent Event(Key, 1);
						Data.EventCallback(Event);
						break;
					}
					default:
						break;
				}
			}
		);

		// Mouse Callbacks
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* Window, double XPos, double YPos)
			{
				WindowData& Data = *(WindowData*)glfwGetWindowUserPointer(Window);

				MouseMovedEvent Event(XPos, YPos);
				Data.EventCallback(Event);
			}
		);

		glfwSetScrollCallback(m_Window, [](GLFWwindow* Window, double XOffset, double YOffset)
			{
				WindowData& Data = *(WindowData*)glfwGetWindowUserPointer(Window);

				MouseScrolledEvent Event(XOffset, YOffset);
				Data.EventCallback(Event);
			}
		);

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* Window, int Button, int Action, int Mods)
			{
				WindowData& Data = *(WindowData*)glfwGetWindowUserPointer(Window);

				switch (Action)
				{
					case GLFW_PRESS:
					{
						MouseButtonPressedEvent Event(Button);
						Data.EventCallback(Event);
						break;
					}
					case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent Event(Button);
						Data.EventCallback(Event);
						break;
					}
					default:
						break;
				}
			}
		);
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