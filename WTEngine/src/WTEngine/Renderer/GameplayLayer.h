#pragma once
#include "WTEngine//Layers/Layer.h"
#include "WTEngine/Events/ApplicationEvent.h"


namespace WTF {

	class WTF_API GameplayLayer : public Layer
	{
	public:
		GameplayLayer();
		~GameplayLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnEvent(Event& event) override;

	private:
		bool OnRenderEvent(AppRenderEvent& e);
	};

}