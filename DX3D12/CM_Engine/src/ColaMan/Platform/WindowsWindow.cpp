#include "hzpch.h"
#include "ColaMan/Log.h"
#include "WindowsWindow.h"
#include <windowsx.h>
#include "../Event/ApplicationEvent.h"
#include "../Event/MouseEvent.h"
#include "../Event/KeyEvent.h"
#include <stdlib.h>
namespace ColaMan {
	//LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	//{
	//	if (ImGui::GetCurrentContext() == NULL)
	//		return 0;

	//	ImGuiIO& io = ImGui::GetIO();
	//	switch (msg)
	//	{
	//	case WM_LBUTTONDOWN: case WM_LBUTTONDBLCLK:
	//	case WM_RBUTTONDOWN: case WM_RBUTTONDBLCLK:
	//	case WM_MBUTTONDOWN: case WM_MBUTTONDBLCLK:
	//	case WM_XBUTTONDOWN: case WM_XBUTTONDBLCLK:
	//	{
	//		int button = 0;
	//		if (msg == WM_LBUTTONDOWN || msg == WM_LBUTTONDBLCLK) { button = 0; }
	//		if (msg == WM_RBUTTONDOWN || msg == WM_RBUTTONDBLCLK) { button = 1; }
	//		if (msg == WM_MBUTTONDOWN || msg == WM_MBUTTONDBLCLK) { button = 2; }
	//		if (msg == WM_XBUTTONDOWN || msg == WM_XBUTTONDBLCLK) { button = (GET_XBUTTON_WPARAM(wParam) == XBUTTON1) ? 3 : 4; }
	//		if (!ImGui::IsAnyMouseDown() && ::GetCapture() == NULL)
	//			::SetCapture(hwnd);
	//		io.MouseDown[button] = true;
	//		return 0;
	//	}
	//	case WM_LBUTTONUP:
	//	case WM_RBUTTONUP:
	//	case WM_MBUTTONUP:
	//	case WM_XBUTTONUP:
	//	{
	//		int button = 0;
	//		if (msg == WM_LBUTTONUP) { button = 0; }
	//		if (msg == WM_RBUTTONUP) { button = 1; }
	//		if (msg == WM_MBUTTONUP) { button = 2; }
	//		if (msg == WM_XBUTTONUP) { button = (GET_XBUTTON_WPARAM(wParam) == XBUTTON1) ? 3 : 4; }
	//		io.MouseDown[button] = false;
	//		if (!ImGui::IsAnyMouseDown() && ::GetCapture() == hwnd)
	//			::ReleaseCapture();
	//		return 0;
	//	}
	//	case WM_MOUSEWHEEL:
	//		io.MouseWheel += (float)GET_WHEEL_DELTA_WPARAM(wParam) / (float)WHEEL_DELTA;
	//		return 0;
	//	case WM_MOUSEHWHEEL:
	//		io.MouseWheelH += (float)GET_WHEEL_DELTA_WPARAM(wParam) / (float)WHEEL_DELTA;
	//		return 0;
	//	case WM_KEYDOWN:
	//	case WM_SYSKEYDOWN:
	//		if (wParam < 256)
	//			io.KeysDown[wParam] = 1;
	//		return 0;
	//	case WM_KEYUP:
	//	case WM_SYSKEYUP:
	//		if (wParam < 256)
	//			io.KeysDown[wParam] = 0;
	//		return 0;
	//	case WM_CHAR:
	//		// You can also use ToAscii()+GetKeyboardState() to retrieve characters.
	//		if (wParam > 0 && wParam < 0x10000)
	//			io.AddInputCharacterUTF16((unsigned short)wParam);
	//		return 0;
	//	case WM_SETCURSOR:
	//		if (LOWORD(lParam) == HTCLIENT && ImGui_ImplWin32_UpdateMouseCursor())
	//			return 1;
	//		return 0;
	//	case WM_DEVICECHANGE:
	//		if ((UINT)wParam == DBT_DEVNODES_CHANGED)
	//			g_WantUpdateHasGamepad = true;
	//		return 0;
	//	case WM_DISPLAYCHANGE:
	//		g_WantUpdateMonitors = true;
	//		return 0;
	//	}
	//	return 0;
	//}
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