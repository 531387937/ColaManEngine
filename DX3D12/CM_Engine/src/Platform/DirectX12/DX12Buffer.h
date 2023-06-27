#pragma once
#include "ColaMan/Renderer/Buffer.h"
#include <d3d12.h>

namespace ColaMan {

	static DXGI_FORMAT ShaderDataTypeToDX12Type(ShaderDataType shaderType)
	{
		switch (shaderType)
		{
		case ColaMan::ShaderDataType::None:			return DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;
		case ColaMan::ShaderDataType::Float:		return DXGI_FORMAT::DXGI_FORMAT_R32_FLOAT;
		case ColaMan::ShaderDataType::Float2:		return DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT;
		case ColaMan::ShaderDataType::Float3:		return DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT;
		case ColaMan::ShaderDataType::Float4:		return DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT;
		case ColaMan::ShaderDataType::Int:			return DXGI_FORMAT::DXGI_FORMAT_R32_SINT;
		case ColaMan::ShaderDataType::Int2:			return DXGI_FORMAT::DXGI_FORMAT_R32G32_SINT;
		case ColaMan::ShaderDataType::Int3:			return DXGI_FORMAT::DXGI_FORMAT_R32G32B32_SINT;
		case ColaMan::ShaderDataType::Int4:			return DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_SINT;
		case ColaMan::ShaderDataType::Bool:			return DXGI_FORMAT::DXGI_FORMAT_R8_UINT;
		}
	}

	class DX12VertexBuffer :public VertexBuffer
	{
	public:
		DX12VertexBuffer(void* vertices, uint32_t size);
		~DX12VertexBuffer();

		virtual void Bind()const override;
		virtual void Unbind()const override;
		virtual void SetLayout(const BufferLayout& layout)override;
		virtual const BufferLayout& GetLayout() const override;
	private:
		Microsoft::WRL::ComPtr<ID3D12Resource> buffer;
		Microsoft::WRL::ComPtr<ID3D12Resource> uploaderBuffer;
		uint32_t count;
		BufferLayout m_Layout;
	private:
		inline D3D12_VERTEX_BUFFER_VIEW VertexBufferView()const
		{
			D3D12_VERTEX_BUFFER_VIEW vbv;
			vbv.BufferLocation = buffer->GetGPUVirtualAddress();
			vbv.StrideInBytes = sizeof(float)*3;
			vbv.SizeInBytes = count;

			return vbv;
		}
	};

	class DX12IndexBuffer :public IndexBuffer
	{
	public:
		DX12IndexBuffer(uint16_t* vertices, uint16_t size);
		~DX12IndexBuffer();

		virtual void Bind()const override;
		virtual void Unbind()const override;
		virtual uint16_t GetCount() const override;
	private:
		Microsoft::WRL::ComPtr<ID3D12Resource> buffer;
		Microsoft::WRL::ComPtr<ID3D12Resource> uploaderBuffer;
		uint16_t count = 0;
	private:
		inline D3D12_INDEX_BUFFER_VIEW IndexBufferView()const
		{
			D3D12_INDEX_BUFFER_VIEW ibv;
			ibv.BufferLocation = buffer->GetGPUVirtualAddress();
			ibv.Format = DXGI_FORMAT_R16_UINT;
			ibv.SizeInBytes = count*sizeof(uint16_t);

			return ibv;
		}
	};
}