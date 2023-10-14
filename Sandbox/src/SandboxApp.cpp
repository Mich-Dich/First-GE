#include "Gluttony.h"

class ExampleLayer : public Gluttony::Layer {

public:
	ExampleLayer()
		: Layer("Example") {}

	void OnUpdate() override {

		GL_LOG(Log, "Updating Example Layer");
	}

	void OnEvent(Gluttony::Event& event) override {

		GL_LOG(Success, "{0}", event);
	}
};

class Sandbox : public Gluttony::Application {

public:
	Sandbox() {

		PushLayer(new ExampleLayer());
	}

	~Sandbox() {

	}
};

Gluttony::Application* Gluttony::CreateApplication() {

	return new Sandbox();
}