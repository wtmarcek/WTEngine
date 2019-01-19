#pragma once

#include "wtfpch.h"
#include "Application.h"

#include <glad/glad.h>


namespace WTF {

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		WTF_CORE_ASSERT(!s_Instance, "Appliaction already exsists!");

		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
	}

	Application::~Application()
	{
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

		for (auto iter = m_LayerStack.end(); iter != m_LayerStack.begin();)
		{
			(*--iter)->OnEvent(e);
			if (e.m_Handled)
			{
				break;
			}
		}

		WTF_CORE_TRACE("{0}", e);
	}

	void Application::PushLayer(Layer * layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}
	
	void Application::PushOverlay(Layer * layer)
	{
		m_LayerStack.PushOverlay(layer);
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

			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
			}

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}