#pragma once

#include "WinterGE/Layers/Layer.h"

namespace WinterGE
{
	class WGE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnEvent(Event& Event) override;

	private:
		float m_Time = 0;
	};
}