#include <WTEngine.h>

class Sandbox : public WTF::Application
{
public:
	Sandbox()
	{
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