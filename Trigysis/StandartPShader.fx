//#include "PSInputs.fx"


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
	
    float4 PTexture = Texture.Sample(Sampler, input.TexCoord ) + input.Color;
    float4 PATexture = ATexture.Sample(Sampler, input.ATexCoord) + input.AColor;

    if(UseAlpha)
    {

        clip(PTexture.a - 0.5f);
        if (PATexture.a != 0)
            clip(PATexture.a - 0.5f);
        else
            return PTexture;
        
            

    }
    else
    {
        if(PATexture.r == 0 && PATexture.g == 0 && PATexture.b == 0 && PATexture.a == 0)
            return PTexture;

    }
    //return PTexture;
    return float4(lerp(PTexture.xyz, PATexture.xyz, 0.5f), 1);

}