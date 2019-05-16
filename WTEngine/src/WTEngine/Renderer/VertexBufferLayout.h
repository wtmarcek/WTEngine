#pragma once
#include <vector>
#include "OpenGLDebug.h"
#include "glad/glad.h"


namespace WTF {

	struct VertexBufferElement
	{
		unsigned int type;
		unsigned int count;
		unsigned char normalized;

		static unsigned int GetTypeSize(unsigned int type)
		{
			switch (type)
			{
			case GL_FLOAT:
				return 4;
				break;
			case GL_UNSIGNED_INT:
				return 4;
				break;
			case GL_UNSIGNED_BYTE:
				return 1;
				break;
			}
			ASSERT(false);
			return(0);
		}
	};

	class WTEngine_API VertexBufferLayout
	{
	public:
		VertexBufferLayout()
			: m_Stride(0) {}


		template<typename T>
		void Push(unsigned int count)
		{
			static_assert(false);
		}

		template<>
		void Push<float>(unsigned int count)
		{
			m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
			m_Stride += VertexBufferElement::GetTypeSize(GL_FLOAT) * count;
		}

		template<>
		void Push<unsigned int>(unsigned int count)
		{
			m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
			m_Stride += VertexBufferElement::GetTypeSize(GL_UNSIGNED_INT) * count;
		}

		template<>
		void Push<unsigned char>(unsigned int count)
		{
			m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
			m_Stride += VertexBufferElement::GetTypeSize(GL_UNSIGNED_BYTE) * count;
		}

		inline const std::vector<VertexBufferElement> GetElement() const { return m_Elements; }
		inline unsigned int GetStride() const { return m_Stride; }

	private:
		std::vector<VertexBufferElement> m_Elements;
		unsigned int m_Stride;
	};

}