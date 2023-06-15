#pragma once
#include "ColaMan/Window.h"
#include "Platform/DirectX12/DirectX12Context.h"
namespace ColaMan {

	static struct WindowData
	{
		using EventCallbackFn = std::function<void(Event&)>;
		wchar_t* Title = L" \0";
		unsigned int Width, Height;
		bool VSync;

		EventCallbackFn EventCallback;
	};

	class WindowsWindow :public Window
	{
	public:
		WindowsWindow(const WindowProps& props, HINSTANCE hInstance);
		virtual ~WindowsWindow();

		void NewFrame() override;
		void OnUpdate() override;
		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		inline void SetEventCallback(const EventCallbackFn& callback)override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync()const override;
		void* GetNativeWindow() const override;

	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		HWND m_Window;

		HINSTANCE mhAppInst = nullptr;
		WindowData m_Data;
		GraphicsContext* m_Context;
		
	};
}