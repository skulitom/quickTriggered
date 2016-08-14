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

    float4 PTexture = Texture.Sample(Sampler, input.TexCoord)+ input.Color;

    //if(UseAlpha)
        //clip(PTexture - 0.5f);
    float Smooth;
    Smooth = clamp(UVal3, 0, 1);
    if(input.TexCoord.x < Sizes.x * 0.5f)
    {
        
        PTexture = lerp(PTexture, Texture.Sample(Sampler, input.TexCoord + float2(1.f / Sizes.x, 0)), Smooth) + input.Color;

    }
    else
    {
        
        PTexture = lerp(PTexture, Texture.Sample(Sampler, input.TexCoord - float2(1.f / Sizes.x, 0)), Smooth) + input.Color;

    }

    if (input.TexCoord.y < Sizes.y * 0.5f)
    {
        
        PTexture = lerp(PTexture, Texture.Sample(Sampler, input.TexCoord + float2(0, 1.f / Sizes.y)), Smooth) + input.Color;

    }
    else
    {
        
        PTexture = lerp(PTexture, Texture.Sample(Sampler, input.TexCoord - float2(0, 1.f / Sizes.y)), Smooth) + input.Color;

    }

    //if (length(input.PosW - float2(UVal0, UVal1)) < 100)
        //PTexture = lerp(PTexture, Texture.Sample(Sampler, input.TexCoord + float2(sin(Time) * sin(Time * 50 * input.TexCoord.y), 0) / 100.f), 100 / length(input.PosW - float2(UVal0, UVal1)));
    return PTexture;

}