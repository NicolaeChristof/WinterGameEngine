#pragma once

#include "Core.h"
#include "Window.h"

#include "WinterGE/Events/ApplicationEvent.h"

namespace WinterGE
{
	class WGE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& Event);

	private:
		bool OnWindowClose(WindowCloseEvent& Event);

		std::unique_ptr<Window> m_Window;
		bool m_bRunning = true;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}