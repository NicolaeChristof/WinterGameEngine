#pragma once

#include "Event.h"

namespace WinterGE
{
	class WGE_API KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const
		{
			return m_KeyCode;
		}

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(int KeyCode) : m_KeyCode(KeyCode)
		{
		}

		int m_KeyCode;
	};

	class WGE_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int KeyCode, int RepeatCount) : KeyEvent(KeyCode), m_RepeatCount(RepeatCount)
		{
		}

		inline int GetRepeatCount() const
		{
			return m_RepeatCount;
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << ") repeats";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int m_RepeatCount;
	};

	class WGE_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int KeyCode) : KeyEvent(KeyCode)
		{
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class WGE_API KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int KeyCode) : KeyEvent(KeyCode)
		{
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};
}