#pragma once
#include <DirectXMath.h>
#include "Buffer.h"
namespace ColaMan {
	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0,DX12 = 1
		};
	public:
		virtual void SetClearColor(const DirectX::XMFLOAT4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const std::shared_ptr<VertexBuffer>& vertexBuffer, const std::shared_ptr<IndexBuffer>& IndexBuffer) = 0;

		inline static API GetAPI() { return s_API; }
	private:
		static API s_API;
	};
}

