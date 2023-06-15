#include "hzpch.h"
#include "Shader.h"
#include <d3dcompiler.h>


namespace ColaMan {
	Shader::Shader(const std::wstring& filename,const D3D_SHADER_MACRO* defines,
		const std::string& entrypoint,
		const std::string& target)
	{
		UINT compileFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)  
		compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

		HRESULT hr = S_OK;

		ComPtr<ID3DBlob> errors;
		hr = D3DCompileFromFile(filename.c_str(), defines, D3D_COMPILE_STANDARD_FILE_INCLUDE,
			entrypoint.c_str(), target.c_str(), compileFlags, 0, &byteCode, &errors);

		if (errors != nullptr)
		{
			OutputDebugStringA((char*)errors->GetBufferPointer());
			CM_CORE_ERROR("{0}", (char*)errors->GetBufferPointer());
			CM_CORE_ASSERT(false, "Shader compilation failure!");
		}
	}
	Shader::~Shader()
	{
		byteCode = nullptr;
	}

	D3D12_SHADER_BYTECODE Shader::Bound()
	{
		return { reinterpret_cast<BYTE*>(byteCode->GetBufferPointer()),
			byteCode->GetBufferSize() };
	}
}
