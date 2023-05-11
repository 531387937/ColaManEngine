#include "hzpch.h"
#include "Application.h"
#include "DirectX12/ShapesApp.h"

namespace ColaMan {
#define BIND_EVENT_FN(x) std::bind(&Application::x,this,std::placeholders::_1)
	Application::Application()
	{
	}

	Application::~Application()
	{
	}
	Application::Application(HINSTANCE hInstance)
	{
		m_Window = std::unique_ptr<Window>(Window::Create(hInstance));
		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		CM_CORE_INFO("{0}",e);
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.m_Handled)
				break;
		}
	}
	
	int Application::Run(HINSTANCE hInstance)
	{
		try
		{
			ShapesApp theApp(m_Window->GetWindow());
			if (!theApp.Initialize())
				return 0;

			while (m_Running)
			{
				for (Layer* layer : m_LayerStack)
				{
					layer->OnUpdate();
				}
				theApp.Run();
				m_Window->OnUpdate();
			}
			return 0;
			
		}
		catch (DxException& e)
		{
			MessageBox(nullptr, e.ToString().c_str(), L"HR Failed", MB_OK);
			return 0;
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}
}

