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

	WTF_CORE_INFO("OpenGL Renderer: {0} {1}", glGetString(GL_VENDOR), glGetString(GL_RENDERER));
}

void WTF::OpenGLContext::SwapBuffers()
{
	glfwSwapBuffers(glfwWindow);
}
