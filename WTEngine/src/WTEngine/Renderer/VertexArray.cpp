#include "wtfpch.h"

#include "VertexArray.h"



WTF::VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_RendererID));
}


WTF::VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void WTF::VertexArray::AddBuffer(const VertexBuffer & vb, const VertexBufferLayout & layout)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElement();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));
		offset += element.count * VertexBufferElement::GetTypeSize(element.type);
	}
}

void WTF::VertexArray::Bind() const
{	
	GLCall(glBindVertexArray(m_RendererID));
}

void WTF::VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}
