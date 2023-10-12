#pragma once

#include "Event.h"

#include <sstream>

namespace Gluttony {

	// Class speciffic for Moving mouse
	class GLUTTONY_API MouseMovedEvent : public Event {

	public:
		MouseMovedEvent(float x, float y)
			: m_MouseX(x), m_MouseY(y) {}

		inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }

		// not the most memory efficient but bood for now
		std::string ToString() const override {

			std::stringstream ss;
			ss << "MouseMoveEvent [X: " << m_MouseX << " Y: " << m_MouseY << "]";
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_MouseX, m_MouseY;
	};

	// Event speciffic for Scrolling
	class GLUTTONY_API MouseScrolledEvent : public Event {

	public:
		MouseScrolledEvent(float OffsetX, float OffsetY)
			: m_OffsetX(OffsetX), m_OffsetY(OffsetY) {}

		inline float GetX() const { return m_OffsetX; }
		inline float GetY() const { return m_OffsetY; }

		// not the most memory efficient but bood for now
		std::string ToString() const override {

			std::stringstream ss;
			ss << "MouseMoveEvent [X: " << m_OffsetX << " Y: " << m_OffsetY << "]";
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_OffsetX, m_OffsetY;
	};

	// Base Calss (Protected Constructor)
	class GLUTTONY_API MouseButtonEvent : public Event {

	public:

		inline int GetMouseButton() const { return m_Button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	protected:

		MouseButtonEvent(int button)
			: m_Button(button) {}

		int m_Button;
	};


	class GLUTTONY_API MouseButtonPressedEvent : public MouseButtonEvent {

	public:
		MouseButtonPressedEvent(int button)
			: MouseButtonEvent(button) {}

		// not the most memory efficient but bood for now
		std::string ToString() const override {

			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	// Usable SubClass 
	class GLUTTONY_API MouseButtonReleasedEvent : public MouseButtonEvent {

	public:
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button) {}

		// not the most memory efficient but bood for now
		std::string ToString() const override {

			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};




}