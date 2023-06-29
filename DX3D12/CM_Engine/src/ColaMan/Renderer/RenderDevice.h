#pragma once
#include "PipelineState.h"
#include "RendererAPI.h"
#include "RootSignature.h"
namespace ColaMan
{
	class RenderDevice
	{
	public:
		virtual void CreatePipeline(const std::shared_ptr<PipelineState>& pipelineState) = 0;
		virtual void CreateRootSignature(const std::shared_ptr<RootSignature>& rootSig) = 0;
	private:
		static RenderDevice* device;
	};
}


