#pragma once
#include "PipelineState.h"
#include "ResourceState.h"
#include "ViewPort.h"

namespace ColaMan
{
    class CMCmdList
    {
    public:
        virtual void CMSetPSO(PipelineState* pso) = 0;
        virtual void ResourceStateChange(UINT numBarriers, ResourceState before,ResourceState target,void* resource) = 0;
        virtual void CMSetViewports(UINT num,ViewPort vieport) = 0;
        virtual void CMSetRenderTarget(int RenderTarget);
    };

}
