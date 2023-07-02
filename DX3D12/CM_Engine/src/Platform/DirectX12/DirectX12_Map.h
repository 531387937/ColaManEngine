#pragma once
#include "ColaMan.h"
#include <unordered_map>
#include <d3d12.h>
#include <wrl.h>
namespace ColaMan
{
	using namespace Microsoft::WRL;
	class DirectX12Map
	{
	public:
		static void AddPipelineState(uint16_t index, ComPtr<ID3D12PipelineState>& pipeline);
		static void AddRootSignature(uint16_t index, ComPtr<ID3D12RootSignature>& rootSignature);
		static void AddDescriptorHeap(uint16_t index, ComPtr<ID3D12DescriptorHeap>& descriptor);
		static ID3D12PipelineState* GetPipeline(uint16_t index);
		static ID3D12RootSignature* GetRootSignature(uint16_t index);
		static ID3D12DescriptorHeap* GetDescriptorHeap(uint16_t index);
	private:
		static std::unordered_map<uint16_t, ComPtr<ID3D12PipelineState>> mPipelines;
		static std::unordered_map<uint16_t, ComPtr<ID3D12RootSignature>> mRootSignatures;
		static std::unordered_map<uint16_t, ComPtr<ID3D12DescriptorHeap>> mDescriptorHeaps;
	};
}