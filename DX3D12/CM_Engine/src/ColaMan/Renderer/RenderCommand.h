#pragma once
#include "RendererAPI.h"
#include "PipelineState.h"
namespace ColaMan
{
	class RenderCommand {
	public:
		static void SetClearColor(const DirectX::XMFLOAT4& color);
		static void Clear();
		static void SetPipelineState(const uint16_t psoIndex);
		static void SetRootSignature(const uint16_t rootIndex);
		inline static void DrawIndexed(const std::shared_ptr<VertexBuffer>& vertexBuffer, const std::shared_ptr<IndexBuffer>& indexBuffer)
		{
			s_RendererAPI->DrawIndexed(vertexBuffer, indexBuffer);
		}
	private:
		static RendererAPI* s_RendererAPI;
	};
}