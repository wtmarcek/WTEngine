#pragma once

#include "WTEngine/Core.h"
#include <glm/glm.hpp>

namespace WTF 
{
	class WTF_API Input
	{
	public:
		inline static bool IsKeyPressed(int keycode) { return instance->IsKeyPressedImpl(keycode); }
		inline static bool IsMouseButtonPressed(int button) { return instance->IsMouseButtonPressedImpl(button); }
		inline static glm::vec2 GetMousePosition() { return instance->GetMousePositionImpl(); }
		inline static float GetMouseX() { return instance->GetMouseX(); }
		inline static float GetMouseY() { return instance->GetMouseY(); }

	protected:
		virtual bool IsKeyPressedImpl(int keycode) const = 0;
		virtual bool IsMouseButtonPressedImpl(int button) const = 0;
		virtual glm::vec2 GetMousePositionImpl() const = 0;
		virtual float GetMouseXImpl() const = 0;
		virtual float GetMouseYImpl() const = 0;
	
	private:
		static Input* instance;		
	};
}