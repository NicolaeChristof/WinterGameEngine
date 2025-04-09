#pragma once

#include "WinterGE/Window.h"

#include <GLFW/glfw3.h>

namespace WinterGE
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProperties& Properties);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override
		{
			return m_Data.Width;
		}

		inline unsigned int GetHeight() const override
		{
			return m_Data.Height;
		}

		// Window attributes
		inline void SetEventCallback(const EventCallbackFn& Callback) override
		{
			m_Data.EventCallback = Callback;
		}

		inline void SetVSync(bool bEnabled) override;
		inline bool IsVSync() const override;

	private:
		virtual void Init(const WindowProperties& Properties);
		virtual void SetGLFWCallback();
		virtual void Shutdown();

	private:
		GLFWwindow* m_Window;

		// Lightweight data to pass to GLFW instead of passing this whole class
		struct WindowData
		{
			std::string Title;
			unsigned int Width;
			unsigned int Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};
}