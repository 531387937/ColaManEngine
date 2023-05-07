#include <wtypes.h>
#include "ColaMan.h"

class Sandbox :public ColaMan::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}

};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE preInstance, PSTR cmdLine, int showCmd)
{
	Sandbox *app = new Sandbox();
	return app->Run(hInstance);
}