#pragma once

namespace WTF
{
	class GraphicsContext
	{
	public:
		virtual void Initialize() = 0;
		virtual void SwapBuffers() = 0;
	};
}