#include "Application.h"

#include "Gluttony/Events/ApplicationEvent.h"
#include "Gluttony/Log.h"

namespace Gluttony {

	Application::Application() {

	}

	Application::~Application() {

	}

	void Application::Run() {
		
		WindowResizeEvent e(1280, 720);
		GL_LOG_TRACE(e);

		while (true);

	}

}