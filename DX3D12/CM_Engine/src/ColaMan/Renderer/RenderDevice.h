#pragma once
#include "PipelineState.h"
#include "RendererAPI.h"
#include "DescriptorHeap.h"
#include "RootSignature.h"
namespace ColaMan
{
	class RenderDevice
	{
	public:
		static void CMCreatePipeline(PipelineState* pipelineState);
		static void CMCreateRootSignature(RootSignature* rootSig);
		static void CMCreateDescriptorHeap(DescriptorHeap* descriptor); 
	protected:
		virtual void CreatePipeline( PipelineState* pipelineState) = 0;
		virtual void CreateRootSignature( RootSignature* rootSig) = 0;
		virtual void CreateDescriptorHeap( DescriptorHeap* descriptor) = 0;
	private:
		static RenderDevice* device;
	};
}


