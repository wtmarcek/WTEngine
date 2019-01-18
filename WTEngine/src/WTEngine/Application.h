#pragma once

#include "Core.h"
#include "Window.h"
#include "WTEngine/Events/ApplicationEvent.h"


namespace WTF {

	class WTEngine_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		
		bool OnWindowClose(WindowCloseEvent& e);
	};
	Application* CreateApplication();
}