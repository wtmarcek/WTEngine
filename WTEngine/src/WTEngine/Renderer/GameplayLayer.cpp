#include "wtfpch.h"
#include "GameplayLayer.h"

namespace WTF {

	GameplayLayer::GameplayLayer()
	{
	}


	GameplayLayer::~GameplayLayer()
	{
	}

	void GameplayLayer::OnAttach()
	{
	}

	void GameplayLayer::OnDetach()
	{
	}

	void GameplayLayer::OnUpdate()
	{
	}

	void GameplayLayer::OnEvent(Event & event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<AppRenderEvent>(WTF_BIND_EVENT_FN(GameplayLayer::OnRenderEvent));
	}

	bool GameplayLayer::OnRenderEvent(AppRenderEvent & e)
	{
		return false;
	}

}