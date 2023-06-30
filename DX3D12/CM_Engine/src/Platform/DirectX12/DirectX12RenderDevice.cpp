#include "hzpch.h"
#include "DirectX12RenderDevice.h"
#include "ColaMan/DirectX12/DX12Core.h"
#include "DirectX12_Map.h"
namespace ColaMan
{

	void DirectX12RenderDevice::CreatePipeline(const std::shared_ptr<PipelineState>& pipelineState)
	{
		ComPtr<ID3D12PipelineState> pso;
		D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = pipelineState->GetD3D12GraphicsPipelineStateDesc();
		
		Dx12Core::GetDevice()->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(pso.GetAddressOf()));
		DirectX12Map::AddPipelineState(pipelineState->pipelineIndex, pso);
	}
	void DirectX12RenderDevice::CreateRootSignature(const std::shared_ptr<RootSignature>& rootSig)
	{
		ComPtr<ID3D12RootSignature> rootSignature = rootSig->GetD3D12RootSignature(Dx12Core::GetDevice());
		DirectX12Map::AddRootSignature(rootSig->rootSignatureIndex, rootSignature);
	}
}