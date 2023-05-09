#include "hzpch.h"
#include "Application.h"
#include "DirectX12/ShapesApp.h"

namespace ColaMan {

	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	int Application::Run(HINSTANCE hInstance)
	{
		try
		{
			ShapesApp theApp(hInstance);
			if (!theApp.Initialize())
				return 0;

			return theApp.Run();
		}
		catch (DxException& e)
		{
			MessageBox(nullptr, e.ToString().c_str(), L"HR Failed", MB_OK);
			return 0;
		}
	}
}

