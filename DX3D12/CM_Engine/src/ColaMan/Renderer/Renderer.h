#pragma once
#include "RenderCommand.h"

namespace ColaMan {
	
	class Renderer {
	public:
		static void BeginFrame();
		static void EndFrame();

		static void Submit(const std::shared_ptr<VertexBuffer>& vertexBuffer, const std::shared_ptr<IndexBuffer>& indexBuffer);
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};
}