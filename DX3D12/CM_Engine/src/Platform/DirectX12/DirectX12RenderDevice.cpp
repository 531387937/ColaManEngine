#include "hzpch.h"
#include "DirectX12RenderDevice.h"
#include "ColaMan/DirectX12/DX12Core.h"
#include "DirectX12_Map.h"
namespace ColaMan
{

	void DirectX12RenderDevice::CreatePipeline(const std::shared_ptr<PipelineState>& pipelineState)
	{

		//Dx12Core::GetDevice()->CreateGraphicsPipelineState()
		ComPtr<ID3D12PipelineState> pso;

		D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc;
		ZeroMemory(&psoDesc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
		psoDesc.VS = pipelineState->vertexShader.Bound();
		psoDesc.PS = pipelineState->pixelShader.Bound();

		DirectX12Map::AddPipelineState(pipelineState->pipelineIndex, pso);
	}
	void DirectX12RenderDevice::CreateRootSignature(const std::shared_ptr<RootSignature>& rootSig)
	{
		ComPtr <ID3D12RootSignature> rootSignature;
		DirectX12Map::AddRootSignature(rootSig->rootSignatureIndex, rootSignature);
	}
}