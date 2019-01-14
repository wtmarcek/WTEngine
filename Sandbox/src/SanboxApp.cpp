#include <WTEngine.h>

class Sandbox : public WTF::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

WTF::Application* WTF::CreateApplication()
{
	return new Sandbox();
}