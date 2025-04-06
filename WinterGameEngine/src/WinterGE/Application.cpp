#include "wgepch.h"
#include "Application.h"

// remove this later
#include <GLFW/glfw3.h>

namespace WinterGE
{
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
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

	void Application::OnEvent(Event& Event)
	{
		EventDispatcher Dispatcher(Event);
		Dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

		LOG_CORE_TRACE("{0}", Event.ToString());
	}

	bool Application::OnWindowClose(WindowCloseEvent& Event)
	{
		m_bRunning = false;
		return true;
	}
}