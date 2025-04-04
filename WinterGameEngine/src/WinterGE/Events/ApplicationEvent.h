#pragma once

#include "Event.h"

namespace WinterGE
{
	class WGE_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int Width, unsigned int Height) : m_Width(Width), m_Height(Height)
		{
		}

		inline unsigned int GetWidth() const
		{
			return m_Width;
		}

		inline unsigned int GetHeight() const
		{
			return m_Height;
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	private:
		unsigned int m_Width;
		unsigned int m_Height;
	};

	class WGE_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent()
		{
		}

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class WGE_API AppTickEvent : public Event
	{
	public:
		AppTickEvent()
		{
		}

		EVENT_CLASS_TYPE(AppTick)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class WGE_API AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent()
		{
		}

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class WGE_API AppRenderEvent : public Event
	{
	public:
		AppRenderEvent()
		{
		}

		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}