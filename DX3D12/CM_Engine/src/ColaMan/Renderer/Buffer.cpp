#include "hzpch.h"
#include "Buffer.h"
#include "Platform/DirectX12/DX12Buffer.h"
#include "Renderer.h"
namespace ColaMan {
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			CM_CORE_ASSERT(false, "RendererAPI::None is not supported!");
			return nullptr;
		case RendererAPI::DX12:
			return new DX12VertexBuffer(vertices, size);
		default:
			return nullptr;
		}
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			CM_CORE_ASSERT(false, "RendererAPI::None is not supported!");
			return nullptr;
		case RendererAPI::DX12:
			return new DX12IndexBuffer(indices, size);
		default:
			return nullptr;
		}
	}
}