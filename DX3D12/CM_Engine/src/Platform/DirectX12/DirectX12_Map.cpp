#include "hzpch.h"
#include "DirectX12_Map.h"

namespace ColaMan
{
	std::unordered_map<uint16_t, ComPtr<ID3D12PipelineState>> DirectX12Map::mPipelines;
	std::unordered_map<uint16_t, ComPtr<ID3D12RootSignature>> DirectX12Map::mRootSignatures;
}