#pragma once

#include "Core.h"
#include "Window.h"
#include "WTEngine/Layers/LayerStack.h"
#include "WTEngine/Events/Event.h"
#include "WTEngine/Events/ApplicationEvent.h"


namespace WTF {

	class WTEngine_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		
		bool OnWindowClose(WindowCloseEvent& e);
		LayerStack m_LayerStack;
	};
	Application* CreateApplication();
}