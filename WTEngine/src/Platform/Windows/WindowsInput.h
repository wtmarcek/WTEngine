#pragma once

#include "WTEngine/Input/Input.h"

namespace WTF
{
	class WindowsInput : public Input
	{
	protected:
		bool IsKeyPressedImpl(int keycode) const override;
		bool IsMouseButtonPressedImpl(int button) const override;
		glm::vec2 GetMousePositionImpl() const override;
		float GetMouseXImpl() const override;
		float GetMouseYImpl() const override;
	};
}