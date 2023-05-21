#pragma once
#include "ColaMan/Input.h"
namespace ColaMan
{
	class WindowsInput :public Input
	{
	public:
		WindowsInput();
		~WindowsInput();
	protected:
		virtual bool IsKeyPressedImpl(int keyCode) override;
		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual std::pair<float, float> GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	};
}