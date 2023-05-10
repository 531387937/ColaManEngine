#pragma once
#include "ColaMan/Window.h"
namespace ColaMan {
	class WindowsWindow :public Window
	{
	public:
		WindowsWindow(const WindowProps& props, HINSTANCE hInstance);
		virtual ~WindowsWindow();

		void OnUpdate() override
		{

		}

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		inline void SetEventCallback(const EventCallbackFn& callback)override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync()const override;
		HWND GetWindow() const override;
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		HWND m_Window;

		struct WindowData
		{
			wchar_t* Title = nullptr;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		HINSTANCE mhAppInst = nullptr;
		WindowData m_Data;
	};
}