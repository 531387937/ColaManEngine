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
	Application::Application(HINSTANCE hInstance)
	{
		m_Window = std::unique_ptr<Window>(Window::Create(hInstance));
	}
	int Application::Run(HINSTANCE hInstance)
	{
		try
		{
			ShapesApp theApp(m_Window->GetWindow());
			if (!theApp.Initialize())
				return 0;
			MSG msg = { 0 };


			while (msg.message != WM_QUIT)
			{
				if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				theApp.Run();
			}
			return (int)msg.wParam;
			
		}
		catch (DxException& e)
		{
			MessageBox(nullptr, e.ToString().c_str(), L"HR Failed", MB_OK);
			return 0;
		}
	}
}

