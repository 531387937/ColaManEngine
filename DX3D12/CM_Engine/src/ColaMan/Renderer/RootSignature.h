#pragma once

#include "ColaMan/Core/RenderCode.h"
#include "Platform/DirectX12/CM2DX12.h"
#include "ColaMan/DirectX12/d3dx12.h"
namespace ColaMan
{

	struct DescriptorRange
	{
		D3D12_DESCRIPTOR_RANGE GetDX12DescriptorRange() const
		{
			D3D12_DESCRIPTOR_RANGE descRange{};
			descRange.RangeType = GetDX12DescriptorRangeType(RangeType);
			descRange.NumDescriptors = NumDescriptors;
			descRange.BaseShaderRegister = BaseShaderRegister;
			descRange.RegisterSpace = RegisterSpace;
			descRange.OffsetInDescriptorsFromTableStart = OffsetInDescriptorsFromTableStart;

			return descRange;
		}

		DESCRIPTOR_RANGE_TYPE RangeType = DESCRIPTOR_RANGE_TYPE::DESCRIPTOR_RANGE_TYPE_CBV;
		UINT NumDescriptors = 1;
		UINT BaseShaderRegister = 0;
		UINT RegisterSpace = 0;
		UINT OffsetInDescriptorsFromTableStart = 0;
	};
	struct RootDescriptorTable
	{
		D3D12_ROOT_DESCRIPTOR_TABLE RootDescriptorTable::GetD3D12RootDescriptorTable() const
		{
			D3D12_ROOT_DESCRIPTOR_TABLE rootDescTable{};
			rootDescTable.NumDescriptorRanges = numDescriptorRanges;

			if (numDescriptorRanges > 0 && pDescriptorRanges != nullptr)
			{
				std::vector<D3D12_DESCRIPTOR_RANGE> descriptorRanges(numDescriptorRanges);

				for (UINT i = 0; i < numDescriptorRanges; ++i)
				{
					descriptorRanges[i] = pDescriptorRanges[i].GetDX12DescriptorRange();
				}

				rootDescTable.pDescriptorRanges = descriptorRanges.data();
			}

			return rootDescTable;
		}

		UINT numDescriptorRanges = 0;
		DescriptorRange* pDescriptorRanges = nullptr;
	};

	struct RootConstants
	{
		D3D12_ROOT_CONSTANTS GetDX12RootConstants() const
		{
			D3D12_ROOT_CONSTANTS rootConstants{};
			rootConstants.ShaderRegister = ShaderRegister;
			rootConstants.RegisterSpace = RegisterSpace;
			rootConstants.Num32BitValues = Num32BitValues;

			return rootConstants;
		}
		UINT ShaderRegister = 0;
		UINT RegisterSpace = 0;
		UINT Num32BitValues = 0;
	};

	struct RootDescriptor
	{
		D3D12_ROOT_DESCRIPTOR GetDX12RootDescriptor() const
		{
			D3D12_ROOT_DESCRIPTOR rootDescriptor{};
			rootDescriptor.ShaderRegister = ShaderRegister;
			rootDescriptor.RegisterSpace = RegisterSpace;

			return rootDescriptor;
		}
		UINT ShaderRegister = 0;
		UINT RegisterSpace = 0;
	};

	struct RootParameter
	{
		RootParameter()
		{
			parameterType = ROOT_PARAMETER_TYPE::ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
			ShaderVisibility = SHADER_VISIBILITY::SHADER_VISIBILITY_ALL;
		}
		D3D12_ROOT_PARAMETER GetDX12RootParameter() const
		{
			D3D12_ROOT_PARAMETER rootParameter{};
			rootParameter.ParameterType = GetDX12RootParameterType(parameterType);
			rootParameter.ShaderVisibility = GetDX12ShaderVisibility(ShaderVisibility);

			switch (parameterType)
			{
			case ROOT_PARAMETER_TYPE::ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE:
				rootParameter.DescriptorTable = DescriptorTable.GetD3D12RootDescriptorTable();
				break;
			case ROOT_PARAMETER_TYPE::ROOT_PARAMETER_TYPE_32BIT_CONSTANTS:
				rootParameter.Constants = Constants.GetDX12RootConstants();
				break;
			case ROOT_PARAMETER_TYPE::ROOT_PARAMETER_TYPE_CBV:
			case ROOT_PARAMETER_TYPE::ROOT_PARAMETER_TYPE_SRV:
			case ROOT_PARAMETER_TYPE::ROOT_PARAMETER_TYPE_UAV:
				rootParameter.Descriptor = Descriptor.GetDX12RootDescriptor();
				break;
			}

			return rootParameter;
		}

		ROOT_PARAMETER_TYPE parameterType = ROOT_PARAMETER_TYPE::ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
		union
		{
			RootDescriptorTable DescriptorTable;
			RootConstants Constants;
			RootDescriptor Descriptor;
		};
		SHADER_VISIBILITY ShaderVisibility = SHADER_VISIBILITY::SHADER_VISIBILITY_ALL;
	};

	struct StaticSamplerDesc
	{
		D3D12_STATIC_SAMPLER_DESC GetDX12StaticSamplerDesc() const
		{
			D3D12_STATIC_SAMPLER_DESC staticSamplerDesc{};
			staticSamplerDesc.Filter = GetDX12Filter(Filter);
			staticSamplerDesc.AddressU = GetDX12TextureAddressMode(AddressU);
			staticSamplerDesc.AddressV = GetDX12TextureAddressMode(AddressV);
			staticSamplerDesc.AddressW = GetDX12TextureAddressMode(AddressW);
			staticSamplerDesc.MipLODBias = MipLODBias;
			staticSamplerDesc.MaxAnisotropy = MaxAnisotropy;
			staticSamplerDesc.ComparisonFunc = GetDX12ComparisonFunc(ComparisonFunc);
			staticSamplerDesc.BorderColor = GetDX12StaticBorderColor(BorderColor);
			staticSamplerDesc.MinLOD = MinLOD;
			staticSamplerDesc.MaxLOD = MaxLOD;
			staticSamplerDesc.ShaderRegister = ShaderRegister;
			staticSamplerDesc.RegisterSpace = RegisterSpace;
			staticSamplerDesc.ShaderVisibility = GetDX12ShaderVisibility(ShaderVisibility);

			return staticSamplerDesc;
		}
		FILTER Filter = FILTER::FILTER_MAXIMUM_MIN_MAG_MIP_LINEAR;
		TEXTURE_ADDRESS_MODE AddressU = TEXTURE_ADDRESS_MODE::TEXTURE_ADDRESS_MODE_WRAP;
		TEXTURE_ADDRESS_MODE AddressV = TEXTURE_ADDRESS_MODE::TEXTURE_ADDRESS_MODE_WRAP;
		TEXTURE_ADDRESS_MODE AddressW = TEXTURE_ADDRESS_MODE::TEXTURE_ADDRESS_MODE_WRAP;
		FLOAT MipLODBias = 0.0f;
		UINT MaxAnisotropy = 0;
		COMPARISON_FUNC ComparisonFunc = COMPARISON_FUNC::COMPARISON_FUNC_LESS;
		STATIC_BORDER_COLOR BorderColor = STATIC_BORDER_COLOR::STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
		FLOAT MinLOD = 0;
		FLOAT MaxLOD = 0;
		UINT ShaderRegister = 0;
		UINT RegisterSpace = 0;
		SHADER_VISIBILITY ShaderVisibility = SHADER_VISIBILITY::SHADER_VISIBILITY_ALL;
	};

	struct RootSignature
	{
	public:

		uint16_t rootSignatureIndex;
		RootSignature() = default;
		RootSignature(UINT Num, std::unique_ptr<RootParameter>& Param,UINT NumSampler,std::unique_ptr<StaticSamplerDesc>& samplers
		, ROOT_SIGNATURE_FLAGS flags = ROOT_SIGNATURE_FLAGS::ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT):numParameters(Num), numSamplers(NumSampler),rootFlags(flags)
		{
			parameters = std::move(Param);
			staticSamplers = std::move(samplers);
		}

		ID3D12RootSignature* RootSignature::GetD3D12RootSignature(ID3D12Device* device) const
		{
			std::vector<D3D12_ROOT_PARAMETER> rootParameter(numParameters);
			for (int i = 0; i < numParameters;i++)
			{
				rootParameter[i] = parameters.get()[i].GetDX12RootParameter();
			}
			std::vector<D3D12_STATIC_SAMPLER_DESC> staticSamplerDesc(numSamplers);
			for (int i = 0; i < numParameters; i++)
			{
				staticSamplerDesc[i] = staticSamplers.get()[i].GetDX12StaticSamplerDesc();
			}
			CD3DX12_ROOT_SIGNATURE_DESC rootSignatureDesc {numParameters, rootParameter.data(), numSamplers, staticSamplerDesc.data(),GetDX12RootSignatureFlags(rootFlags)};

			ID3DBlob* signatureBlob = nullptr;
			ID3DBlob* errorBlob = nullptr;

			HRESULT hr = D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &signatureBlob, &errorBlob);
			if (FAILED(hr))
			{
				// 处理错误信息
				if (errorBlob)
				{
					char* errorMessage = reinterpret_cast<char*>(errorBlob->GetBufferPointer());
					// 输出或处理错误消息
				}

				// 释放资源
				if (signatureBlob)
				{
					signatureBlob->Release();
				}
				if (errorBlob)
				{
					errorBlob->Release();
				}

				CM_CORE_ASSERT(false, "Create DX12 RootSignature failed!");
				// 返回空指针
				return nullptr;
			}

			ID3D12RootSignature* rootSignature = nullptr;
			hr = device->CreateRootSignature(0, signatureBlob->GetBufferPointer(), signatureBlob->GetBufferSize(), IID_PPV_ARGS(&rootSignature));

			if (FAILED(hr))
			{
				// 创建失败，处理错误
				// ...
				CM_CORE_ASSERT(false, "Create DX12 RootSignature failed!");
				// 返回空指针
				return nullptr;
			}

			return rootSignature;
		}

		UINT numParameters;
		UINT numSamplers;
		std::unique_ptr<RootParameter> parameters = nullptr;
		std::unique_ptr<StaticSamplerDesc> staticSamplers = nullptr;
		ROOT_SIGNATURE_FLAGS rootFlags;
	private:
		static uint16_t index;
	};
}


