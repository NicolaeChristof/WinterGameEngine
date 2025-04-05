#pragma once

#include "wgepch.h"

#include "WinterGE/Core.h"
#include "WinterGE/Events/Event.h"

namespace WinterGE
{
	struct WindowProperties
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProperties(const std::string& Title = "Winter Game Engine", unsigned int Width = 1280, unsigned int Height = 720)
			: Title(Title), Width(Width), Height(Height)
		{
		}
	};

	// Interface representing a desktop system based window.
	// We are creating this as an abstract class because the
	// implementation needs to be platform specific
	class WGE_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window()
		{
		}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFn& Callback) = 0;
		virtual void SetVSync(bool bEnabled) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProperties& Properties = WindowProperties());
	};
}