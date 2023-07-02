#include "hzpch.h"
#include "RenderDevice.h"
#include "Platform/DirectX12/DirectX12RenderDevice.h"

namespace ColaMan
{
	RenderDevice* RenderDevice::device = new DirectX12RenderDevice;
	void RenderDevice::CMCreatePipeline(PipelineState* pipelineState)
	{
		device->CreatePipeline(pipelineState);
	}
	void RenderDevice::CMCreateRootSignature(RootSignature* rootSig)
	{
		device->CreateRootSignature(rootSig);
	}
	void RenderDevice::CMCreateDescriptorHeap(DescriptorHeap* descriptor)
	{
		device->CreateDescriptorHeap(descriptor);
	}
}
