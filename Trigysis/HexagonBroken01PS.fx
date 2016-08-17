
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

    float4 PHex = Texture.Sample(Sampler, input.TexCoord);
    float4 PFig = ATexture.Sample(Sampler, input.TexCoord);

    if(UVal0 == 0)
        PFig.a = PHex.r * (1 - (bool) PHex.g) * (1 - (bool) PHex.b);
    else if(UVal0 == 1)
        PFig.a = PHex.g * PHex.b * (1 - (bool) PHex.r);
    else if(UVal0 == 2)
        PFig.a = PHex.g * (1 - (bool) PHex.r) * (1 - (bool) PHex.b);
    else if(UVal0 == 3)
        PFig.a = PHex.r * PHex.g * (1 - (bool) PHex.b);
    else if(UVal0 == 4)
        PFig.a = PHex.r * PHex.b * (1 - (bool) PHex.g);

    PFig.a = PFig.a * PHex.a;

    clip(PFig.a - 0.1f);
    
    return PFig + input.Color;
}