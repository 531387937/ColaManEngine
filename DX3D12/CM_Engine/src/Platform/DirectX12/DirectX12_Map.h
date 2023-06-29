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
		inline static void AddPipelineState(uint16_t index, ComPtr<ID3D12PipelineState> pipeline)
		{
			mPipelines[index] = pipeline;
		}
		inline static void AddRootSignature(uint16_t index, ComPtr<ID3D12RootSignature> rootSignature)
		{
			mRootSignatures[index] = rootSignature;
		}
		inline static ID3D12PipelineState* GetPipeline(uint16_t index)
		{
			if (mPipelines[index])
			{
				return mPipelines[index].Get();
			}
			CM_CORE_ASSERT(false, "Can`t find the pipeline");
			return nullptr;
		}
		inline static ID3D12RootSignature* GetRootSignature(uint16_t index)
		{
			if (mRootSignatures[index])
			{
				return mRootSignatures[index].Get();
			}
			CM_CORE_ASSERT(false, "Can`t find the rootSignature");
			return nullptr;
		}
	private:
		static std::unordered_map<uint16_t, ComPtr<ID3D12PipelineState>> mPipelines;
		static std::unordered_map<uint16_t, ComPtr<ID3D12RootSignature>> mRootSignatures;
	};
}