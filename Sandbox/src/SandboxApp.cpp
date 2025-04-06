#include <WinterGE.h>

class ExampleLayer : public WinterGE::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{
	}

	void OnUpdate() override
	{
		LOG_INFO("ExampleLayer::Update");
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
	}

	~Sandbox()
	{

	}
};

WinterGE::Application* WinterGE::CreateApplication()
{
	return new Sandbox();
}