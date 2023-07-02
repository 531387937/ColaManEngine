#include "hzpch.h"
#include "DirectX12_Map.h"

namespace ColaMan
{
	std::unordered_map<uint16_t, ComPtr<ID3D12PipelineState>> DirectX12Map::mPipelines;
	std::unordered_map<uint16_t, ComPtr<ID3D12RootSignature>> DirectX12Map::mRootSignatures;
	std::unordered_map<uint16_t, ComPtr<ID3D12DescriptorHeap>> DirectX12Map::mDescriptorHeaps;
	void DirectX12Map::AddPipelineState(uint16_t index, ComPtr<ID3D12PipelineState>& pipeline)
	{
		mPipelines[index] = std::move(pipeline);
	}
	void DirectX12Map::AddRootSignature(uint16_t index, ComPtr<ID3D12RootSignature>& rootSignature)
	{
		mRootSignatures[index] = std::move(rootSignature);
	}
	void DirectX12Map::AddDescriptorHeap(uint16_t index, ComPtr<ID3D12DescriptorHeap>& descriptor)
	{
		mDescriptorHeaps[index] = std::move(descriptor);
	}
	ID3D12PipelineState* DirectX12Map::GetPipeline(uint16_t index)
	{
		if (mPipelines[index])
		{
			return mPipelines[index].Get();
		}
		CM_CORE_ASSERT(false, "Can`t find the pipeline!");
		return nullptr;
	}
	ID3D12RootSignature* DirectX12Map::GetRootSignature(uint16_t index)
	{
		if (mRootSignatures[index])
		{
			return mRootSignatures[index].Get();
		}
		CM_CORE_ASSERT(false, "Can`t find the rootSignature!");
		return nullptr;
	}
	ID3D12DescriptorHeap* DirectX12Map::GetDescriptorHeap(uint16_t index)
	{
		if (mDescriptorHeaps[index])
		{
			return mDescriptorHeaps[index].Get();
		}
		CM_CORE_ASSERT(false, "Can`t find the descriptorHeap!");
		return nullptr;
	}
}