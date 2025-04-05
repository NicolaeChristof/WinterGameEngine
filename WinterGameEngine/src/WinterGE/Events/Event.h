#pragma once

#include "WinterGE/Core.h"

namespace WinterGE
{
	// Events are currently blocking, meaning when an event occurs it
	// immediately gets dispatched and must be dealt with.
	// TODO: add a buffer for the events in an event bus and process them
	// during the "event" part of the update stage.

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		KeyPressed, KeyReleased,
		MouseMoved, MouseScrolled, MouseButtonPressed, MouseButtonReleased,
		AppTick, AppUpdate, AppRender,

		EventTypeEnd
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication	= BIT(0),
		EventCategoryInput			= BIT(1),
		EventCategoryKeyboard		= BIT(2),
		EventCategoryMouse			= BIT(3),
		EventCategoryMouseButton	= BIT(4)
	};

	class WGE_API Event
	{
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual const char* GetName() const = 0;
		virtual std::string ToString() const
		{
			return GetName();
		}

		inline bool IsInCategory(EventCategory Category)
		{
			return GetCategoryFlags() & Category;
		}
	protected:
		bool m_Handled = false;
	};

// These macros allow us to easily override the pure virtual functions from the base Event class
#define EVENT_CLASS_TYPE(Type)\
static EventType GetStaticType() { return EventType::##Type; }\
virtual EventType GetEventType() const override { return GetStaticType(); }\
virtual const char* GetName() const override { return #Type; }

#define EVENT_CLASS_CATEGORY(Category)\
virtual int GetCategoryFlags() const override { return Category; }

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& Event) : m_Event(Event)
		{
		}

		template<typename T>
		bool Dispatch(std::function<bool(T&)> Func)
		{
			if (T::GetStaticType() == m_Event.GetEventType())
			{
				// This line of code is using type punning which is basically a fancy way to cast m_Event to type T
				m_Event.m_Handled = Func(*(T*)&m_Event);
				// For actual production code I would use a static cast which is more readable
				//m_Event.m_Handled = Func(static_cast<T>(m_Event));
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};

	inline std::ostream& operator<< (std::ostream& Stream, const Event& Event)
	{
		return Stream << Event.ToString();
	}
}