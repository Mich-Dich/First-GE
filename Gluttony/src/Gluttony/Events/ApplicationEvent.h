#pragma once

#include "Event.h"

namespace Gluttony {

	class GLUTTONY_API WindowResizeEvent : public Event {
	
	public:

		WindowResizeEvent(unsigned int width, unsigned int height)
			: m_Width(width), m_Height(height) {}

		// simple getters
		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }

		// not the most memory efficient but bood for now
		std::string ToString() const override {
			std::stringstream ss;
			ss << "WindowResizeEvent: [X: " << m_Width << ", Y:" << m_Height << "]";
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	private:

		unsigned int m_Width, m_Height;
	};

	class GLUTTONY_API WindowCloseEvent : public Event {

	public:

		// simple Constructor
		WindowCloseEvent() {}

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};


	class GLUTTONY_API AppTickEvent : public Event {

	public:

		// simple Constructor
		AppTickEvent() {}

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class GLUTTONY_API AppUpdateEvent : public Event {

	public:

		// simple Constructor
		AppUpdateEvent() {}

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class GLUTTONY_API AppRenderEvent : public Event {

	public:

		// simple Constructor
		AppRenderEvent() {}

		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};



}