#include "wgepch.h"
#include "ImGuiLayer.h"

#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"

#include "WinterGE/Application.h"

// Temporary
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace WinterGE
{
	ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer")
	{
	}

	ImGuiLayer::~ImGuiLayer()
	{
	}

	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& IO = ImGui::GetIO();
		IO.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		IO.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach()
	{

	}

	void ImGuiLayer::OnUpdate()
	{
		// Set the display size to be the same as our window
		ImGuiIO& IO = ImGui::GetIO();
		Application& App = Application::Get();
		IO.DisplaySize = ImVec2(App.GetWindow().GetWidth(), App.GetWindow().GetHeight());

		float time = (float)glfwGetTime();
		IO.DeltaTime = m_Time > 0.0 ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool bShow = true;
		ImGui::ShowDemoWindow(&bShow);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(Event& Event)
	{
		// TODO: PROFILE THIS: I think a switch statement might be faster

		EventDispatcher Dispatcher(Event);
		Dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
		Dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
		Dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
		Dispatcher.Dispatch<MouseButtonReleasedEvent>(BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
		Dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
		Dispatcher.Dispatch<KeyReleasedEvent>(BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
		Dispatcher.Dispatch<KeyTypedEvent>(BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));
		Dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));
	}

// Private Functions

	bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& Event)
	{
		ImGuiIO& IO = ImGui::GetIO();
		IO.AddMousePosEvent(Event.GetX(), Event.GetY());

		return false;
	}

	bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& Event)
	{
		ImGuiIO& IO = ImGui::GetIO();
		IO.AddMouseWheelEvent(Event.GetXOffset(), Event.GetYOffset());

		return false;
	}

	bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& Event)
	{
		ImGuiIO& IO = ImGui::GetIO();
		IO.AddMouseButtonEvent(Event.GetMouseButton(), true);

		return false;
	}

	bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& Event)
	{
		ImGuiIO& IO = ImGui::GetIO();
		IO.AddMouseButtonEvent(Event.GetMouseButton(), false);

		return false;
	}

	bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& Event)
	{
		ImGuiIO& IO = ImGui::GetIO();
		IO.KeysDown[Event.GetKeyCode()] = true;

		IO.KeyCtrl = IO.KeysDown[GLFW_KEY_LEFT_CONTROL] || IO.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		IO.KeyShift = IO.KeysDown[GLFW_KEY_LEFT_SHIFT] || IO.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		IO.KeyAlt = IO.KeysDown[GLFW_KEY_LEFT_ALT] || IO.KeysDown[GLFW_KEY_RIGHT_ALT];
		IO.KeySuper = IO.KeysDown[GLFW_KEY_LEFT_SUPER] || IO.KeysDown[GLFW_KEY_RIGHT_SUPER];

		return false;
	}

	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& Event)
	{
		ImGuiIO& IO = ImGui::GetIO();
		IO.KeysDown[Event.GetKeyCode()] = false;

		return false;
	}

	bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& Event)
	{
		ImGuiIO& IO = ImGui::GetIO();
		int KeyCode = Event.GetKeyCode();
		if (KeyCode > 0 && KeyCode < 0x10000)
		{
			IO.AddInputCharacter((unsigned short)KeyCode);
		}

		return false;
	}

	bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& Event)
	{
		ImGuiIO& IO = ImGui::GetIO();
		IO.DisplaySize = ImVec2(Event.GetWidth(), Event.GetHeight());
		IO.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, Event.GetWidth(), Event.GetHeight());

		return false;
	}
}