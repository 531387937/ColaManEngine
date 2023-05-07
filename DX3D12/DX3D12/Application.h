#pragma once

#include <wtypes.h>

namespace ColaMan {

	class __declspec(dllexport) Application 
	{
	public:
		Application();
		~Application();

		int Run(HINSTANCE hInstance);
	};

}
