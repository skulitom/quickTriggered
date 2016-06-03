
SamplerState Sampler : register(s0);
Texture2D Texture : register(t0);

struct PSInput
{

	float4 PosH : SV_POSITION;
	float4 Color : COLOR;
	float2 TexPos : TEXCOORD;

};

float4 PSMain(PSInput input) : SV_TARGET
{
	
	float4 Color = input.Color + Texture.Sample(Sampler, input.TexPos);

	clip(Color.a - 0.5f);

	return Color;

}