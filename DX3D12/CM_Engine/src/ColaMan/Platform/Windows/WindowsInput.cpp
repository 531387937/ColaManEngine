#include "hzpch.h"
#include "WindowsInput.h"
#include "ColaMan/Application.h"

namespace ColaMan
{
	Input* Input::s_Instance = new WindowsInput();
	WindowsInput::WindowsInput()
	{
		
	}
	WindowsInput::~WindowsInput()
	{
	}
	bool WindowsInput::IsKeyPressedImpl(int keyCode)
	{
		auto window = static_cast<HWND>(Application::Instance->GetWindow().GetNativeWindow());
		if (window == GetActiveWindow())
		{
			short state = GetAsyncKeyState(keyCode);
			return state & 0x8000 || state & 0x0001;
		}
		return false;
	}
	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<HWND>(Application::Instance->GetWindow().GetNativeWindow());
		if (window == GetActiveWindow())
		{
			short state = GetAsyncKeyState(button);
			return state & 0x8000 || state & 0x0001;
		}
		return false;
	}
	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		auto window = static_cast<HWND>(Application::Instance->GetWindow().GetNativeWindow());
		if (window == GetActiveWindow())
		{
			LPPOINT point = new POINT();
			GetCursorPos(point);
			return { (float)point->x,(float)point->y };
		}
		return { 0.0f,0.0f };
	}
	float WindowsInput::GetMouseXImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return x;
	}
	float WindowsInput::GetMouseYImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return y;
	}
}