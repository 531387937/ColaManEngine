#pragma once

namespace ColaMan {
	enum class RendererAPI
	{
		None = 0,DX12 = 1
	};

	class Renderer {
	public:
		inline static RendererAPI GetAPI() { return s_RendererAPI; }
	private:
		static RendererAPI s_RendererAPI;
	};
}