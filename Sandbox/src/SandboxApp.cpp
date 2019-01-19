#include <WTEngine.h>

class Sandbox : public WTF::Application
{
public:
	Sandbox()
	{
		//WTF::Layer* layer = new WTF::Layer("chuj");
		//PushLayer(layer);

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