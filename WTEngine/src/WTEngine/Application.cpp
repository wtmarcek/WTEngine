#pragma once

#include "wtfpch.h"
#include "Application.h"
#include "Input/Input.h"

#include <glad/glad.h>

namespace WTF {

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		WTF_CORE_ASSERT(!s_Instance, "Appliaction already exsists!");

		s_Instance = this;

		window = std::unique_ptr<Window>(Window::Create());
		window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		imGuiLayer = new ImGuiLayer();
		PushOverlay(imGuiLayer);
	}

	Application::~Application()
	{
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

		for (auto iter = layerStack.end(); iter != layerStack.begin();)
		{
			(*--iter)->OnEvent(e);
			if (e.m_Handled)
			{
				break;
			}
		}
	}

	void Application::PushLayer(Layer * layer)
	{
		layerStack.PushLayer(layer);
		layer->OnAttach();
	}
	
	void Application::PushOverlay(Layer * layer)
	{
		layerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::Run()
	{
		WindowResizeEvent windowResizeEvent(1280, 720);
		WTF_TRACE(windowResizeEvent);

		while (m_Running)
		{
			glClearColor(0, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : layerStack)
				layer->OnUpdate();
			
			imGuiLayer->Begin();
			for (auto layer : layerStack)
				layer->OnImGuiRender();
			imGuiLayer->End();

			window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}