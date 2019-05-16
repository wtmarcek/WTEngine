#pragma once
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "WTEngine/Shaders/Shader.h"

namespace WTF {

	class WTF_API Renderer
	{
	public:
		void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
		void Clear() const;
	};

}