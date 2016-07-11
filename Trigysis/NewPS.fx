//#include <PSInputs.fx>


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
    uint2 Sizes;
    Texture.GetDimensions(Sizes.x, Sizes.y);

    float4 PTexture = Texture.Sample(Sampler, input.TexCoord) + input.Color;
    //float4 PATexture = ATexture.Sample(Sampler, input.ATexCoord) + input.AColor;


    if(UVal2)
    {
        
        if (input.TexCoord.x < 0.2)
        {
		
            PTexture = float4(0, 0.1f - input.TexCoord.x / 2, 0.1f - input.TexCoord.x, 1.f);
	
        }
        if (1 - input.TexCoord.x < 0.2)
        {
		
            PTexture = float4(0, -(0.8 - input.TexCoord.x), -(0.8 - input.TexCoord.x), 1.f);
	
        }
	
    }

    float2 MPos = float2(UVal0, UVal1);
    float Len = length(input.PosW - MPos);
    if ((UVal2 == 1 && Len < 50) || UVal2 == 2)
    {
        PTexture = lerp(Texture.Sample(Sampler, input.TexCoord + (Len) / 50), PTexture, (Len) / 50);
    }

    if (UseAlpha)
    {

        clip(PTexture.a - 0.1f);
        
    }

    return PTexture;

    //return float4(lerp(PTexture.xyz, PATexture.xyz, 0.5f), 1);

}