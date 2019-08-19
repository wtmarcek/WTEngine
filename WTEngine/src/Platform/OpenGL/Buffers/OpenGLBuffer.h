#pragma once

#include "WTEngine/Renderer/Buffers/Buffer.h"


namespace WTF
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		void Bind() const override;
		void Unbind() const override;

		virtual const BufferLayout& GetLayout() const { return layout; }
		virtual void SetLayout(const BufferLayout& layout) { this->layout = layout; }

	private:
		uint32_t rendererID;
		BufferLayout layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t size);
		virtual ~OpenGLIndexBuffer();

		void Bind() const override;
		void Unbind() const override;
		uint32_t GetCount() const override;

	private:
		uint32_t rendererID;
		uint32_t count;
	};
}