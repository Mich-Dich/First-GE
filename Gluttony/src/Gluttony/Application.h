#pragma once

#include "Core.h"

namespace Gluttony {

	class GLUTTONY_API Application {

	public:
		// Constructor
		Application();

		// Destructor
		virtual ~Application();

		void Run();

	};

	//To be defined in Client
	Application* CreateApplication();


}

