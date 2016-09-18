
SamplerState Sampler : register(s0);

Texture2D Texture : register(t0);
Texture2D ATexture : register(t1);

cbuffer CPPOutput : register(b0)
{
	// 8 + 4 + 4 = 16 
	float Time;
	float DeltaTime;
	uint UseAlpha;
	float Pad;
	float UVal0;
	float UVal1;
	float UVal2;
	float UVal3;
};

struct PSInput
{

	float4 PosH : SV_POSITION;
	float2 PosW : POS;
	float4 Color : COLOR0;
	float4 AColor : COLOR1;
	float2 TexCoord : TEXCOORD0;
	float2 ATexCoord : TEXCOORD1;

};
float4 PSMain(PSInput input) : SV_Target
{

	float4 PFig = Texture.Sample(Sampler, input.TexCoord);
	PFig = float4(lerp(PFig.rgb, input.Color.rgb, 0.7).rgb, PFig.a * (0.7 + abs(cos(Time*0.5) * 0.2)));
	PFig.rgb = PFig.rgb * 2 * (0.7 + abs(sin(Time) * 0.2f)).rrr;

	clip(PFig.a - 0.1f);

	return PFig;
}