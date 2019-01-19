#include <WTEngine.h>


class ExampleLayer : public WTF::Layer
{
public:
	ExampleLayer()
		: Layer("Example") {}

	void OnUpdate() override
	{
		WTF_INFO("ExampleLayer::Update");
	}

	void OnEvent(WTF::Event& event) override
	{
		WTF_TRACE("{0}", event);
	}

};

class Sandbox : public WTF::Application
{
public:
	Sandbox()
	{
		WTF::Layer* layer = new WTF::Layer("chuj");
		PushLayer(layer);
	}

	~Sandbox()
	{
	}
};

WTF::Application* WTF::CreateApplication()
{
	return new Sandbox();
}