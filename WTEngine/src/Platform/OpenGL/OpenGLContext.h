#pragma once

#include "WTEngine/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace WTF
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* glfwWindow);

		void Initialize() override;
		void SwapBuffers() override;

	private:
		GLFWwindow* glfwWindow;

	};
}