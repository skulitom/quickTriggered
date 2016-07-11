struct VSInput
{
	float2 Pos : POSITION;
	float2 TexPos : TEXCOORD;
};

struct VSOut
{

    float4 PosH : SV_POSITION;
    float2 PosW : POS;
	float4 Color : COLOR0;
    float4 AColor : COLOR1;
	float2 TexCoord : TEXCOORD0;
    float2 ATexCoord : TEXCOORD1;
   
};

cbuffer CPPOut : register (b0)
{

	matrix ViewMatrix;
	matrix ProjMatrix;
	matrix WorldMatrix;
    float4 TextureOffset;
    float4 Color;
    float4 AColor;
    float2 Scale;
    uint UseGlobalCoords;
    float3 Pad;

};

VSOut VSMain(VSInput input)
{
	VSOut VOut;
    VOut.Color = Color;
    VOut.AColor = AColor;

    VOut.PosH = mul(float4(input.Pos, 0, 1), WorldMatrix);
    VOut.PosW = VOut.PosH.xy;
    VOut.PosH = mul(VOut.PosH, ViewMatrix);
    VOut.PosH = mul(VOut.PosH, ProjMatrix);
    if(!UseGlobalCoords)
    {
        VOut.TexCoord = input.TexPos + TextureOffset.xy;
        VOut.ATexCoord = input.TexPos + TextureOffset.zw;
    }
    else
    {
        VOut.TexCoord = VOut.PosH.xy + TextureOffset.xy;
        VOut.ATexCoord = VOut.PosH.xy + TextureOffset.zw;
    }

    VOut.TexCoord = VOut.TexCoord / float2(Scale.x, Scale.x);
    VOut.ATexCoord = VOut.ATexCoord / float2(Scale.y, Scale.y);

	return VOut;
}