#pragma once
#include "glad/glad.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "OpenGLDebug.h"

namespace WTF {

	class WTEngine_API VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

		void Bind() const;
		void Unbind() const;
	private:
		unsigned int m_RendererID;
	};

}