#pragma once

#include "Event.h"

namespace Gluttony {

	// Cant be used directly (protected constructor) Use [class KeyPressedEvent] instead
	class GLUTTONY_API KeyEvent : public Event {

	public:
		inline int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:

		// simple Constructor
		KeyEvent(int KeyCode)
			: m_KeyCode(KeyCode) {}

		int m_KeyCode;

	};

	// Calss for handelling a Key "DOWN" Event
	class GLUTTONY_API KeyPressedEvent : public KeyEvent {

	public:

		// simple Constructor
		KeyPressedEvent(int KeyCode, int repeatCount)
			: KeyEvent(KeyCode), m_RepeatCount(repeatCount) {}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		// not the most memory efficient but bood for now
		std::string ToString() const override {

			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)

	protected:
		int m_RepeatCount;

	};

	// Calss for handelling a Key "UP" Event
	class GLUTTONY_API KeyReleasedEvent : public KeyEvent {

	public:

		// simple Constructor
		KeyReleasedEvent(int KeyCode)
			: KeyEvent(KeyCode) {}

		// not the most memory efficient but bood for now
		std::string ToString() const override {

			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};
}