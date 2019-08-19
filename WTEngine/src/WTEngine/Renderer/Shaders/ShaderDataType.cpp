#include "wtfpch.h"
#include "ShaderDataType.h"

#include <glad/glad.h>

unsigned int WTF::ShaderDataType::ConvertToGLEnum() const
{
	switch (dataType)
	{
		case DataType::xFloat:		return GL_FLOAT;
		case DataType::xInt:		return GL_INT;
		case DataType::xBool:		return GL_BOOL;
		case DataType::xMat3x3:		return GL_FLOAT;
		case DataType::xMat4x4:		return GL_FLOAT;
	}

	WTF_CORE_ASSERT(false, "Unknown ShaderDataType!");
	return 0;
}
