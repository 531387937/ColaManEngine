#pragma once
#include "ColaMan/Renderer/RenderDevice.h"
namespace ColaMan
{
	class DirectX12RenderDevice : public RenderDevice
	{
	public:
		DirectX12RenderDevice() = default;
		void CreatePipeline( PipelineState* pipelineState);
		void CreateRootSignature( RootSignature* rootSig);
		void CreateDescriptorHeap( DescriptorHeap* descriptor);

	};
}


