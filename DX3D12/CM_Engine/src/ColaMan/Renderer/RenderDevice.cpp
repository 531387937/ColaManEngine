#include "hzpch.h"
#include "RenderDevice.h"
#include "Platform/DirectX12/DirectX12RenderDevice.h"

namespace ColaMan
{
	RenderDevice* RenderDevice::device = new DirectX12RenderDevice;
}
