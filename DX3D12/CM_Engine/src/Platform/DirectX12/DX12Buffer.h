#pragma once
#include "ColaMan/Renderer/Buffer.h"
#include <d3d12.h>

namespace ColaMan {
	class DX12VertexBuffer :public VertexBuffer
	{
	public:
		DX12VertexBuffer(float* vertices, uint32_t size);
		~DX12VertexBuffer();

		virtual void Bind()const override;
		virtual void Unbind()const override;
	private:
		Microsoft::WRL::ComPtr<ID3D12Resource> buffer;
		Microsoft::WRL::ComPtr<ID3D12Resource> uploaderBuffer;
		uint32_t count;
	private:
		inline D3D12_VERTEX_BUFFER_VIEW VertexBufferView()const
		{
			D3D12_VERTEX_BUFFER_VIEW vbv;
			vbv.BufferLocation = buffer->GetGPUVirtualAddress();
			vbv.StrideInBytes = sizeof(float);
			vbv.SizeInBytes = count*sizeof(float);

			return vbv;
		}
	};

	class DX12IndexBuffer :public IndexBuffer
	{
	public:
		DX12IndexBuffer(uint32_t* vertices, uint32_t size);
		~DX12IndexBuffer();

		virtual void Bind()const override;
		virtual void Unbind()const override;
		virtual uint32_t GetCount() const override;
	private:
		Microsoft::WRL::ComPtr<ID3D12Resource> buffer;
		Microsoft::WRL::ComPtr<ID3D12Resource> uploaderBuffer;
		uint32_t count = 0;
	private:
		inline D3D12_INDEX_BUFFER_VIEW IndexBufferView()const
		{
			D3D12_INDEX_BUFFER_VIEW ibv;
			ibv.BufferLocation = buffer->GetGPUVirtualAddress();
			ibv.Format = DXGI_FORMAT_R32_UINT;
			ibv.SizeInBytes = count*sizeof(uint32_t);

			return ibv;
		}
	};
}