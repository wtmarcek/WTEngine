#pragma once

#include <WTEngine.h>

class ExampleLayer : public WTF::Layer
{
public:
	ExampleLayer() : Layer("Example") {}

	void OnUpdate() override
	{
		if (WTF::Input::IsKeyPressed(WTF_KEY_TAB))
			WTF_INFO("Tab");
	}

	void OnEvent(WTF::Event& event) override
	{
		//WTF_TRACE("wololo");
	}
};

class Sandbox : public WTF::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new WTF::ImGuiLayer());
	}

	~Sandbox()
	{
	}
};

WTF::Application* WTF::CreateApplication()
{
	return new Sandbox();
}