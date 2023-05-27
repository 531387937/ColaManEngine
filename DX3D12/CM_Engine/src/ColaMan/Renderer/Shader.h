#pragma once

#include <string>
#include <d3d12.h>

using namespace Microsoft::WRL;
namespace ColaMan{
	class Shader
	{
	public:
		Shader(const std::wstring& filename, const D3D_SHADER_MACRO* defines,
			const std::string& entrypoint,
			const std::string& target);
		~Shader();

		void Bind() const;
		void UnBind() const;
	private:
		ComPtr<ID3DBlob> byteCode = nullptr;
	D3D12_SHADER_BYTECODE operator= (const Shader& other) {
		return { reinterpret_cast<BYTE*>(other.byteCode->GetBufferPointer()),
		other.byteCode->GetBufferSize() };
	}
	};
}