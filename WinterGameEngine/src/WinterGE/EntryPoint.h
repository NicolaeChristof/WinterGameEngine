#pragma once

#ifdef WGE_PLATFORM_WINDOWS

extern WinterGE::Application* WinterGE::CreateApplication();

int main(int argc, char** argv)
{
	WinterGE::Log::Init();

	WinterGE::Application* App = WinterGE::CreateApplication();
	App->Run();

	delete App;
}

#else
#error Winter Game Engine only supports Windows!
#endif