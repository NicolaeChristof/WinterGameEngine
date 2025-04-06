#pragma once

#include "Event.h"

namespace WinterGE
{
	class WGE_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(double x, double y) : m_MouseX(x), m_MouseY(y)
		{
		}

		inline double GetX() const
		{
			return m_MouseX;
		}

		inline double GetY() const
		{
			return m_MouseY;
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		double m_MouseX;
		double m_MouseY;
	};

	class WGE_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(double XOffset, double YOffset) : m_XOffset(XOffset), m_YOffset(YOffset)
		{
		}

		inline double GetXOffset() const
		{
			return m_XOffset;
		}

		inline double GetYOffset() const
		{
			return m_YOffset;
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << m_XOffset << ", " << m_YOffset;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		double m_XOffset;
		double m_YOffset;
	};

	class WGE_API MouseButtonEvent : public Event
	{
	public:
		inline int GetMouseButton() const
		{
			return m_Button;
		}

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	protected:
		MouseButtonEvent(int Button) : m_Button(Button)
		{
		}

		int m_Button;
	};

	class WGE_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int Button) : MouseButtonEvent(Button)
		{
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MovedButtonPressedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class WGE_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int Button) : MouseButtonEvent(Button)
		{
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}