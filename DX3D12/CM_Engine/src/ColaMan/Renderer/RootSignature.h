#pragma once
namespace ColaMan
{
	struct RootSignature
	{
	public:
		uint16_t rootSignatureIndex;
		RootSignature() = default;
	private:
		static uint16_t index;
	};
}


