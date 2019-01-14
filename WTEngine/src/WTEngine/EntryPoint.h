#pragma once

#ifdef  WTF_PLATFORM_WINDOWS

extern WTF::Application* WTF::CreateApplication();

int main(int argc, char** argv)
{
	auto app = WTF::CreateApplication();
	app->Run();
	delete app;
}

#endif //  WTF_PLATFORM_WINDOWS
