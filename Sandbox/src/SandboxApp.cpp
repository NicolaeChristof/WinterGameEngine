#include <WinterGE.h>

class ExampleLayer : public WinterGE::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{
	}

	void OnAttach() override
	{
	}

	void OnDetach() override
	{
	}

	void OnUpdate() override
	{
	}

	void OnEvent(WinterGE::Event& Event) override
	{
		LOG_TRACE("{0}", Event.ToString());
	}
};

class Sandbox : public WinterGE::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new WinterGE::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

WinterGE::Application* WinterGE::CreateApplication()
{
	return new Sandbox();
}