#pragma once

namespace ColaMan {
	class GraphicsContext
	{
	public:
		virtual void Init() = 0;
		virtual void newFrame() = 0;
		virtual void SwapBuffers() = 0;
	};
}