
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
        VOut.TexCoord = input.TexPos / Scale.xx + TextureOffset.xy;
        VOut.ATexCoord = input.TexPos / Scale.yy + TextureOffset.zw;
    }
    else
    {
        VOut.TexCoord.x = input.TexPos.x * WorldMatrix._11 / (512 * Scale.x)+ TextureOffset.x;
        VOut.TexCoord.y = input.TexPos.y * WorldMatrix._22 / (512 * Scale.x) + TextureOffset.y;

        VOut.ATexCoord.x = input.TexPos.x * WorldMatrix._11 / (512 * Scale.y) + TextureOffset.z;
        VOut.ATexCoord.y = input.TexPos.y * WorldMatrix._22 / (512 * Scale.y) + TextureOffset.w;
    }

    VOut.TexCoord = VOut.TexCoord ;
    VOut.ATexCoord = VOut.ATexCoord ;

	return VOut;
}