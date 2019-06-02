#pragma once

#include "WTEngine/Layers/Layer.h"

#include "WTEngine/Events/MouseEvent.h"
#include "WTEngine/Events/KeyEvent.h"
#include "WTEngine/Events/ApplicationEvent.h"


namespace WTF {

	class WTF_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;

		void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;

	};

}