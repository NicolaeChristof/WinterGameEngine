#pragma once

#include "WinterGE/Core.h"
#include "Layer.h"

#include <vector>

namespace WinterGE
{
	class WGE_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* Layer);
		void PopLayer(Layer* Layer);
		void PushOverlay(Layer* Overlay);
		void PopOverlay(Layer* Overlay);

		std::vector<Layer*>::iterator begin()
		{
			return m_Layers.begin();
		}

		std::vector<Layer*>::iterator end()
		{
			return m_Layers.end();
		}

	private:
		std::vector<Layer*> m_Layers;
		std::vector<Layer*>::iterator m_LayerInsert;
	};
}