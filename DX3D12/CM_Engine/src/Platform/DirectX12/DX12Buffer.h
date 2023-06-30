#pragma once
#include "ColaMan/Renderer/Buffer.h"
#include <d3d12.h>
#include "Platform/DirectX12/CM2DX12.h"

namespace ColaMan {

	class DX12VertexBuffer :public VertexBuffer
	{
	public:
		DX12VertexBuffer(void* vertices, uint32_t size);
		~DX12VertexBuffer();

		virtual void Bind()const override;
		virtual void Unbind()const override;
		virtual void SetLayout(const InputLayout& layout)override;
		virtual const InputLayout& GetLayout() const override;
	private:
		Microsoft::WRL::ComPtr<ID3D12Resource> buffer;
		Microsoft::WRL::ComPtr<ID3D12Resource> uploaderBuffer;
		uint32_t count;
		InputLayout m_Layout;
	private:
		inline D3D12_VERTEX_BUFFER_VIEW VertexBufferView()const
		{
			D3D12_VERTEX_BUFFER_VIEW vbv;
			vbv.BufferLocation = buffer->GetGPUVirtualAddress();
			vbv.StrideInBytes = m_Layout.GetStride();;
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