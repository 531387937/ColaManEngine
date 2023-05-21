#include "hzpch.h"
#include "ColaMan/Log.h"
#include "WindowsWindow.h"
#include <windowsx.h>
#include "ColaMan/Event/ApplicationEvent.h"
#include "ColaMan/Event/MouseEvent.h"
#include "ColaMan/Event/KeyEvent.h"
#include <stdlib.h>
namespace ColaMan {
	static bool s_WindowInitialized = false;
	LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		//ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam);
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
				{
					MouseButtonPressedEvent mousePressedEvent(0);
					pData->EventCallback(mousePressedEvent);
					return 0;
					break;
				}
				case WM_MBUTTONDOWN:
				{
					MouseButtonPressedEvent mousePressedEvent(2);
					pData->EventCallback(mousePressedEvent);
					return 0;
					break;
				}
				case WM_RBUTTONDOWN:
				{
					MouseButtonPressedEvent mousePressedEvent(1);
					pData->EventCallback(mousePressedEvent);
					return 0;
					break;
				}
				case WM_LBUTTONUP:
				{
					MouseButtonReleasedEvent mouseReleasedEvent(0);
					pData->EventCallback(mouseReleasedEvent);
					return 0;
					break;
				}
				case WM_MBUTTONUP:
				{
					MouseButtonReleasedEvent mouseReleasedEvent(2);
					pData->EventCallback(mouseReleasedEvent);
					return 0;
					break;
				}
				case WM_RBUTTONUP:
				{
					MouseButtonReleasedEvent mouseReleasedEvent(1);
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
					MouseScrolledEvent mouseScrolledEvent(0, (float)GET_WHEEL_DELTA_WPARAM(wParam) / (float)WHEEL_DELTA);
					pData->EventCallback(mouseScrolledEvent);
					return 0;
					break;
				}
				case WM_MOUSEHWHEEL:
				{
					MouseScrolledEvent mouseScrolledEvent((float)GET_WHEEL_DELTA_WPARAM(wParam) / (float)WHEEL_DELTA, 0);
					pData->EventCallback(mouseScrolledEvent);
					return 0;
					break;
				}
				case WM_CHAR:
				{
					KeyTypedEvent keyTypeEvent(wParam);
					pData->EventCallback(keyTypeEvent);
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
	void WindowsWindow::OnUpdate()
	{
		static MSG msg = { 0 };
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (msg.message == WM_QUIT)
		{

		}
		m_Context->SwapBuffers();
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
		m_Context = new DirectX12Context(m_Window);
		m_Context->Init();

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
	void* WindowsWindow::GetNativeWindow() const
	{
		return m_Window;
	}
}