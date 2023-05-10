#include <wtypes.h>
#include "ColaMan.h"

class Sandbox :public ColaMan::Application
{
public:
	Sandbox()
	{

	}
	Sandbox(HINSTANCE hInstance) :Application(hInstance) {

	}
	~Sandbox()
	{

	}

};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE preInstance, PSTR cmdLine, int showCmd)
{
	AllocConsole();

	ColaMan::Log::Init();
	CM_CORE_WARN("Initialized log!");
	CM_TRACE("Hello!");
	Sandbox *app = new Sandbox(hInstance);
	ColaMan::WindowResizeEvent e(1280, 720);
	CM_TRACE(e);
	return app->Run(hInstance);
}