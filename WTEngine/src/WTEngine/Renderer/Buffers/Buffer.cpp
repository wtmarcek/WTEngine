#pragma once
#include "wtfpch.h"
#include "Buffer.h"

#include "WTEngine/Renderer/Renderer.h"
#include "Platform/OpenGL/Buffers/OpenGLBuffer.h"

//VertexBuffer
WTF::VertexBuffer* WTF::VertexBuffer::Create(float * vertices, uint32_t size)
{
	switch (Renderer::GetAPI())
	{
		case RendererAPI::None: 
			WTF_CORE_ASSERT(false, "RendererAPI::None is not supported"); 
			return nullptr;
		case RendererAPI::OpenGL: 
			return new OpenGLVertexBuffer(vertices, size);
	}

	WTF_CORE_ASSERT(false, "Invalid RendererAPI");
	return nullptr;
}

//IndexBuffer
WTF::IndexBuffer* WTF::IndexBuffer::Create(uint32_t * indices, uint32_t size)
{
	switch (Renderer::GetAPI())
	{
		case RendererAPI::None:
			WTF_CORE_ASSERT(false, "RendererAPI::None is not supported");
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLIndexBuffer(indices, size);
	}

	WTF_CORE_ASSERT(false, "Invalid RendererAPI");
	return nullptr;
}
