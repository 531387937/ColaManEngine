#pragma once
#include "PipelineState.h"
#include "ColaMan/Core/RenderCode.h"
#include "Platform/DirectX12/CM2DX12.h"
namespace ColaMan {


	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetLayout(const InputLayout& layout) = 0;
		virtual const InputLayout& GetLayout() const = 0;

		static VertexBuffer* Create(void* vertices, uint32_t size);
	};

	class IndexBuffer {
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind()const = 0;
		virtual void Unbind()const = 0;
		virtual uint16_t GetCount()const = 0;

		static IndexBuffer* Create(uint16_t* indices, uint16_t size);
	};
}