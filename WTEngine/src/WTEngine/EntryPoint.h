#pragma once

#ifdef  WTF_PLATFORM_WINDOWS

extern WTF::Application* WTF::CreateApplication();

int main(int argc, char** argv)
{
	WTF::Log::Init();
	WTF::Log::GetCoreLogger()->error("Hello Engine");
	WTF::Log::GetClientLogger()->info("Hello Client");


	auto app = WTF::CreateApplication();
	app->Run();
	delete app;
}

#endif //  WTF_PLATFORM_WINDOWS
