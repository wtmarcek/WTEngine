#pragma once

#include "Core.h"

namespace WTF {

	class WTEngine_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};
	Application* CreateApplication();
}