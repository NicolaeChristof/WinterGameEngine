#include "wgepch.h"
#include "Application.h"

// remove this when we remove the color change from the run loop
#include <glad/glad.h>

namespace WinterGE
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		WGE_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

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

			// Starts at bottom most layer and works up to top layer/overlays
			for (Layer* Layer : m_LayerStack)
			{
				Layer->OnUpdate();
			}

			m_Window->OnUpdate();
		}
	}

	// OnEvent gets called by the Window whenever events are triggered
	// We are passed an Event with information about the Event
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
		Layer->OnAttach();
	}

	void Application::PopLayer(Layer* Layer)
	{
		m_LayerStack.PopLayer(Layer);
		Layer->OnDetach();
	}

	void Application::PushOverlay(Layer* Overlay)
	{
		m_LayerStack.PushOverlay(Overlay);
		Overlay->OnAttach();
	}

	void Application::PopOverlay(Layer* Overlay)
	{
		m_LayerStack.PopOverlay(Overlay);
		Overlay->OnDetach();
	}

// Private Function Definitions

	bool Application::OnWindowClose(WindowCloseEvent& Event)
	{
		m_bRunning = false;
		return true;
	}
}