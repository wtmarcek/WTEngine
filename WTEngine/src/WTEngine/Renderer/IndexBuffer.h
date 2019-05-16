#pragma once
#include "wtfpch.h"


namespace WTF {

	class WTF_API IndexBuffer
	{
	public:
		IndexBuffer(const unsigned int* data, unsigned int size);
		~IndexBuffer();

		void Bind() const;
		void Unbind() const;

		inline unsigned int GetCount() const { return m_Count; }

	private:
		unsigned int m_RendererID;
		unsigned int m_Count;
	};

}