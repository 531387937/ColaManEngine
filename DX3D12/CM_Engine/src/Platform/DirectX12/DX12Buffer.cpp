#include "hzpch.h"
#include "DX12Buffer.h"
#include "ColaMan/DirectX12/d3dUtil.h"
#include "ColaMan/DirectX12/CMd3dApp.h"

namespace ColaMan
{
	DX12VertexBuffer::DX12VertexBuffer(float* vertices, uint32_t size):count(size)
	{
		auto app = CMD3DApp::GetApp();
		buffer = d3dUtil::CreateDefaultBuffer(app->GetDevice(), app->GetCommandList(), vertices, size, uploaderBuffer);
	}
	DX12VertexBuffer::~DX12VertexBuffer()
	{
		buffer = nullptr;
	}
	void DX12VertexBuffer::Bind() const
	{
		auto app = CMD3DApp::GetApp();
		app->GetCommandList()->IASetVertexBuffers(0, 1, &VertexBufferView());
	}

	void DX12VertexBuffer::Unbind() const
	{
	}

	DX12IndexBuffer::DX12IndexBuffer(uint32_t* indices, uint32_t size) :count(size)
	{
		auto app = CMD3DApp::GetApp();
		buffer = d3dUtil::CreateDefaultBuffer(app->GetDevice(), app->GetCommandList(), indices, size, uploaderBuffer);
	}
	DX12IndexBuffer::~DX12IndexBuffer()
	{
		buffer = nullptr;
	}
	void DX12IndexBuffer::Bind() const
	{
		auto app = CMD3DApp::GetApp();
		app->GetCommandList()->IASetIndexBuffer(&IndexBufferView());
	}

	void DX12IndexBuffer::Unbind() const
	{
	}
	uint32_t DX12IndexBuffer::GetCount() const
	{
		return count;
	}
}
