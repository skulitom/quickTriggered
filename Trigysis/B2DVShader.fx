
struct VSInput
{
	float2 Pos : POSITION;
	float4 Color : COLOR;
	float2 TexPos : TEXCOORD;
};

struct VSOut
{
	float4 PosH : SV_POSITION;
	float4 Color : COLOR;
	float2 TexPos : TEXCOORD;
};

cbuffer LowFUpdate : register (b0)
{
	matrix ViewMatrix;
	matrix ProjMatrix;
	matrix WorldMatrix;
};

VSOut VSMain(VSInput input)
{
	VSOut VOut;
	VOut.Color = input.Color;
	VOut.PosH = mul(float4(input.Pos,0, 1), WorldMatrix);
	VOut.PosH = mul(VOut.PosH, ViewMatrix);
	VOut.PosH = mul(VOut.PosH, ProjMatrix);
	VOut.TexPos = input.TexPos;
	return VOut;
}