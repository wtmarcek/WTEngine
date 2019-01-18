#pragma once

#include "wtfpch.h"
#include "Application.h"

#include "WTEngine/Log.h"

#include <GLFW/glfw3.h>


namespace WTF {

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application::Application()
	{
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

		WTF_CORE_TRACE("{0}", e);
	}

	void Application::Run()
	{
		WindowResizeEvent windowResizeEvent(1280, 720);
		WTF_TRACE(windowResizeEvent);

		while (m_Running)
		{
			glClearColor(0, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}