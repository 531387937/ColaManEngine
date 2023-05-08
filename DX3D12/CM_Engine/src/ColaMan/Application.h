#pragma once

#include <wtypes.h>
#include "Core.h"

namespace ColaMan {

	class CM_API Application
	{
	public:
		Application();
		virtual ~Application();

		int Run(HINSTANCE hInstance);
	};

}
