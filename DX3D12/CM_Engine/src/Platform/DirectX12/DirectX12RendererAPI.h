#pragma once
#include "ColaMan/Renderer/RendererAPI.h"
namespace ColaMan
{
	class DirectX12RendererAPI : public RendererAPI
	{
		// ͨ�� RendererAPI �̳�
		virtual void SetClearColor(const DirectX::XMFLOAT4& color) override;
		virtual void Clear() override;
		virtual void DrawIndexed(const std::shared_ptr<VertexBuffer>& vertexBuffer, const std::shared_ptr<IndexBuffer>& IndexBuffer) override;
	};
}


