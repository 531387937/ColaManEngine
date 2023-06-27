#include "hzpch.h"
#include "Renderer.h"


namespace ColaMan {
	void Renderer::BeginFrame()
	{

	}
	void Renderer::EndFrame()
	{
	}
	void Renderer::Submit(const std::shared_ptr<VertexBuffer>& vertexBuffer, const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		RenderCommand::DrawIndexed(vertexBuffer, indexBuffer);
	}
}