#include "hzpch.h"
#include "DirectX12Context.h"
#include <ColaMan/DirectX12/ShapesApp.h>

namespace ColaMan {
	DirectX12Context::DirectX12Context(HWND window):m_Window(window)
	{
		
	}
	void DirectX12Context::Init() 
	{
		static ShapesApp theApp(m_Window);
		if (!theApp.Initialize())
			return;
	}
	void DirectX12Context::SwapBuffers()
	{
		static ShapesApp* app = (ShapesApp*)CMD3DApp::GetApp();
		app->ExcuteCommand();
	}
}