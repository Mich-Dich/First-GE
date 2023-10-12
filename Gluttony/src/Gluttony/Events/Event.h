#pragma once

#include "Gluttony/Core.h"

namespace Gluttony {

	/*	Future changes - UNFINISHED
	
	Events are currently bocking (blocking the engine untill they are done)
	Evennt should be bufferd in an event bus and proccessed in a dedicated segtion during update stage */


	enum class EventType {
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory {
		None = 0,
		EventCategoryApplication	= BIT(0),
		EventCategoryInput			= BIT(1),
		EventCategoryKeyboard		= BIT(2),
		EventCategoryMouse			= BIT(3),
		EventCategoryMouseButton	= BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category)	virtual int GetCategoryFlags() const override { return category; }

	class GLUTTONY_API Event {

		friend class EventDispacher;

	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;

		virtual std::string ToString() const {
			return GetName(); 
		}

		inline bool IsInCategory(EventCategory category) {
			return GetCategoryFlags() & category;
		}

	protected:
		bool m_Handeled = false;

	};

	// Class for Dispaching specific Events
	class EventDispacher {

		template<typename T> using EventFn = std::function<bool(T&)>;

	public:

		EventDispacher(Event& event)
			: m_Event(event) {}

		template<typename T> bool Dispacher(EventFn<T> func) {

			if (m_Event.GetEventType() == T::GetStaticType()) {

				m_Event.m_Handeled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e) { return os << e.ToString(); }
}