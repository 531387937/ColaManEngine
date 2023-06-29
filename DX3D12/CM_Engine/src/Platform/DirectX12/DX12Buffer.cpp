#include "hzpch.h"
#include "DX12Buffer.h"
#include "ColaMan/DirectX12/d3dUtil.h" 
#include "ColaMan/DirectX12/DX12Core.h"

namespace ColaMan
{
	DX12VertexBuffer::DX12VertexBuffer(void* vertices, uint32_t size):count(size)
	{
		buffer = d3dUtil::CreateDefaultBuffer(Dx12Core::GetDevice(), Dx12Core::GetCommandList(), vertices, size, uploaderBuffer);
	}
	DX12VertexBuffer::~DX12VertexBuffer()
	{
		buffer = nullptr;
	}
	void DX12VertexBuffer::Bind() const
	{
		Dx12Core::GetCommandList()->IASetVertexBuffers(0, 1, &VertexBufferView());
	}

	void DX12VertexBuffer::Unbind() const
	{
	}

	void DX12VertexBuffer::SetLayout(const InputLayout& layout)
	{
		m_Layout = layout;
	}

	const InputLayout& DX12VertexBuffer::GetLayout() const
	{
		return m_Layout;
		// TODO: 在此处插入 return 语句
	}

	///////////////////////IndexBuffer/////////////////////////////////


	DX12IndexBuffer::DX12IndexBuffer(uint16_t* indices, uint16_t size) :count(size)
	{
		buffer = d3dUtil::CreateDefaultBuffer(Dx12Core::GetDevice(), Dx12Core::GetCommandList(), indices, size*sizeof(uint16_t), uploaderBuffer);
	}
	DX12IndexBuffer::~DX12IndexBuffer()
	{
		buffer = nullptr;
	}
	void DX12IndexBuffer::Bind() const
	{
		Dx12Core::GetCommandList()->IASetIndexBuffer(&IndexBufferView());
	}

	void DX12IndexBuffer::Unbind() const
	{
	}
	uint16_t DX12IndexBuffer::GetCount() const
	{
		return count;
	}
}
