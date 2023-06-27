//***************************************************************************************
// color.hlsl by Frank Luna (C) 2015 All Rights Reserved.
//
// Transforms and colors geometry.
//***************************************************************************************

struct VertexIn
{
	float3 PosL  : POSITION;
	float4 ColorL :COLOR;
};

struct VertexOut
{
	float4 PosH  : SV_POSITION;
	float4 Pos :POSITION;
	float4 Color:COLOR;
};

VertexOut VS(VertexIn vin)
{
	VertexOut vout;
	
	// Transform to homogeneous clip space.
	vout.PosH = float4(vin.PosL, 1.0f);
	vout.Pos = vout.PosH+0.5f;
	// Just pass vertex color into the pixel shader.
    //vout.Color = vin.Color;
	vout.Color = vin.ColorL;
    return vout;
}

float4 PS(VertexOut pin) : SV_Target
{
    return float4(pin.Color.xyz,1);
}


