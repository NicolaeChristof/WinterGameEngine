#include "wgepch.h"
#include "Application.h"

// remove this when we remove the color change from the run loop
#include <glad/glad.h>

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

			for (Layer* Layer : m_LayerStack)
			{
				Layer->OnUpdate();
			}

			m_Window->OnUpdate();
		}
	}

	// OnEvent gets called by the Window whenever events are triggered
	// We are passed an Event with information on the Event
	void Application::OnEvent(Event& Event)
	{
		EventDispatcher Dispatcher(Event);
		Dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

		LOG_CORE_TRACE("{0}", Event.ToString());

		for (auto Iter = m_LayerStack.end(); Iter != m_LayerStack.begin(); )
		{
			Layer* Layer = *(--Iter);
			if (Layer->IsEnabled())
			{
				Layer->OnEvent(Event);
				if (Event.IsHandled())
				{
					break;
				}
			}
		}
	}

	void Application::PushLayer(Layer* Layer)
	{
		m_LayerStack.PushLayer(Layer);
	}

	void Application::PopLayer(Layer* Layer)
	{
		m_LayerStack.PopLayer(Layer);
	}

	void Application::PushOverlay(Layer* Overlay)
	{
		m_LayerStack.PushOverlay(Overlay);
	}

	void Application::PopOverlay(Layer* Overlay)
	{
		m_LayerStack.PopOverlay(Overlay);
	}

// Private Function Definitions

	bool Application::OnWindowClose(WindowCloseEvent& Event)
	{
		m_bRunning = false;
		return true;
	}
}