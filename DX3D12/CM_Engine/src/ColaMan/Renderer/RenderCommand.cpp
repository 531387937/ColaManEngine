#include "hzpch.h"
#include "RenderCommand.h"

#include "Platform/DirectX12/DirectX12RendererAPI.h"
namespace ColaMan
{
	RendererAPI* RenderCommand::s_RendererAPI = new DirectX12RendererAPI;
	void RenderCommand::SetClearColor(const DirectX::XMFLOAT4& color)
	{
		s_RendererAPI->SetClearColor(color);
	}
	void RenderCommand::Clear()
	{
		s_RendererAPI->Clear();
	}
	void RenderCommand::SetPipelineState(const uint16_t psoIndex)
	{
		s_RendererAPI->SetPipeline(psoIndex);
	}
	void RenderCommand::SetRootSignature(const uint16_t rootIndex)
	{
		s_RendererAPI->SetRootSignature(rootIndex);
	}
}