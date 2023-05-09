#pragma once

#include <wtypes.h>
#include "Core.h"
#include "Window.h"

namespace ColaMan {

	class CM_API Application
	{
	public:
		Application();
		virtual ~Application();

		int Run(HINSTANCE hInstance);

	private:
		std::unique_ptr<Window> m_Window;
	};

}
