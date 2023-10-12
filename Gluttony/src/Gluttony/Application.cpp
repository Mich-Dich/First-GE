#include "glpch.h"
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
		GL_CORE_LOG(Log, e);
		GL_CORE_LOG(Trace, e);
		GL_CORE_LOG(Success, e);
		GL_CORE_LOG(Warning, e);
		GL_CORE_LOG(Error, e);
		GL_CORE_LOG(Fatal, e);


		GL_LOG(Log, e);
		GL_LOG(Trace, e);
		GL_LOG(Success, e);
		GL_LOG(Warning, e);
		GL_LOG(Error, e);
		GL_LOG(Fatal, e);

		while (true);

	}

}