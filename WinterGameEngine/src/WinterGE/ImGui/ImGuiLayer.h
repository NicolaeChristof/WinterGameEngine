#pragma once

#include "WinterGE/Layers/Layer.h"

#include "WinterGE/Events/MouseEvent.h"
#include "WinterGE/Events/KeyEvent.h"
#include "WinterGE/Events/ApplicationEvent.h"

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
		bool OnMouseMovedEvent(MouseMovedEvent& Event);
		bool OnMouseScrolledEvent(MouseScrolledEvent& Event);
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& Event);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& Event);

		bool OnKeyPressedEvent(KeyPressedEvent& Event);
		bool OnKeyReleasedEvent(KeyReleasedEvent& Event);
		bool OnKeyTypedEvent(KeyTypedEvent& Event);

		bool OnWindowResizeEvent(WindowResizeEvent& Event);

		float m_Time = 0;
	};
}