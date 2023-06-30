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
}