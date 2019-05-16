#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <sstream>


namespace WTF {

#define ASSERT(x) if (!(x)) __debugbreak(); //std::cin.ignore();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

	void GLClearError();
	bool GLLogCall(const char* function, const char* file, int line);
}