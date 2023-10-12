#pragma once

#include "Gluttony/Log.h"

#ifdef GL_PLATFORM_WINDOWS

extern Gluttony::Application* Gluttony::CreateApplication();

int main(int argc, char** argv) {

	Gluttony::Log::Init();

	auto app = Gluttony::CreateApplication();
	app->Run();
	delete app;

}
#endif