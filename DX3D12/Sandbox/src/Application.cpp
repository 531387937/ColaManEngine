#include <wtypes.h>

namespace ColaMan {

	class __declspec(dllimport) Application
	{
	public:
		Application();
		~Application();

		int Run(HINSTANCE hInstance);
	};

}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE preInstance, PSTR cmdLine, int showCmd)
{
	ColaMan::Application app;
	return app.Run(hInstance);
}