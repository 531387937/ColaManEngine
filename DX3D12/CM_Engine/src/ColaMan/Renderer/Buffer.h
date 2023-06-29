#pragma once

namespace ColaMan {

	enum class ShaderDataType
	{
		None = 0,
		Float, Float2, Float3, Float4, Mat2, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:    return 4;
			case ShaderDataType::Float2:   return 4 * 2;
			case ShaderDataType::Float3:   return 4 * 3;
			case ShaderDataType::Float4:   return 4 * 4;
			case ShaderDataType::Mat3:     return 4 * 3 * 3;
			case ShaderDataType::Mat4:     return 4 * 4 * 4;
			case ShaderDataType::Int:      return 4;
			case ShaderDataType::Int2:     return 4 * 2;
			case ShaderDataType::Int3:     return 4 * 3;
			case ShaderDataType::Int4:     return 4 * 4;
			case ShaderDataType::Bool:     return 1;
		}

		CM_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}


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