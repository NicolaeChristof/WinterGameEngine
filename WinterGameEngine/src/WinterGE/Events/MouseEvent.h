#pragma once

#include "Event.h"

namespace WinterGE
{
	class WGE_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y) : m_MouseX(x), m_MouseY(y)
		{
		}

		inline float GetX() const
		{
			return m_MouseX;
		}

		inline float GetY() const
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
		float m_MouseX;
		float m_MouseY;
	};

	class WGE_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float XOffset, float YOffset) : m_XOffset(XOffset), m_YOffset(YOffset)
		{
		}

		inline float GetXOffset() const
		{
			return m_XOffset;
		}

		inline float GetYOffset() const
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
		float m_XOffset;
		float m_YOffset;
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