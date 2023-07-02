#include "hzpch.h"
#include "DirectX12RenderDevice.h"
#include "ColaMan/DirectX12/DX12Core.h"
#include "DirectX12_Map.h"
namespace ColaMan
{

	void DirectX12RenderDevice::CreatePipeline(PipelineState* pipelineState)
	{
		ComPtr<ID3D12PipelineState> pso = pipelineState->GetD3D12GraphicsPipelineStateDesc(Dx12Core::GetDevice());
		
		//ThrowIfFailed(Dx12Core::GetDevice()->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(pso.GetAddressOf())));
		DirectX12Map::AddPipelineState(pipelineState->pipelineIndex, pso);
	}
	void DirectX12RenderDevice::CreateRootSignature(RootSignature* rootSig)
	{
		ComPtr<ID3D12RootSignature> rootSignature = rootSig->GetD3D12RootSignature(Dx12Core::GetDevice());
		DirectX12Map::AddRootSignature(rootSig->rootSignatureIndex, rootSignature);
	}
	void DirectX12RenderDevice::CreateDescriptorHeap(DescriptorHeap* descriptor)
	{
		ComPtr<ID3D12DescriptorHeap> descriptorHeap = descriptor->GetDX12DescriptorHeapDesc(Dx12Core::GetDevice());
		DirectX12Map::AddDescriptorHeap( descriptor->descriptorIndex, descriptorHeap);
	}
}