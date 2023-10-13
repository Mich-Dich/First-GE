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


		/*
		GL_CORE_TRACE(e);
		GL_CORE_INFO(e);
		GL_CORE_WARN(e);
		GL_CORE_ERROR(e);
		GL_CORE_CRITICAL(e);

		GL_TRACE(e);
		GL_INFO(e);
		GL_WARN(e);
		GL_ERROR(e);
		GL_CRITICAL(e);
		*/

		while (true);

	}

}