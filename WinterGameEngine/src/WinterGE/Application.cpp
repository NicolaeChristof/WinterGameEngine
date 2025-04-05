#include "Application.h"

#include "WinterGE/Events/ApplicationEvent.h"
#include "WinterGE/Log.h"

namespace WinterGE
{
	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		WindowResizeEvent Event(1280, 720);
		WGE_LOG_TRACE(Event.ToString());

		while (true);
	}
}