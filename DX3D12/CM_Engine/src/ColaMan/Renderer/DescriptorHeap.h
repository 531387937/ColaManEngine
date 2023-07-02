#pragma once
#include "ColaMan.h"
#include "ColaMan/Core/RenderCode.h"
#include "Platform/DirectX12/CM2DX12.h"
namespace ColaMan
{
	class DescriptorHeap
	{
	public:

		ID3D12DescriptorHeap* DescriptorHeap::GetDX12DescriptorHeapDesc(ID3D12Device* device) const
		{
			D3D12_DESCRIPTOR_HEAP_DESC heapDesc;
			heapDesc.Type = GetDX12DescriptorHeapType(type);
			heapDesc.NumDescriptors = descriptorNum;
			heapDesc.Flags = GetDX12DescriptorHeapFlag(flags);
			heapDesc.NodeMask = NodeMask;

			ID3D12DescriptorHeap* heap;
			device->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&heap));
			return heap;
		}


		DescriptorHeap()
		{
			descriptorIndex = index;
			index++;
		}
		uint16_t descriptorIndex;

		DESCRIPTOR_HEAP_TYPE type;
		UINT descriptorNum;
		DESCRIPTOR_HEAP_FLAGS flags;
		UINT NodeMask;

	private:
		static  uint16_t index;
	};
}