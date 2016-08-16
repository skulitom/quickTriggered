
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
    float4 PFig = ATexture.Sample(Sampler, input.TexCoord) + input.Color;

    
    //if (PHex.r < 1.f)
    //{
    //    PFig.rgb = lerp(float3(0.2, 0.8, 0.2), PFig.rgb, PHex.r);
    //}

    PFig.a = PHex.a;

    //if(PFig.a < 1.f)
        //PFig.rgb = lerp(PFig.rbg, float3(1.f, 1.f, 0.f), 1 - PFig.a);

    clip(PFig.a - 0.1f);
    
    return PFig;
}