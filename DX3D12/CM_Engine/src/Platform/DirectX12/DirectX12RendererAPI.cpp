#include "hzpch.h"
#include "DirectX12RendererAPI.h"
#include "ColaMan/DirectX12/DX12Core.h"

void ColaMan::DirectX12RendererAPI::SetClearColor(const DirectX::XMFLOAT4& color)
{
	Dx12Core::GetDX12()->dxClearColor(color);
}

void ColaMan::DirectX12RendererAPI::Clear()
{
	Dx12Core::GetDX12()->Clear();
}

void ColaMan::DirectX12RendererAPI::DrawIndexed(const std::shared_ptr<VertexBuffer>& vertexBuffer, const std::shared_ptr<IndexBuffer>& IndexBuffer)
{
	IndexBuffer->Bind();
	Dx12Core::GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	vertexBuffer->Bind();
	Dx12Core::GetCommandList()->DrawIndexedInstanced(IndexBuffer->GetCount(), 1, 0, 0, 0);
}

void ColaMan::DirectX12RendererAPI::SetPipeline(const uint16_t psoIndex)
{
	Dx12Core::GetCommandList()->SetPipelineState(DirectX12Map::GetPipeline(psoIndex));
}

void ColaMan::DirectX12RendererAPI::SetRootSignature(const uint16_t rootSigIndex)
{
	Dx12Core::GetCommandList()->SetGraphicsRootSignature(DirectX12Map::GetRootSignature(rootSigIndex));
}
