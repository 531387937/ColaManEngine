#pragma once

static D3D12_FILL_MODE GetDX12FillMode(FillMode mode)
{
    switch (mode)
    {
    case FillMode::SOLID:
        return D3D12_FILL_MODE_SOLID;
    case FillMode::WIREFRAME:
        return D3D12_FILL_MODE_WIREFRAME;
    }
    CM_CORE_ASSERT(false, "Unknow Fill Mode! Please check if the mode is correct!");
    return D3D12_FILL_MODE_SOLID;
}



static D3D12_CULL_MODE GetDX12CullMode(CullMode mode)
{
    switch (mode)
    {
    case CullMode::None:
        return D3D12_CULL_MODE_NONE;
    case CullMode::Back:
        return D3D12_CULL_MODE_BACK;
    case CullMode::Front:
        return D3D12_CULL_MODE_FRONT;
    }
    CM_CORE_ASSERT(false, "Unknow Cull Mode! Please check if the mode is correct!");
    return D3D12_CULL_MODE_BACK;
}



static D3D12_CONSERVATIVE_RASTERIZATION_MODE GetDX12ConservativeRasterizationMode(CONSERVATIVE_RASTERIZATION_MODE mode)
{
    switch (mode)
    {
    case CONSERVATIVE_RASTERIZATION_MODE::CONSERVATIVE_RASTERIZATION_MODE_OFF:
        return D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;
    case CONSERVATIVE_RASTERIZATION_MODE::CONSERVATIVE_RASTERIZATION_MODE_ON:
        return D3D12_CONSERVATIVE_RASTERIZATION_MODE_ON;
    }
    CM_CORE_ASSERT(false, "Unknown Conservative Rasterization Mode! Please check if the mode is correct!");
    return D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;
}



static D3D12_BLEND GetDX12BlendMode(BlendMode mode)
{
    switch (mode)
    {
    case BlendMode::BLEND_ZERO:
        return D3D12_BLEND_ZERO;
    case BlendMode::BLEND_ONE:
        return D3D12_BLEND_ONE;
    case BlendMode::BLEND_SRC_COLOR:
        return D3D12_BLEND_SRC_COLOR;
    case BlendMode::BLEND_INV_SRC_COLOR:
        return D3D12_BLEND_INV_SRC_COLOR;
    case BlendMode::BLEND_SRC_ALPHA:
        return D3D12_BLEND_SRC_ALPHA;
    case BlendMode::BLEND_INV_SRC_ALPHA:
        return D3D12_BLEND_INV_SRC_ALPHA;
    case BlendMode::BLEND_DEST_ALPHA:
        return D3D12_BLEND_DEST_ALPHA;
    case BlendMode::BLEND_INV_DEST_ALPHA:
        return D3D12_BLEND_INV_DEST_ALPHA;
    case BlendMode::BLEND_DEST_COLOR:
        return D3D12_BLEND_DEST_COLOR;
    case BlendMode::BLEND_INV_DEST_COLOR:
        return D3D12_BLEND_INV_DEST_COLOR;
    case BlendMode::BLEND_SRC_ALPHA_SAT:
        return D3D12_BLEND_SRC_ALPHA_SAT;
    case BlendMode::BLEND_BLEND_FACTOR:
        return D3D12_BLEND_BLEND_FACTOR;
    case BlendMode::BLEND_INV_BLEND_FACTOR:
        return D3D12_BLEND_INV_BLEND_FACTOR;
    case BlendMode::BLEND_SRC1_COLOR:
        return D3D12_BLEND_SRC1_COLOR;
    case BlendMode::BLEND_INV_SRC1_COLOR:
        return D3D12_BLEND_INV_SRC1_COLOR;
    case BlendMode::BLEND_SRC1_ALPHA:
        return D3D12_BLEND_SRC1_ALPHA;
    case BlendMode::BLEND_INV_SRC1_ALPHA:
        return D3D12_BLEND_INV_SRC1_ALPHA;
    }
    CM_CORE_ASSERT(false, "Unknown Blend Mode! Please check if the mode is correct!");
    return D3D12_BLEND_ZERO;
}



static D3D12_BLEND_OP GetDX12BlendOp(BLEND_OP op)
{
    switch (op)
    {
    case BLEND_OP::BLEND_OP_ADD:
        return D3D12_BLEND_OP_ADD;
    case BLEND_OP::BLEND_OP_SUBTRACT:
        return D3D12_BLEND_OP_SUBTRACT;
    case BLEND_OP::BLEND_OP_REV_SUBTRACT:
        return D3D12_BLEND_OP_REV_SUBTRACT;
    case BLEND_OP::BLEND_OP_MIN:
        return D3D12_BLEND_OP_MIN;
    case BLEND_OP::BLEND_OP_MAX:
        return D3D12_BLEND_OP_MAX;
    }
    CM_CORE_ASSERT(false, "Unknown Blend Operation! Please check if the operation is correct!");
    return D3D12_BLEND_OP_ADD;
}


static D3D12_LOGIC_OP GetDX12LogicOp(LOGIC_OP op)
{
    switch (op)
    {
    case LOGIC_OP::LOGIC_OP_CLEAR:
        return D3D12_LOGIC_OP_CLEAR;
    case LOGIC_OP::LOGIC_OP_SET:
        return D3D12_LOGIC_OP_SET;
    case LOGIC_OP::LOGIC_OP_COPY:
        return D3D12_LOGIC_OP_COPY;
    case LOGIC_OP::LOGIC_OP_COPY_INVERTED:
        return D3D12_LOGIC_OP_COPY_INVERTED;
    case LOGIC_OP::LOGIC_OP_NOOP:
        return D3D12_LOGIC_OP_NOOP;
    case LOGIC_OP::LOGIC_OP_INVERT:
        return D3D12_LOGIC_OP_INVERT;
    case LOGIC_OP::LOGIC_OP_AND:
        return D3D12_LOGIC_OP_AND;
    case LOGIC_OP::LOGIC_OP_NAND:
        return D3D12_LOGIC_OP_NAND;
    case LOGIC_OP::LOGIC_OP_OR:
        return D3D12_LOGIC_OP_OR;
    case LOGIC_OP::LOGIC_OP_NOR:
        return D3D12_LOGIC_OP_NOR;
    case LOGIC_OP::LOGIC_OP_XOR:
        return D3D12_LOGIC_OP_XOR;
    case LOGIC_OP::LOGIC_OP_EQUIV:
        return D3D12_LOGIC_OP_EQUIV;
    case LOGIC_OP::LOGIC_OP_AND_REVERSE:
        return D3D12_LOGIC_OP_AND_REVERSE;
    case LOGIC_OP::LOGIC_OP_AND_INVERTED:
        return D3D12_LOGIC_OP_AND_INVERTED;
    case LOGIC_OP::LOGIC_OP_OR_REVERSE:
        return D3D12_LOGIC_OP_OR_REVERSE;
    case LOGIC_OP::LOGIC_OP_OR_INVERTED:
        return D3D12_LOGIC_OP_OR_INVERTED;
    }
    CM_CORE_ASSERT(false, "Unknown Logic Operation! Please check if the operation is correct!");
    return D3D12_LOGIC_OP_CLEAR;
}


static D3D12_COLOR_WRITE_ENABLE GetDX12ColorWriteEnable(COLOR_WRITE_ENABLE enable)
{
    switch (enable)
    {
    case COLOR_WRITE_ENABLE::COLOR_WRITE_ENABLE_RED:
        return D3D12_COLOR_WRITE_ENABLE_RED;
    case COLOR_WRITE_ENABLE::COLOR_WRITE_ENABLE_GREEN:
        return D3D12_COLOR_WRITE_ENABLE_GREEN;
    case COLOR_WRITE_ENABLE::COLOR_WRITE_ENABLE_BLUE:
        return D3D12_COLOR_WRITE_ENABLE_BLUE;
    case COLOR_WRITE_ENABLE::COLOR_WRITE_ENABLE_ALPHA:
        return D3D12_COLOR_WRITE_ENABLE_ALPHA;
    case COLOR_WRITE_ENABLE::COLOR_WRITE_ENABLE_ALL:
        return D3D12_COLOR_WRITE_ENABLE_ALL;
    }
    CM_CORE_ASSERT(false, "Unknown Color Write Enable! Please check if the enable value is correct!");
    return D3D12_COLOR_WRITE_ENABLE_ALL;
}

static D3D12_DEPTH_WRITE_MASK GetDX12DepthWriteMask(DEPTH_WRITE_MASK mask)
{
    switch (mask)
    {
    case DEPTH_WRITE_MASK::DEPTH_WRITE_MASK_ZERO:
        return D3D12_DEPTH_WRITE_MASK_ZERO;
    case DEPTH_WRITE_MASK::DEPTH_WRITE_MASK_ALL:
        return D3D12_DEPTH_WRITE_MASK_ALL;
    }
    CM_CORE_ASSERT(false, "Unknown Depth Write Mask! Please check if the mask value is correct!");
    return D3D12_DEPTH_WRITE_MASK_ALL;
}



static D3D12_COMPARISON_FUNC GetDX12ComparisonFunc(COMPARISON_FUNC func)
{
    switch (func)
    {
    case COMPARISON_FUNC::COMPARISON_FUNC_NEVER:
        return D3D12_COMPARISON_FUNC_NEVER;
    case COMPARISON_FUNC::COMPARISON_FUNC_LESS:
        return D3D12_COMPARISON_FUNC_LESS;
    case COMPARISON_FUNC::COMPARISON_FUNC_EQUAL:
        return D3D12_COMPARISON_FUNC_EQUAL;
    case COMPARISON_FUNC::COMPARISON_FUNC_LESS_EQUAL:
        return D3D12_COMPARISON_FUNC_LESS_EQUAL;
    case COMPARISON_FUNC::COMPARISON_FUNC_GREATER:
        return D3D12_COMPARISON_FUNC_GREATER;
    case COMPARISON_FUNC::COMPARISON_FUNC_NOT_EQUAL:
        return D3D12_COMPARISON_FUNC_NOT_EQUAL;
    case COMPARISON_FUNC::COMPARISON_FUNC_GREATER_EQUAL:
        return D3D12_COMPARISON_FUNC_GREATER_EQUAL;
    case COMPARISON_FUNC::COMPARISON_FUNC_ALWAYS:
        return D3D12_COMPARISON_FUNC_ALWAYS;
    }
    CM_CORE_ASSERT(false, "Unknown Comparison Function! Please check if the function is correct!");
    return D3D12_COMPARISON_FUNC_ALWAYS;
}

static D3D12_STENCIL_OP GetDX12StencilOp(STENCIL_OP op)
{
    switch (op)
    {
    case STENCIL_OP::STENCIL_OP_KEEP:
        return D3D12_STENCIL_OP_KEEP;
    case STENCIL_OP::STENCIL_OP_ZERO:
        return D3D12_STENCIL_OP_ZERO;
    case STENCIL_OP::STENCIL_OP_REPLACE:
        return D3D12_STENCIL_OP_REPLACE;
    case STENCIL_OP::STENCIL_OP_INCR_SAT:
        return D3D12_STENCIL_OP_INCR_SAT;
    case STENCIL_OP::STENCIL_OP_DECR_SAT:
        return D3D12_STENCIL_OP_DECR_SAT;
    case STENCIL_OP::STENCIL_OP_INVERT:
        return D3D12_STENCIL_OP_INVERT;
    case STENCIL_OP::STENCIL_OP_INCR:
        return D3D12_STENCIL_OP_INCR;
    case STENCIL_OP::STENCIL_OP_DECR:
        return D3D12_STENCIL_OP_DECR;
    }
    CM_CORE_ASSERT(false, "Unknown Stencil Operation! Please check if the operation is correct!");
    return D3D12_STENCIL_OP_KEEP;
}

static D3D12_PRIMITIVE_TOPOLOGY_TYPE GetDX12PrimitiveTopologyType(PRIMITIVE_TOPOLOGY_TYPE topology)
{
    switch (topology)
    {
    case PRIMITIVE_TOPOLOGY_TYPE::PRIMITIVE_TOPOLOGY_TYPE_UNDEFINED:
        return D3D12_PRIMITIVE_TOPOLOGY_TYPE_UNDEFINED;
    case PRIMITIVE_TOPOLOGY_TYPE::PRIMITIVE_TOPOLOGY_TYPE_POINT:
        return D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT;
    case PRIMITIVE_TOPOLOGY_TYPE::PRIMITIVE_TOPOLOGY_TYPE_LINE:
        return D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE;
    case PRIMITIVE_TOPOLOGY_TYPE::PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE:
        return D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    case PRIMITIVE_TOPOLOGY_TYPE::PRIMITIVE_TOPOLOGY_TYPE_PATCH:
        return D3D12_PRIMITIVE_TOPOLOGY_TYPE_PATCH;
    }
    CM_CORE_ASSERT(false, "Unknown Primitive Topology Type! Please check if the topology type is correct!");
    return D3D12_PRIMITIVE_TOPOLOGY_TYPE_UNDEFINED;
}

static D3D12_PIPELINE_STATE_FLAGS GetDX12PipelineStateFlags(PIPELINE_STATE_FLAGS flags)
{
    switch (flags)
    {
    case PIPELINE_STATE_FLAGS::PIPELINE_STATE_FLAG_NONE:
        return D3D12_PIPELINE_STATE_FLAG_NONE;
    case PIPELINE_STATE_FLAGS::PIPELINE_STATE_FLAG_TOOL_DEBUG:
        return D3D12_PIPELINE_STATE_FLAG_TOOL_DEBUG;
    default:
        CM_CORE_ASSERT(false, "Unknown PIPELINE_STATE_FLAGS value!");
        return D3D12_PIPELINE_STATE_FLAG_NONE;
    }
}



static D3D12_ROOT_PARAMETER_TYPE GetDX12RootParameterType(ROOT_PARAMETER_TYPE type)
{
    switch (type)
    {
    case ROOT_PARAMETER_TYPE::ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE:
        return D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
    case ROOT_PARAMETER_TYPE::ROOT_PARAMETER_TYPE_32BIT_CONSTANTS:
        return D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
    case ROOT_PARAMETER_TYPE::ROOT_PARAMETER_TYPE_CBV:
        return D3D12_ROOT_PARAMETER_TYPE_CBV;
    case ROOT_PARAMETER_TYPE::ROOT_PARAMETER_TYPE_SRV:
        return D3D12_ROOT_PARAMETER_TYPE_SRV;
    case ROOT_PARAMETER_TYPE::ROOT_PARAMETER_TYPE_UAV:
        return D3D12_ROOT_PARAMETER_TYPE_UAV;
    }
    CM_CORE_ASSERT(false, "Unknown Root Parameter Type! Please check if the type is correct!");
    return D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
}

static D3D12_SHADER_VISIBILITY GetDX12ShaderVisibility(SHADER_VISIBILITY visibility)
{
    switch (visibility)
    {
    case SHADER_VISIBILITY::SHADER_VISIBILITY_ALL:
        return D3D12_SHADER_VISIBILITY_ALL;
    case SHADER_VISIBILITY::SHADER_VISIBILITY_VERTEX:
        return D3D12_SHADER_VISIBILITY_VERTEX;
    case SHADER_VISIBILITY::SHADER_VISIBILITY_HULL:
        return D3D12_SHADER_VISIBILITY_HULL;
    case SHADER_VISIBILITY::SHADER_VISIBILITY_DOMAIN:
        return D3D12_SHADER_VISIBILITY_DOMAIN;
    case SHADER_VISIBILITY::SHADER_VISIBILITY_GEOMETRY:
        return D3D12_SHADER_VISIBILITY_GEOMETRY;
    case SHADER_VISIBILITY::SHADER_VISIBILITY_PIXEL:
        return D3D12_SHADER_VISIBILITY_PIXEL;
    case SHADER_VISIBILITY::SHADER_VISIBILITY_AMPLIFICATION:
        return D3D12_SHADER_VISIBILITY_AMPLIFICATION;
    case SHADER_VISIBILITY::SHADER_VISIBILITY_MESH:
        return D3D12_SHADER_VISIBILITY_MESH;
    }
    CM_CORE_ASSERT(false, "Unknown Shader Visibility! Please check if the visibility is correct!");
    return D3D12_SHADER_VISIBILITY_ALL;
}

static D3D12_DESCRIPTOR_RANGE_TYPE GetDX12DescriptorRangeType(DESCRIPTOR_RANGE_TYPE rangeType)
{
    switch (rangeType)
    {
    case DESCRIPTOR_RANGE_TYPE::DESCRIPTOR_RANGE_TYPE_SRV:
        return D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
    case DESCRIPTOR_RANGE_TYPE::DESCRIPTOR_RANGE_TYPE_UAV:
        return D3D12_DESCRIPTOR_RANGE_TYPE_UAV;
    case DESCRIPTOR_RANGE_TYPE::DESCRIPTOR_RANGE_TYPE_CBV:
        return D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
    case DESCRIPTOR_RANGE_TYPE::DESCRIPTOR_RANGE_TYPE_SAMPLER:
        return D3D12_DESCRIPTOR_RANGE_TYPE_SAMPLER;
    }
    CM_CORE_ASSERT(false, "Unknown Descriptor Range Type! Please check if the range type is correct!");
    return D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
}

static D3D12_FILTER GetDX12Filter(FILTER filter)
{
    switch (filter)
    {
    case FILTER::FILTER_MIN_MAG_MIP_POINT:
        return D3D12_FILTER_MIN_MAG_MIP_POINT;
    case FILTER::FILTER_MIN_MAG_POINT_MIP_LINEAR:
        return D3D12_FILTER_MIN_MAG_POINT_MIP_LINEAR;
    case FILTER::FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT:
        return D3D12_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT;
    case FILTER::FILTER_MIN_POINT_MAG_MIP_LINEAR:
        return D3D12_FILTER_MIN_POINT_MAG_MIP_LINEAR;
    case FILTER::FILTER_MIN_LINEAR_MAG_MIP_POINT:
        return D3D12_FILTER_MIN_LINEAR_MAG_MIP_POINT;
    case FILTER::FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR:
        return D3D12_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
    case FILTER::FILTER_MIN_MAG_LINEAR_MIP_POINT:
        return D3D12_FILTER_MIN_MAG_LINEAR_MIP_POINT;
    case FILTER::FILTER_MIN_MAG_MIP_LINEAR:
        return D3D12_FILTER_MIN_MAG_MIP_LINEAR;
    case FILTER::FILTER_ANISOTROPIC:
        return D3D12_FILTER_ANISOTROPIC;
    case FILTER::FILTER_COMPARISON_MIN_MAG_MIP_POINT:
        return D3D12_FILTER_COMPARISON_MIN_MAG_MIP_POINT;
    case FILTER::FILTER_COMPARISON_MIN_MAG_POINT_MIP_LINEAR:
        return D3D12_FILTER_COMPARISON_MIN_MAG_POINT_MIP_LINEAR;
    case FILTER::FILTER_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT:
        return D3D12_FILTER_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT;
    case FILTER::FILTER_COMPARISON_MIN_POINT_MAG_MIP_LINEAR:
        return D3D12_FILTER_COMPARISON_MIN_POINT_MAG_MIP_LINEAR;
    case FILTER::FILTER_COMPARISON_MIN_LINEAR_MAG_MIP_POINT:
        return D3D12_FILTER_COMPARISON_MIN_LINEAR_MAG_MIP_POINT;
    case FILTER::FILTER_COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR:
        return D3D12_FILTER_COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
    case FILTER::FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT:
        return D3D12_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT;
    case FILTER::FILTER_COMPARISON_MIN_MAG_MIP_LINEAR:
        return D3D12_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
    case FILTER::FILTER_COMPARISON_ANISOTROPIC:
        return D3D12_FILTER_COMPARISON_ANISOTROPIC;
    case FILTER::FILTER_MINIMUM_MIN_MAG_MIP_POINT:
        return D3D12_FILTER_MINIMUM_MIN_MAG_MIP_POINT;
    case FILTER::FILTER_MINIMUM_MIN_MAG_POINT_MIP_LINEAR:
        return D3D12_FILTER_MINIMUM_MIN_MAG_POINT_MIP_LINEAR;
    case FILTER::FILTER_MINIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT:
        return D3D12_FILTER_MINIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT;
    case FILTER::FILTER_MINIMUM_MIN_POINT_MAG_MIP_LINEAR:
        return D3D12_FILTER_MINIMUM_MIN_POINT_MAG_MIP_LINEAR;
    case FILTER::FILTER_MINIMUM_MIN_LINEAR_MAG_MIP_POINT:
        return D3D12_FILTER_MINIMUM_MIN_LINEAR_MAG_MIP_POINT;
    case FILTER::FILTER_MINIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR:
        return D3D12_FILTER_MINIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
    case FILTER::FILTER_MINIMUM_MIN_MAG_LINEAR_MIP_POINT:
        return D3D12_FILTER_MINIMUM_MIN_MAG_LINEAR_MIP_POINT;
    case FILTER::FILTER_MINIMUM_MIN_MAG_MIP_LINEAR:
        return D3D12_FILTER_MINIMUM_MIN_MAG_MIP_LINEAR;
    case FILTER::FILTER_MINIMUM_ANISOTROPIC:
        return D3D12_FILTER_MINIMUM_ANISOTROPIC;
    case FILTER::FILTER_MAXIMUM_MIN_MAG_MIP_POINT:
        return D3D12_FILTER_MAXIMUM_MIN_MAG_MIP_POINT;
    case FILTER::FILTER_MAXIMUM_MIN_MAG_POINT_MIP_LINEAR:
        return D3D12_FILTER_MAXIMUM_MIN_MAG_POINT_MIP_LINEAR;
    case FILTER::FILTER_MAXIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT:
        return D3D12_FILTER_MAXIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT;
    case FILTER::FILTER_MAXIMUM_MIN_POINT_MAG_MIP_LINEAR:
        return D3D12_FILTER_MAXIMUM_MIN_POINT_MAG_MIP_LINEAR;
    case FILTER::FILTER_MAXIMUM_MIN_LINEAR_MAG_MIP_POINT:
        return D3D12_FILTER_MAXIMUM_MIN_LINEAR_MAG_MIP_POINT;
    case FILTER::FILTER_MAXIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR:
        return D3D12_FILTER_MAXIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
    case FILTER::FILTER_MAXIMUM_MIN_MAG_LINEAR_MIP_POINT:
        return D3D12_FILTER_MAXIMUM_MIN_MAG_LINEAR_MIP_POINT;
    case FILTER::FILTER_MAXIMUM_MIN_MAG_MIP_LINEAR:
        return D3D12_FILTER_MAXIMUM_MIN_MAG_MIP_LINEAR;
    case FILTER::FILTER_MAXIMUM_ANISOTROPIC:
        return D3D12_FILTER_MAXIMUM_ANISOTROPIC;
    }
    CM_CORE_ASSERT(false, "Unknown Filter Type! Please check if the filter is correct!");
    return D3D12_FILTER_MIN_MAG_MIP_POINT;
}

static D3D12_TEXTURE_ADDRESS_MODE GetDX12TextureAddressMode(TEXTURE_ADDRESS_MODE addressMode)
{
    switch (addressMode)
    {
    case TEXTURE_ADDRESS_MODE::TEXTURE_ADDRESS_MODE_WRAP:
        return D3D12_TEXTURE_ADDRESS_MODE_WRAP;
    case TEXTURE_ADDRESS_MODE::TEXTURE_ADDRESS_MODE_MIRROR:
        return D3D12_TEXTURE_ADDRESS_MODE_MIRROR;
    case TEXTURE_ADDRESS_MODE::TEXTURE_ADDRESS_MODE_CLAMP:
        return D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
    case TEXTURE_ADDRESS_MODE::TEXTURE_ADDRESS_MODE_BORDER:
        return D3D12_TEXTURE_ADDRESS_MODE_BORDER;
    case TEXTURE_ADDRESS_MODE::TEXTURE_ADDRESS_MODE_MIRROR_ONCE:
        return D3D12_TEXTURE_ADDRESS_MODE_MIRROR_ONCE;
    }
    CM_CORE_ASSERT(false, "Unknown Texture Address Mode! Please check if the address mode is correct!");
    return D3D12_TEXTURE_ADDRESS_MODE_WRAP;
}

static D3D12_STATIC_BORDER_COLOR GetDX12StaticBorderColor(STATIC_BORDER_COLOR borderColor)
{
    switch (borderColor)
    {
    case STATIC_BORDER_COLOR::STATIC_BORDER_COLOR_TRANSPARENT_BLACK:
        return D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
    case STATIC_BORDER_COLOR::STATIC_BORDER_COLOR_OPAQUE_BLACK:
        return D3D12_STATIC_BORDER_COLOR_OPAQUE_BLACK;
    case STATIC_BORDER_COLOR::STATIC_BORDER_COLOR_OPAQUE_WHITE:
        return D3D12_STATIC_BORDER_COLOR_OPAQUE_WHITE;
    }
    CM_CORE_ASSERT(false, "Unknown Static Border Color! Please check if the border color is correct!");
    return D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
}

static D3D12_ROOT_SIGNATURE_FLAGS GetDX12RootSignatureFlags(ROOT_SIGNATURE_FLAGS flags)
{
    return static_cast<D3D12_ROOT_SIGNATURE_FLAGS>(flags);
}

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

static DXGI_FORMAT ShaderDataTypeToDX12Type(ShaderDataType shaderType)
{
    switch (shaderType)
    {
    case ShaderDataType::None:			return DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;
    case ShaderDataType::Float:		return DXGI_FORMAT::DXGI_FORMAT_R32_FLOAT;
    case ShaderDataType::Float2:		return DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT;
    case ShaderDataType::Float3:		return DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT;
    case ShaderDataType::Float4:		return DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT;
    case ShaderDataType::Int:			return DXGI_FORMAT::DXGI_FORMAT_R32_SINT;
    case ShaderDataType::Int2:			return DXGI_FORMAT::DXGI_FORMAT_R32G32_SINT;
    case ShaderDataType::Int3:			return DXGI_FORMAT::DXGI_FORMAT_R32G32B32_SINT;
    case ShaderDataType::Int4:			return DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_SINT;
    case ShaderDataType::Bool:			return DXGI_FORMAT::DXGI_FORMAT_R8_UINT;
    }
}

static DXGI_FORMAT format2DXFormat(ShaderDataType type)
{
    switch (type)
    {

    case ShaderDataType::Float:   return DXGI_FORMAT_R32_FLOAT;
    case ShaderDataType::Float2:  return DXGI_FORMAT_R32G32_FLOAT;
    case ShaderDataType::Float3:  return DXGI_FORMAT_R32G32B32_FLOAT;
    case ShaderDataType::Float4:  return DXGI_FORMAT_R32G32B32A32_FLOAT;
        //case ShaderDataType::Mat3:    return DXGI_FORMAT_;
        //case ShaderDataType::Mat4:    return 4 * 4;
    case ShaderDataType::Int:     return DXGI_FORMAT_R8_SINT;
    case ShaderDataType::Int2:    return DXGI_FORMAT_R8G8_SINT;
        //case ShaderDataType::Int3:    return DXGI_FORMAT_R8G8B8_SINT;
    case ShaderDataType::Int4:    return DXGI_FORMAT_R8G8B8A8_SINT;
    case ShaderDataType::Bool:    return DXGI_FORMAT_R1_UNORM;

    }
}