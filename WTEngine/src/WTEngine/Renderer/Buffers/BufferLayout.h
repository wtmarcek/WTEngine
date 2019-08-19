#pragma once

#include "wtfpch.h"
#include "WTEngine/Renderer/Shaders/ShaderDataType.h"

#include <stdint.h>

using namespace std;
namespace WTF
{

	struct BufferElement
	{
	public:
		string name;
		ShaderDataType type;
		uint32_t offset;
		uint32_t size;
		bool isNormalized;

		BufferElement() {}

		BufferElement(ShaderDataType type, const string& name, bool isNormalized = false)
			:name(name), type(type), offset(0), isNormalized(isNormalized)
		{
			size = type.GetSize();
		}		
	};

	class BufferLayout
	{
	public:
		BufferLayout() {}

		BufferLayout(const initializer_list<BufferElement>& elements)
		: elements(elements) 
		{
			uint32_t offset = 0;
			stride = 0;
			for (auto& element : this->elements)
			{
				element.offset = offset;
				offset += element.size;				
				stride += element.size;
			}
		}

		inline const vector<BufferElement>& GetElements() const { return elements; }
		inline uint32_t GetStride() const { return stride; }

		vector<BufferElement>::iterator begin() { return elements.begin(); };
		vector<BufferElement>::iterator end() { return elements.end(); };

	private:
		vector<BufferElement> elements;
		uint32_t stride;

	};
}