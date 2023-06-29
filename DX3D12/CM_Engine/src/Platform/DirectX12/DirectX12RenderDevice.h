#pragma once
#include "ColaMan/Renderer/RenderDevice.h"
namespace ColaMan
{
	class DirectX12RenderDevice : public RenderDevice
	{
	public:
		DirectX12RenderDevice() = default;
		virtual void CreatePipeline(const std::shared_ptr<PipelineState>& pipelineState) override;
		virtual void CreateRootSignature(const std::shared_ptr<RootSignature>& rootSig) override;


	};
}


