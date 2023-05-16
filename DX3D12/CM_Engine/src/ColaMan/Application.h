#pragma once

#include <wtypes.h>
#include "Core.h"
#include "ColaMan/LayerStack.h"
#include "Event/ApplicationEvent.h"
#include "ColaMan/ImGui/ImGuiLayer.h"
#include "Window.h"

namespace ColaMan {

	class CM_API Application
	{
	public:

		Application();
		Application(HINSTANCE hInstance);

		static Application* Instance;
		virtual ~Application();

		int Run(HINSTANCE hInstance);

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() { return *m_Window; }
	private:

		bool OnWindowClose(WindowCloseEvent& e);
		bool m_Running = true;
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_LayerStack;
	};

}
