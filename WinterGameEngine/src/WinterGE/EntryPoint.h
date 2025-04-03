#pragma once

#ifdef WGE_PLATFORM_WINDOWS

extern WinterGE::Application* WinterGE::CreateApplication();

int main(int argc, char** argv)
{
	auto App = WinterGE::CreateApplication();
	App->Run();
	delete App;
}

#else
#error Winter Game Engine only supports Windows!
#endif