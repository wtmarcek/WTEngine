#pragma once

#include <stdint.h>

namespace WTF
{
	enum DataType
	{
		xFloat,
		xInt,
		xBool,
		xMat3x3,
		xMat4x4
	};

	struct ShaderDataType
	{
	public:

		ShaderDataType() {}

		ShaderDataType(uint32_t size, uint32_t componentCount, DataType dataType)
			:size(size), componentCount(componentCount), dataType(dataType) {}

		uint32_t GetSize() const { return size; }
		uint32_t GetComponentCount() const { return componentCount; }
		unsigned int ConvertToGLEnum() const;

	private:
		uint32_t size;
		uint32_t componentCount;
		DataType dataType;		
	};

	//Bool
	static ShaderDataType Bool(1, 1, DataType::xBool);

	//Int
	static ShaderDataType Int(4, 1, DataType::xInt);
	static ShaderDataType Int2(4 * 2, 2, DataType::xInt);
	static ShaderDataType Int3(4 * 3, 3, DataType::xInt);
	static ShaderDataType Int4(4 * 4, 4, DataType::xInt);

	//Float
	static ShaderDataType Float(4, 1, DataType::xFloat);
	static ShaderDataType Float2(4 * 2, 2, DataType::xFloat);
	static ShaderDataType Float3(4 * 3, 3, DataType::xFloat);
	static ShaderDataType Float4(4 * 4, 4, DataType::xFloat);

	//Matrix
	static ShaderDataType Mat3x3(4 * 3 * 3, 3 * 3, DataType::xMat3x3);
	static ShaderDataType Mat4x4(4 * 4 * 4, 4 * 4, DataType::xMat4x4);
}