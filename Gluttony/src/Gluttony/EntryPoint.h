#pragma once

#ifdef GL_PLATFORM_WINDOWS

extern Gluttony::Application* Gluttony::CreateApplication();

int main(int argc, char** argv) {

	Gluttony::Log::Init();

	GL_CORE_LOG_INFO("Engine initialises Logging system");
	int a = 45668;
	GL_LOG_WARM("Answer: {0}", a);

	auto app = Gluttony::CreateApplication();
	app->Run();
	delete app;

}
#endif