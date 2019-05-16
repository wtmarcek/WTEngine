#pragma once
#include "wtfpch.h"

#include "OpenGLDebug.h"
#include <iostream>



void WTF::GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool WTF::GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "OpenGL Error: " << "(" << error << "): " << function << " " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}

