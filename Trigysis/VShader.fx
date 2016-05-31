
struct VSInput
{

	float2 Pos : POSITION;
	float2 TexCoord : TEXCOORD;

};

struct VSOut
{

	float4 PosH : SV_POSITION;
	float2 PosW : Pos;
	float2 TexCoord : TEXCOORD;
	float4 Color : COLOR;

};

cbuffer LowFUpdate : register (b0)
{

	matrix ViewMatrix;
	matrix ProjMatrix;
	matrix WorldMatrix;
	float4 Color;

};

VSOut VSMain(VSInput input)
{

	VSOut VOut;

	//input.Pos = input.Pos.xy * 350;

	VOut.PosH = mul(float4(input.Pos,0, 1), WorldMatrix);
	VOut.PosH = mul(VOut.PosH, ViewMatrix);
	VOut.PosH = mul(VOut.PosH, ProjMatrix);

	float4 PrePosW = mul(float4(input.Pos, 0, 1), WorldMatrix);

	VOut.PosW = PrePosW.xy;
	VOut.TexCoord = input.TexCoord;

	VOut.Color = Color;

	return VOut;

}