#pragma once

#include "wtfpch.h"
#include "Application.h"

#include "WTEngine/Events/ApplicationEvent.h"
#include "WTEngine/Log.h"


namespace WTF {

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent windowResizeEvent(1280, 720);
		WTF_TRACE(windowResizeEvent);

		while (m_Running)
		{
			m_Window->OnUpdate();
		}
	}
}