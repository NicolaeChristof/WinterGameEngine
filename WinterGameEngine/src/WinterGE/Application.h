#pragma once

#include "Core.h"
#include "Window.h"

#include "WinterGE/Events/ApplicationEvent.h"
#include "WinterGE/Layers/LayerStack.h"

namespace WinterGE
{
	class WGE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& Event);

		void PushLayer(Layer* Layer);
		void PopLayer(Layer* Layer);
		void PushOverlay(Layer* Overlay);
		void PopOverlay(Layer* Overlay);

		static inline Application& Get()
		{
			return *s_Instance;
		}

		inline Window& GetWindow()
		{
			return *m_Window;
		}

	private:
		static Application* s_Instance;

		bool OnWindowClose(WindowCloseEvent& Event);

		std::unique_ptr<Window> m_Window;
		bool m_bRunning = true;
		LayerStack m_LayerStack;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}