#include "hzpch.h"
#include "ColaMan/Log.h"
#include "WindowsWindow.h"
#include <stdlib.h>
namespace ColaMan {
	LRESULT CALLBACK
		MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		// Forward hwnd on because we can get messages (e.g., WM_CREATE)
		// before CreateWindow returns, and thus before mhMainWnd is valid.
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	static bool s_WindowInitialized = false;

	Window* Window::Create(HINSTANCE hInstance, const WindowProps& props)
	{
		return new WindowsWindow(props,hInstance);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props, HINSTANCE hInstance):mhAppInst(hInstance)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow() {
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		std::mbstowcs(m_Data.Title, props.Title.c_str(), props.Title.length() + 1);
		
		CM_CORE_INFO("Creating window {0} ({1},{2})", props.Title, props.Width, props.Height);


		WNDCLASS wc;
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = MainWndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = mhAppInst;
		wc.hIcon = LoadIcon(0, IDI_APPLICATION);
		wc.hCursor = LoadCursor(0, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
		wc.lpszMenuName = 0;
		wc.lpszClassName = L"MainWnd";

		if (!RegisterClass(&wc))
		{
			MessageBox(0, L"RegisterClass Failed", 0, 0);
			return;
		}

		RECT R{ 0,0,m_Data.Width,m_Data.Height };
		AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
		int width = R.right - R.left;
		int height = R.bottom - R.top;

		m_Window = CreateWindow(L"MainWnd", m_Data.Title, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, 0, 0, mhAppInst, 0);
		if (!m_Window)
		{
			MessageBox(0, L"CreateWindow Failed.", 0, 0);
			return;
		}

		ShowWindow(m_Window, SW_SHOW);
		UpdateWindow(m_Window);
	}

	void WindowsWindow::Shutdown()
	{
		DestroyWindow(m_Window);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}
	HWND WindowsWindow::GetWindow() const
	{
		return m_Window;
	}
}