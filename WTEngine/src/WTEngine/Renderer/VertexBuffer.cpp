#include "wtfpch.h"

#include "VertexBuffer.h"
#include "OpenGLDebug.h"


WTF::VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	GLCall(glGenBuffers(1, &m_RendererID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

WTF::VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_RendererID));
}

void WTF::VertexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void WTF::VertexBuffer::Unbind() const
{	
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}
