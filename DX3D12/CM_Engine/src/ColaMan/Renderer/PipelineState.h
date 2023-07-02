#pragma once
#include "Shader.h"
#include "ColaMan/Renderer/RootSignature.h"
#include "ColaMan/Core/RenderCode.h"
#include "Platform/DirectX12/CM2DX12.h"
#include "Platform/DirectX12/DirectX12_Map.h"
namespace ColaMan
{
	struct RasterState
	{
		RasterState() = default;
		D3D12_RASTERIZER_DESC GetDX12RasterDesc() const
		{
			D3D12_RASTERIZER_DESC rasterDesc{};
			rasterDesc.FillMode = GetDX12FillMode(fillMode);
			rasterDesc.DepthBias = depthBias;
			rasterDesc.DepthBiasClamp = depthBiasClamp;
			rasterDesc.AntialiasedLineEnable = antialiasedLineEnable;
			rasterDesc.ConservativeRaster = GetDX12ConservativeRasterizationMode(ConservativeRaster);
			rasterDesc.CullMode = GetDX12CullMode(cullMode);
			rasterDesc.ForcedSampleCount = forcedSampleCount;
			rasterDesc.FrontCounterClockwise = frontCounterClockwise;
			rasterDesc.MultisampleEnable = multisampleEnable;
			rasterDesc.SlopeScaledDepthBias = slopeScaledDepthBias;
			return rasterDesc;
		}
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
		D3D12_RENDER_TARGET_BLEND_DESC GetDX12RenderTargetBlendDesc() const
		{
			D3D12_RENDER_TARGET_BLEND_DESC dx12BlendDesc{};
			dx12BlendDesc.BlendEnable = BlendEnable;
			dx12BlendDesc.LogicOpEnable = LogicOpEnable;
			dx12BlendDesc.SrcBlend = GetDX12BlendMode(SrcBlend);
			dx12BlendDesc.DestBlend = GetDX12BlendMode(DestBlend);
			dx12BlendDesc.BlendOp = GetDX12BlendOp(BlendOp);
			dx12BlendDesc.SrcBlendAlpha = GetDX12BlendMode(SrcBlendAlpha);
			dx12BlendDesc.DestBlendAlpha = GetDX12BlendMode(DestBlendAlpha);
			dx12BlendDesc.BlendOpAlpha = GetDX12BlendOp(BlendOpAlpha);
			dx12BlendDesc.LogicOp = GetDX12LogicOp(LogicOp);
			dx12BlendDesc.RenderTargetWriteMask = RenderTargetWriteMask;
			return dx12BlendDesc;
		}
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
		D3D12_BLEND_DESC GetD3D12BlendDesc() const
		{
			D3D12_BLEND_DESC desc{};
			desc.AlphaToCoverageEnable = AlphaToCoverageEnable;
			desc.IndependentBlendEnable = IndependentBlendEnable;

			for (UINT i = 0; i < 8; ++i)
			{
				desc.RenderTarget[i] = RenderTarget[i].GetDX12RenderTargetBlendDesc();
			}

			return desc;
		}

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

		D3D12_INPUT_LAYOUT_DESC GetDX12InputLayoutDesc()const
		{
			std::vector<D3D12_INPUT_ELEMENT_DESC> mInputLayout;
			for (auto iter = begin(); iter != end(); iter++)
			{
				mInputLayout.push_back({ iter->Name.c_str(), iter->Index, format2DXFormat(iter->Type), iter->Slot, iter->Offset, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 });
			}
			return D3D12_INPUT_LAYOUT_DESC{ mInputLayout.data(), (UINT)mInputLayout.size() };
		}
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
		D3D12_DEPTH_STENCILOP_DESC DEPTH_STENCILOP::GetDX12DepthStencilOpDesc() const
		{
			D3D12_DEPTH_STENCILOP_DESC desc{};
			desc.StencilFailOp = GetDX12StencilOp(StencilFailOp);
			desc.StencilDepthFailOp = GetDX12StencilOp(StencilDepthFailOp);
			desc.StencilPassOp = GetDX12StencilOp(StencilPassOp);
			desc.StencilFunc = GetDX12ComparisonFunc(StencilFunc);
			return desc;
		}
		STENCIL_OP StencilFailOp = STENCIL_OP::STENCIL_OP_KEEP;
		STENCIL_OP StencilDepthFailOp = STENCIL_OP::STENCIL_OP_KEEP;
		STENCIL_OP StencilPassOp = STENCIL_OP::STENCIL_OP_KEEP;
		COMPARISON_FUNC StencilFunc = COMPARISON_FUNC::COMPARISON_FUNC_ALWAYS;
	};

	struct DepthStencilState
	{
		D3D12_DEPTH_STENCIL_DESC DepthStencilState::GetDX12DepthStencilDesc() const
		{
			D3D12_DEPTH_STENCIL_DESC desc{};
			desc.DepthEnable = DepthEnable;
			desc.DepthWriteMask = GetDX12DepthWriteMask(DepthWriteMask);
			desc.DepthFunc = GetDX12ComparisonFunc(DepthFunc);
			desc.StencilEnable = StencilEnable;
			desc.StencilReadMask = StencilReadMask;
			desc.StencilWriteMask = StencilWriteMask;
			desc.FrontFace = FrontFace.GetDX12DepthStencilOpDesc();
			desc.BackFace = BackFace.GetDX12DepthStencilOpDesc();
			return desc;
		}
		bool DepthEnable = true;
		DEPTH_WRITE_MASK DepthWriteMask = DEPTH_WRITE_MASK::DEPTH_WRITE_MASK_ALL;
		COMPARISON_FUNC DepthFunc = COMPARISON_FUNC::COMPARISON_FUNC_LESS;
		bool StencilEnable = true;
		UINT8 StencilReadMask = 0xff;
		UINT8 StencilWriteMask = 0xff;
		DEPTH_STENCILOP FrontFace;
		DEPTH_STENCILOP BackFace;
	};

	struct SampleState
	{
		DXGI_SAMPLE_DESC GetDXGISampleDesc() const
		{
			DXGI_SAMPLE_DESC desc{};
			desc.Count = Count;
			desc.Quality = Quality;
			return desc;
		}
		UINT Count = 1;
		UINT Quality = 0;
	};

	class PipelineState
	{
	public:
		ID3D12PipelineState* PipelineState::GetD3D12GraphicsPipelineStateDesc(ID3D12Device* device) const
		{
			ID3D12PipelineState* pso;
			D3D12_GRAPHICS_PIPELINE_STATE_DESC desc{};
			ZeroMemory(&desc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
			desc.pRootSignature = DirectX12Map::GetRootSignature(rootSignatureIndex);
			if (vertexShader)
				desc.VS = vertexShader->Bound();
			if (pixelShader)
				desc.PS = pixelShader->Bound();
			if (domainShader)
				desc.DS = domainShader->Bound();
			if (hullShader)
				desc.HS = hullShader->Bound();
			if (geometryShader)
				desc.GS = geometryShader->Bound();
			desc.BlendState = blendState.GetD3D12BlendDesc();
			desc.SampleMask = sampleMask;
			desc.RasterizerState = rasterState.GetDX12RasterDesc();
			desc.DepthStencilState = depthStencilState.GetDX12DepthStencilDesc();

			std::vector<D3D12_INPUT_ELEMENT_DESC> mInputLayout;
			for (auto iter = inputLayout.begin(); iter != inputLayout.end(); iter++)
			{
				mInputLayout.push_back({ iter->Name.c_str(), iter->Index, format2DXFormat(iter->Type), iter->Slot, iter->Offset, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 });

			}

			desc.InputLayout = { mInputLayout.data(), (UINT)mInputLayout.size() };
			desc.PrimitiveTopologyType = GetDX12PrimitiveTopologyType(primitiveTopologyType);
			desc.NumRenderTargets = numRenderTargets;
			for (UINT i = 0; i < numRenderTargets; ++i)
			{
				desc.RTVFormats[i] = rtvFormats[i];
			}
			desc.DSVFormat = dsvFormat;
			desc.SampleDesc.Count = sampleState.Count;
			desc.SampleDesc.Quality = sampleState.Quality;
			desc.NodeMask = nodeMask;
			desc.Flags = GetDX12PipelineStateFlags(flags);

			// Set other members as needed.
			device->CreateGraphicsPipelineState(&desc, IID_PPV_ARGS(&pso));
			return pso;
		}

		PipelineState()
		{
			pipelineIndex = index;
			index++;
		}
		// used for hashMap
		uint16_t pipelineIndex;

		//property
		uint16_t rootSignatureIndex = -1;
		mutable std::shared_ptr<Shader> vertexShader;
		mutable std::shared_ptr<Shader> pixelShader;
		mutable std::shared_ptr<Shader> domainShader;
		mutable std::shared_ptr<Shader> hullShader;
		mutable std::shared_ptr<Shader> geometryShader;
		BlendState blendState;
		UINT sampleMask = UINT_MAX;
		RasterState rasterState;
		DepthStencilState depthStencilState;
		InputLayout inputLayout;
		PRIMITIVE_TOPOLOGY_TYPE primitiveTopologyType = PRIMITIVE_TOPOLOGY_TYPE::PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		UINT numRenderTargets = 1;
		DXGI_FORMAT rtvFormats[8] = { DXGI_FORMAT_UNKNOWN };
		DXGI_FORMAT dsvFormat;
		SampleState sampleState;
		UINT nodeMask = 0x1;
		PIPELINE_STATE_FLAGS flags = PIPELINE_STATE_FLAGS::PIPELINE_STATE_FLAG_NONE;
	private:
		static uint16_t index;
	};
}
