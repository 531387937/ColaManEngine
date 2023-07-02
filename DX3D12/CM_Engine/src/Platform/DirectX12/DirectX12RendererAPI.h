#pragma once
#include "ColaMan/Renderer/RendererAPI.h"
namespace ColaMan
{
	class DirectX12RendererAPI : public RendererAPI
	{
		// Í¨¹ý RendererAPI ¼Ì³Ð
		virtual void SetClearColor(const DirectX::XMFLOAT4& color) override;
		virtual void Clear() override;
		virtual void DrawIndexed(const std::shared_ptr<VertexBuffer>& vertexBuffer, const std::shared_ptr<IndexBuffer>& IndexBuffer) override;
		virtual void SetPipeline(const uint16_t psoIndex) override;
		virtual void SetRootSignature(const uint16_t rootSigIndex) override;
	};
}


