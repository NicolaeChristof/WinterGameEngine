#include "wgepch.h"
#include "LayerStack.h"

namespace WinterGE
{
	LayerStack::LayerStack()
	{
		m_LayerInsert = m_Layers.begin();
	}

	LayerStack::~LayerStack()
	{
		for (Layer* Layer : m_Layers)
		{
			delete Layer;
		}
	}

	void LayerStack::PushLayer(Layer* Layer)
	{
		m_LayerInsert = m_Layers.emplace(m_LayerInsert, Layer);
	}

	void LayerStack::PopLayer(Layer* Layer)
	{
		auto Iter = std::find(m_Layers.begin(), m_Layers.end(), Layer);
		if (Iter != m_Layers.end())
		{
			m_Layers.erase(Iter);
			--m_LayerInsert;
		}
	}

	void LayerStack::PushOverlay(Layer* Overlay)
	{
		m_Layers.emplace_back(Overlay);
	}

	void LayerStack::PopOverlay(Layer* Overlay)
	{
		auto Iter = std::find(m_Layers.begin(), m_Layers.end(), Overlay);
		if (Iter != m_Layers.end())
		{
			m_Layers.erase(Iter);
		}
	}
}