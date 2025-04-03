#include <WinterGE.h>

class Sandbox : public WinterGE::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

WinterGE::Application* WinterGE::CreateApplication()
{
	return new Sandbox();
}