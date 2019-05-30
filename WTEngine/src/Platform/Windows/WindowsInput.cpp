#include "wtfpch.h"
#include "WindowsInput.h"

#include <GLFW/glfw3.h>
#include <WTEngine/Application.h>

namespace WTF
{
	Input* Input::instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(int keycode) const
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		int state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button) const
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		int state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	std::pair<float, float> WindowsInput::GetMousePositionImpl() const
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double posX, posY;
		glfwGetCursorPos(window, &posX, &posY);		
		return std::make_pair((float)posX, (float)posY);;
	}

	float WindowsInput::GetMouseXImpl() const
	{
		return GetMousePosition().first;
	}

	float WindowsInput::GetMouseYImpl() const
	{
		return GetMousePosition().second;
	}
}