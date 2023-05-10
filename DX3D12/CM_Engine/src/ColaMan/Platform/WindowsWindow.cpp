#include "hzpch.h"
#include "ColaMan/Log.h"
#include "WindowsWindow.h"
#include <windowsx.h>
#include "../Event/ApplicationEvent.h"
#include "../Event/MouseEvent.h"
#include "../Event/KeyEvent.h"
#include <stdlib.h>
namespace ColaMan {

	static bool s_WindowInitialized = false;
	LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		static WindowData* pData = nullptr;
		switch (msg)
		{
			// 处理窗口消息...
		case WM_CREATE:
			pData = reinterpret_cast<WindowData*>(reinterpret_cast<LPCREATESTRUCT>(lParam)->lpCreateParams);
			return 0;
			break;
		}
		if (pData != nullptr && pData->EventCallback)
		{
			switch (msg)
			{
				case WM_SIZE:
				{

					WindowResizeEvent resizeEvent(LOWORD(lParam), HIWORD(lParam));
					//CM_CORE_INFO(even);
					pData->Height = HIWORD(lParam);
					pData->Width = LOWORD(lParam);
					pData->EventCallback(resizeEvent);
					return 0;
					break;
				}
				case WM_CLOSE:
				{
					WindowCloseEvent closeEvent;
					pData->EventCallback(closeEvent);
					return 0;
					break;
				}
				case WM_KEYDOWN:
				{
					KeyPressedEvent keyPressedEvent(wParam, false);
					pData->EventCallback(keyPressedEvent);
					return 0;
					break;
				}
				case WM_KEYUP:
				{
					KeyReleasedEvent keyReleasedEvent(wParam);
					pData->EventCallback(keyReleasedEvent);
					return 0;
					break;
				}
				case WM_KEYLAST:
				{
					KeyPressedEvent keyPressedEvent(wParam, true);
					pData->EventCallback(keyPressedEvent);
					return 0;
					break;
				}
				case WM_LBUTTONDOWN:
				case WM_MBUTTONDOWN:
				case WM_RBUTTONDOWN:
				{
					MouseButtonPressedEvent mousePressedEvent(wParam);
					pData->EventCallback(mousePressedEvent);
					return 0;
					break;
				}
				case WM_LBUTTONUP:
				case WM_MBUTTONUP:
				case WM_RBUTTONUP:
				{
					MouseButtonReleasedEvent mouseReleasedEvent(wParam);
					pData->EventCallback(mouseReleasedEvent);
					return 0;
					break;
				}
				case WM_MOUSEMOVE:
				{
					MouseMovedEvent mouseMovedEvent(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
					pData->EventCallback(mouseMovedEvent);
					return 0;
					break;
				}
				case WM_MOUSEWHEEL:
				{
					MouseScrolledEvent mouseScrolledEvent(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
					pData->EventCallback(mouseScrolledEvent);
					return 0;
					break;
				}
			}
		}

		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	Window* Window::Create(HINSTANCE hInstance, const WindowProps& props)
	{
		return new WindowsWindow(props, hInstance);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props, HINSTANCE hInstance) :mhAppInst(hInstance)
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

		size_t length = std::mbstowcs(nullptr, props.Title.c_str(), 0);

		m_Data.Title = new wchar_t[length + 1];
		std::mbstowcs(m_Data.Title, props.Title.c_str(), length + 1);

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

		m_Window = CreateWindow(L"MainWnd", m_Data.Title, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, 0, 0, mhAppInst, &m_Data);
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