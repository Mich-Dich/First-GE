#include "glpch.h"
#include "Application.h"
#include "Gluttony/Log.h"

#include <glad/glad.h>

namespace Gluttony {

#define BIND_EVENT_FUNC(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application() {

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FUNC(OnEvent));
	}

	Application::~Application() {}

	void Application::Run() {

		while (m_Running) {

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_Window->OnUpdate();
		}
	}

	void Application::PushLayer(Layer* layer) {

		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer) {

		m_LayerStack.PushOverlay(layer);
	}

	// Handle Event from Window
	void Application::OnEvent(Event& event) {
		
		EventDispacher Dispacher(event);
		Dispacher.Dispacher<WindowCloseEvent>(BIND_EVENT_FUNC(OnWindowClose));
		GL_CORE_LOG("{0}", event);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ) {

			(*--it)->OnEvent(event);
			if (event.Handeled)
				break;
		}

	}

	bool Application::OnWindowClose(WindowCloseEvent& event) {

		m_Running = false;
		return true;
	}
}