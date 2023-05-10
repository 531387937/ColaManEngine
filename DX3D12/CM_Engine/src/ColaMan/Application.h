#pragma once

#include <wtypes.h>
#include "Core.h"

#include "Event/ApplicationEvent.h"
#include "Window.h"

namespace ColaMan {

	class CM_API Application
	{
	public:
		Application();
		Application(HINSTANCE hInstance);
		virtual ~Application();

		int Run(HINSTANCE hInstance);

		void OnEvent(Event& e);

	private:

		bool OnWindowClose(WindowCloseEvent& e);
		bool m_Running = true;
		std::unique_ptr<Window> m_Window;
	};

}
