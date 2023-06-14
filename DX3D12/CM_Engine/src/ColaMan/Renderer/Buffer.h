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

	struct BufferElement
	{
		std::string Name;
		ShaderDataType Type;
		uint32_t Index;
		uint32_t Size;
		uint32_t Offset;
		uint32_t Slot;

		BufferElement() = default;

		BufferElement(const std::string& name, ShaderDataType type) :Name(name),Index(0), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Slot(0)
		{

		}

		BufferElement(const std::string& name,uint32_t index, ShaderDataType type) :Name(name),Index(index), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Slot(0)
		{
			
		}
	};

	class BufferLayout
	{
	public:
		BufferLayout() = default;
		~BufferLayout() = default;
		BufferLayout(std::initializer_list<BufferElement>& element):m_Elements(element)
		{
			CalculateOffsetsAndStride();
		}

		uint32_t GetStride() const { return m_Stride; }
		const std::vector<BufferElement>& GetElements() const { return m_Elements; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
	private:
		void CalculateOffsetsAndStride()
		{
			uint32_t offset = 0;
			for (auto& element : m_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
			}
			m_Stride = offset;
		}
	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;

		static VertexBuffer* Create(float* vertices, uint32_t size);
	};

	class IndexBuffer {
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind()const = 0;
		virtual void Unbind()const = 0;
		virtual uint32_t GetCount()const = 0;

		static IndexBuffer* Create(uint32_t* indices, uint32_t size);
	};
}