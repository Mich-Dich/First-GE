#pragma once

#include "Core.h"

#include "Gluttony/LayerStack.h"
#include "Gluttony/Window.h"
#include "Gluttony/Events/Event.h"
#include "Gluttony/Events/ApplicationEvent.h"

namespace Gluttony {

	class GLUTTONY_API Application {

	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

	private:
		bool OnWindowClose(WindowCloseEvent& event);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	//To be defined in Client
	Application* CreateApplication();
}

