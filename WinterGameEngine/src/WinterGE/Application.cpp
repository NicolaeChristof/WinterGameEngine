#include "wgepch.h"

#include "Application.h"

#include "WinterGE/Events/ApplicationEvent.h"

// remove this later
#include <GLFW/glfw3.h>

namespace WinterGE
{
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (m_bRunning)
		{
			glClearColor(1, 0, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Window->OnUpdate();
		}
	}
}