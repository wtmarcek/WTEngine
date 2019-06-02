#pragma once

#include "Core.h"
#include "Window.h"
#include "WTEngine/Layers/LayerStack.h"
#include "WTEngine/Events/Event.h"
#include "WTEngine/Events/ApplicationEvent.h"

#include "WTEngine//ImGui/ImGuiLayer.h"

namespace WTF {

	class WTF_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *window; }
	private:
		std::unique_ptr<Window> window;
		ImGuiLayer* imGuiLayer;
		

		bool m_Running = true;
		
		bool OnWindowClose(WindowCloseEvent& e);
		LayerStack layerStack;

	private:
		static Application* s_Instance;
	};
	Application* CreateApplication();
}