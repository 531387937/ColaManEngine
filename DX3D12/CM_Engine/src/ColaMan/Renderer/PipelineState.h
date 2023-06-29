#pragma once
#include "Shader.h"
#include <ColaMan/Renderer/Buffer.h>
#include "ColaMan/Renderer/RootSignature.h"
namespace ColaMan
{
    //////////////////enum///////////////////////////////

    enum class FillMode
    {
        WIREFRAME = 1, SOLID = 2
    };

    enum class CullMode
    {
        None = 1, Front = 2, Back = 3
    };

    enum class CONSERVATIVE_RASTERIZATION_MODE
    {
        CONSERVATIVE_RASTERIZATION_MODE_OFF = 1,
        CONSERVATIVE_RASTERIZATION_MODE_ON = 2
    };

    enum class BlendMode
    {
        BLEND_ZERO = 1,
        BLEND_ONE = 2,
        BLEND_SRC_COLOR = 3,
        BLEND_INV_SRC_COLOR = 4,
        BLEND_SRC_ALPHA = 5,
        BLEND_INV_SRC_ALPHA = 6,
        BLEND_DEST_ALPHA = 7,
        BLEND_INV_DEST_ALPHA = 8,
        BLEND_DEST_COLOR = 9,
        BLEND_INV_DEST_COLOR = 10,
        BLEND_SRC_ALPHA_SAT = 11,
        BLEND_BLEND_FACTOR = 14,
        BLEND_INV_BLEND_FACTOR = 15,
        BLEND_SRC1_COLOR = 16,
        BLEND_INV_SRC1_COLOR = 17,
        BLEND_SRC1_ALPHA = 18,
        BLEND_INV_SRC1_ALPHA = 19
    };

    enum class BLEND_OP
    {
        BLEND_OP_ADD = 1,
        BLEND_OP_SUBTRACT = 2,
        BLEND_OP_REV_SUBTRACT = 3,
        BLEND_OP_MIN = 4,
        BLEND_OP_MAX = 5
    };
    enum class LOGIC_OP
    {
        LOGIC_OP_CLEAR = 0,
        LOGIC_OP_SET = 1,
        LOGIC_OP_COPY = 2,
        LOGIC_OP_COPY_INVERTED = 3,
        LOGIC_OP_NOOP = 4,
        LOGIC_OP_INVERT = 5,
        LOGIC_OP_AND = 6,
        LOGIC_OP_NAND = 7,
        LOGIC_OP_OR = 8,
        LOGIC_OP_NOR = 9,
        LOGIC_OP_XOR = 10,
        LOGIC_OP_EQUIV = 11,
        LOGIC_OP_AND_REVERSE = 12,
        LOGIC_OP_AND_INVERTED = 13,
        LOGIC_OP_OR_REVERSE = 14,
        LOGIC_OP_OR_INVERTED = 15
    };

    enum class COLOR_WRITE_ENABLE
    {
       COLOR_WRITE_ENABLE_RED = 1,
       COLOR_WRITE_ENABLE_GREEN = 2,
       COLOR_WRITE_ENABLE_BLUE = 4,
       COLOR_WRITE_ENABLE_ALPHA = 8,
       COLOR_WRITE_ENABLE_ALL = (((COLOR_WRITE_ENABLE_RED | COLOR_WRITE_ENABLE_GREEN) | COLOR_WRITE_ENABLE_BLUE) |COLOR_WRITE_ENABLE_ALPHA)
    };

    enum class DEPTH_WRITE_MASK
    {
        DEPTH_WRITE_MASK_ZERO = 0,
        DEPTH_WRITE_MASK_ALL = 1
    };

    enum class COMPARISON_FUNC
    {
        COMPARISON_FUNC_NEVER = 1,
        COMPARISON_FUNC_LESS = 2,
        COMPARISON_FUNC_EQUAL = 3,
        COMPARISON_FUNC_LESS_EQUAL = 4,
        COMPARISON_FUNC_GREATER = 5,
        COMPARISON_FUNC_NOT_EQUAL = 6,
        COMPARISON_FUNC_GREATER_EQUAL = 7,
        COMPARISON_FUNC_ALWAYS = 8
    };

    enum class STENCIL_OP
    {
        STENCIL_OP_KEEP = 1,
        STENCIL_OP_ZERO = 2,
        STENCIL_OP_REPLACE = 3,
        STENCIL_OP_INCR_SAT = 4,
        STENCIL_OP_DECR_SAT = 5,
        STENCIL_OP_INVERT = 6,
        STENCIL_OP_INCR = 7,
        STENCIL_OP_DECR = 8
    };

    enum PRIMITIVE_TOPOLOGY_TYPE
    {
        PRIMITIVE_TOPOLOGY_TYPE_UNDEFINED = 0,
        PRIMITIVE_TOPOLOGY_TYPE_POINT = 1,
        PRIMITIVE_TOPOLOGY_TYPE_LINE = 2,
        PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE = 3,
        PRIMITIVE_TOPOLOGY_TYPE_PATCH = 4
    };

    enum class PIPELINE_STATE_FLAGS
    {
        PIPELINE_STATE_FLAG_NONE = 0,
        PIPELINE_STATE_FLAG_TOOL_DEBUG = 0x1
    };
    /////////////////////////////////////////DESC///////////////////////////////////////

    struct RasterState
    {
        RasterState() = default;
        FillMode fillMode = FillMode::SOLID;
        CullMode cullMode = CullMode::Back;
        bool frontCounterClockwise = false;
        int depthBias = 0;
        float depthBiasClamp = 0.0f;
        float slopeScaledDepthBias = 0.0f;
        bool depthClipEnable = true;
        bool multisampleEnable = false;
        bool antialiasedLineEnable = false;
        UINT forcedSampleCount = 0;
        CONSERVATIVE_RASTERIZATION_MODE ConservativeRaster = CONSERVATIVE_RASTERIZATION_MODE::CONSERVATIVE_RASTERIZATION_MODE_OFF;
    };

    struct RenderTargetBlendState
    {
        RenderTargetBlendState() = default;
        bool BlendEnable = false;
        bool LogicOpEnable = false;
        BlendMode SrcBlend = BlendMode::BLEND_ONE;
        BlendMode DestBlend = BlendMode::BLEND_ZERO;
        BLEND_OP BlendOp = BLEND_OP::BLEND_OP_ADD;
        BlendMode SrcBlendAlpha = BlendMode::BLEND_ONE;
        BlendMode DestBlendAlpha = BlendMode::BLEND_ZERO;
        BLEND_OP BlendOpAlpha = BLEND_OP::BLEND_OP_ADD;
        LOGIC_OP LogicOp = LOGIC_OP::LOGIC_OP_NOOP;
        UINT8 RenderTargetWriteMask = (UINT8)COLOR_WRITE_ENABLE::COLOR_WRITE_ENABLE_ALL;
    };

    struct BlendState
    {
        BlendState() = default;
        bool AlphaToCoverageEnable = false;
        bool IndependentBlendEnable = false;
        RenderTargetBlendState RenderTarget[8];
    };

    struct InputElement
    {
        std::string Name;
        ShaderDataType Type;
        uint32_t Index;
        uint32_t Size;
        uint32_t Offset;
        uint32_t Slot;
        bool Normalized;
        InputElement() = default;

        InputElement(const std::string& name, ShaderDataType type, bool normalized = false) :Name(name), Index(0), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Slot(0), Normalized(normalized)
        {

        }

        InputElement(const std::string& name, uint32_t index, ShaderDataType type, bool normalized = false) :Name(name), Index(index), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Slot(0), Normalized(normalized)
        {

        }

        uint32_t GetComponentCount() const
        {
            switch (Type)
            {
            case ShaderDataType::Float:   return 1;
            case ShaderDataType::Float2:  return 2;
            case ShaderDataType::Float3:  return 3;
            case ShaderDataType::Float4:  return 4;
            case ShaderDataType::Mat3:    return 3 * 3;
            case ShaderDataType::Mat4:    return 4 * 4;
            case ShaderDataType::Int:     return 1;
            case ShaderDataType::Int2:    return 2;
            case ShaderDataType::Int3:    return 3;
            case ShaderDataType::Int4:    return 4;
            case ShaderDataType::Bool:    return 1;
            }

            CM_CORE_ASSERT(false, "Unknown ShaderDataType!");
            return 0;
        }
    };

    struct InputLayout
    {
    public:
        InputLayout() = default;
        ~InputLayout() = default;
        InputLayout(const std::initializer_list<InputElement>& element) :m_Elements(element)
        {
            CalculateOffsetsAndStride();
        }

        uint32_t GetStride() const { return m_Stride; }
        const std::vector<InputElement>& GetElements() const { return m_Elements; }

        std::vector<InputElement>::iterator begin() { return m_Elements.begin(); }
        std::vector<InputElement>::iterator end() { return m_Elements.end(); }
        std::vector<InputElement>::const_iterator begin() const { return m_Elements.begin(); }
        std::vector<InputElement>::const_iterator end() const { return m_Elements.end(); }
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
        std::vector<InputElement> m_Elements;
        uint32_t m_Stride = 0;
    };

    struct DEPTH_STENCILOP
    {
       STENCIL_OP StencilFailOp;
       STENCIL_OP StencilDepthFailOp;
       STENCIL_OP StencilPassOp;
       COMPARISON_FUNC StencilFunc;
    };

    struct DepthStencilState
    {
        bool DepthEnable;
        DEPTH_WRITE_MASK DepthWriteMask;
        COMPARISON_FUNC DepthFunc;
        bool StencilEnable;
        UINT8 StencilReadMask;
        UINT8 StencilWriteMask;
        DEPTH_STENCILOP FrontFace;
        DEPTH_STENCILOP BackFace;
    };

    struct SampleState
    {
        UINT Count;
        UINT Quality;
    };

    class PipelineState
    {
    public:
        PipelineState()
        {
            pipelineIndex = index;
            index++;
        }
        // used for hashMap
        uint16_t pipelineIndex;

        //property
        uint16_t rootSignatureIndex;
        Shader vertexShader;
        Shader pixelShader;
        Shader domainShader;
        Shader hullShader;
        Shader geometryShader;
        BlendState blendState;
        UINT sampleMask;
        RasterState rasterState;
        DepthStencilState depthStencilState;
        InputLayout inputLayout;
        PRIMITIVE_TOPOLOGY_TYPE primitiveTopologyType;
        UINT numRenderTargets;
        DXGI_FORMAT rtvFormats[8];
        DXGI_FORMAT dsvFormat;
        SampleState sampleState;
        UINT nodeMask;
        PIPELINE_STATE_FLAGS flags;
    private:
        static uint16_t index;
    };
}
