
cbuffer PerFrame : register (b0)
{

	float2 BrushPos;

};

Texture2D SampleTexture : register(t0);
SamplerState RenderSampler : register(s0);

RWTexture2D<unsigned int> MemoryText;

struct PSInput
{

	float4 PosH : SV_POSITION;
	float2 PosW : Pos;
	float2 TexCoord : TEXCOORD;
	float4 Color : COLOR;

};

float4 PSMain(PSInput input) : SV_TARGET
{
	
	input.PosH.w = 1.f;

	float2 DistVec = input.PosW - BrushPos;

	float Dist = length(DistVec);

	float4 TextureColor = SampleTexture.Sample(RenderSampler, input.TexCoord);

	float4 ColorOut = float4(1.f / Dist, 0, 0, 1) + input.Color + TextureColor;
	//ColorOut.a = TextureColor.a;
	//clip(ColorOut.a - 0.1f);

	//MemoryText[input.PosH.xy] = ColorOut;

	return ColorOut;

}