#pragma once

#include "Core.h"
#include "Window.h"

namespace WinterGE
{
	class WGE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	private:
		std::unique_ptr<Window> m_Window;
		bool m_bRunning = true;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}