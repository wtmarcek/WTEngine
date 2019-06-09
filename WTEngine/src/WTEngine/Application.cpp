#pragma once

#include "wtfpch.h"
#include "Application.h"
#include "Input/Input.h"

#include <glad/glad.h>

namespace WTF {

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application* Application::instance = nullptr;

	Application::Application()
	{
		WTF_CORE_ASSERT(!instance, "Appliaction already exsists!");

		instance = this;

		window = std::unique_ptr<Window>(Window::Create());
		window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		imGuiLayer = new ImGuiLayer();
		PushOverlay(imGuiLayer);

		//VertexArray
		glGenVertexArrays(1, &vertexArray);
		glBindVertexArray(vertexArray);
		//VertexBuffer
		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		//IndexBuffer
		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		glGenBuffers(1, &indexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		
		string vertexSource = R"(
			#version 330 core

			layout (location = 0) in vec3 position;
				
			void main()
			{
				gl_Position = vec4(position, 1.0);
			}
		)";

		string fragmentSource = R"(
			#version 330 core

			layout (location = 0) out vec4 color;
			
			void main()
			{
				color = vec4(1.0, 1.0, 0.0, 1.0);
			}
		)";

		shader = make_unique<Shader>(vertexSource, fragmentSource);
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

		while (isRunning)
		{
			glClearColor(0, 0, 0.5, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			shader->Bind();
			glBindVertexArray(vertexArray);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

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
		isRunning = false;
		return true;
	}
}