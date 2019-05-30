#pragma once

#include "WTEngine/Input/Input.h"

namespace WTF
{
	class WindowsInput : public Input
	{
	protected:
		bool IsKeyPressedImpl(int keycode) const override;
		bool IsMouseButtonPressedImpl(int button) const override;
		std::pair<float, float> GetMousePositionImpl() const override;
		float GetMouseXImpl() const override;
		float GetMouseYImpl() const override;
	};
}