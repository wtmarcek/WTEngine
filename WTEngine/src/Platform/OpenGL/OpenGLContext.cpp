#pragma once

#include "wtfpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>


WTF::OpenGLContext::OpenGLContext(GLFWwindow* glfwWindow)
	: glfwWindow(glfwWindow) 
{
	WTF_CORE_ASSERT(glfwWindow, "Window is null!");
}

void WTF::OpenGLContext::Initialize()
{
	glfwMakeContextCurrent(glfwWindow);
	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	WTF_CORE_ASSERT(status, "Failed to initialize Glad!");
}

void WTF::OpenGLContext::SwapBuffers()
{
	glfwSwapBuffers(glfwWindow);
}
