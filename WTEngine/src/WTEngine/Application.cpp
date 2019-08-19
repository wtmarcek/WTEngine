#pragma once

#include "wtfpch.h"
#include "Application.h"
#include "Input/Input.h"
#include "WTEngine/Renderer/Buffers/BufferLayout.h"
#include "WTEngine/Renderer/Shaders/ShaderDataType.h"
#include "WTEngine/Renderer/Shaders/Shader.h"

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
		

		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		
		BufferLayout layout = 
		{
			{ Float3, "position", false },
			{ Float4, "color", false },
			{ Float3, "normal", true }
		};

		vertexBuffer->SetLayout(layout);

		uint32_t counter = 0;
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(counter);
			glVertexAttribPointer
			(
				counter,
				element.type.GetComponentCount(),
				element.type.ConvertToGLEnum(),
				element.isNormalized ? GL_TRUE : GL_FALSE, 
				layout.GetStride(), 
				(const void*)element.offset
			);
			counter++;
		}
		
		uint32_t indices[3] = { 0, 1, 2 };		
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		
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
			glDrawElements(GL_TRIANGLES, indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

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