#pragma once

#include "Gluttony/Layer.h"

namespace Gluttony {

	class UILayer : public Layer {

	public:
		UILayer();
		~UILayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);

	private:

	};

}