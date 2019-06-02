#include "wtfpch.h"
#include "LayerStack.h"



WTF::LayerStack::LayerStack() { }

WTF::LayerStack::~LayerStack()
{
	for (Layer* layer : layers)
	{
		delete layer;
	}
}

void WTF::LayerStack::PushLayer(Layer * layer)
{
	layers.emplace(layers.begin() + layerInsertIndex, layer);
	layerInsertIndex++;
}

void WTF::LayerStack::PushOverlay(Layer * overlay)
{
	layers.emplace_back(overlay);
}

void WTF::LayerStack::PopLayer(Layer * layer)
{
	auto iter = std::find(layers.begin(), layers.end(), layer);
	if (iter != layers.end())
	{
		layers.erase(iter);
		layerInsertIndex--;
	}
}

void WTF::LayerStack::PopOverlay(Layer * overlay)
{
	auto iter = std::find(layers.begin(), layers.end(), overlay);
	if (iter != layers.end())
	{
		layers.erase(iter);
	}
}
