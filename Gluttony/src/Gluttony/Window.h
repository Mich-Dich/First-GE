#pragma once

#include "glpch.h"
#include "Gluttony/Core.h"
#include "Gluttony/Events/Event.h"

namespace Gluttony {

	struct WindowProps {

		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string inTitle = "Gluttony Engine", unsigned int inWidth = 1280, unsigned int inHeigth = 720) 
			: Title(inTitle), Width(inWidth), Height(inHeigth) {}
	};

	class GLUTTONY_API Window {

	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}
		virtual void OnUpdate() = 0;

		// virtual getters
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		// Atributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};
}