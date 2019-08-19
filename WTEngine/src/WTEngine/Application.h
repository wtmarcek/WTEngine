#pragma once

#include "Core.h"
#include "Window.h"
#include "WTEngine/Layers/LayerStack.h"
#include "WTEngine/Events/Event.h"

#include "WTEngine/Events/ApplicationEvent.h"
#include "WTEngine/Renderer/Shaders/Shader.h"
#include "WTEngine/Renderer/Buffers/Buffer.h"

#include "WTEngine//ImGui/ImGuiLayer.h"

using namespace std;

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

		inline static Application& Get() { return *instance; }
		inline Window& GetWindow() { return *window; }
	
	private:
		std::unique_ptr<Window> window;
		ImGuiLayer* imGuiLayer;
		
		bool isRunning = true;
		
		bool OnWindowClose(WindowCloseEvent& e);
		LayerStack layerStack;

		unsigned int vertexArray;
		unique_ptr<Shader> shader;
		unique_ptr<VertexBuffer> vertexBuffer;
		unique_ptr<IndexBuffer> indexBuffer;

	private:
		static Application* instance;
	};
	Application* CreateApplication();
}