#pragma once
#include "RendererAPI.h"
namespace ColaMan
{
	class RenderCommand {
	public:
		static void SetClearColor(const DirectX::XMFLOAT4& color);
		static void Clear();
		inline static void DrawIndexed(const std::shared_ptr<VertexBuffer>& vertexBuffer, const std::shared_ptr<IndexBuffer>& indexBuffer)
		{
			s_RendererAPI->DrawIndexed(vertexBuffer, indexBuffer);
		}
	private:
		static RendererAPI* s_RendererAPI;
	};
}