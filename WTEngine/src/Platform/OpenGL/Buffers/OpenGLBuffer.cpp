#pragma once
#include "wtfpch.h"
#include "OpenGLBuffer.h"

#include <glad/glad.h>

//VertexBuffer
WTF::OpenGLVertexBuffer::OpenGLVertexBuffer(float * vertices, uint32_t size)
{
	glCreateBuffers(1, &rendererID);
	Bind();
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

WTF::OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
	glDeleteBuffers(1, &rendererID);
}

void WTF::OpenGLVertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, rendererID);
}

void WTF::OpenGLVertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


//IndexBuffer
WTF::OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t * indices, uint32_t count)
	: count(count)
{
	glGenBuffers(1, &rendererID);
	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

WTF::OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
	glDeleteBuffers(1, &rendererID);
}

void WTF::OpenGLIndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
}

void WTF::OpenGLIndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

uint32_t WTF::OpenGLIndexBuffer::GetCount() const
{
	return count;
}
