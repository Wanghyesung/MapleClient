#include "globals.hlsli"

struct VSIn
{
    float3 Pos : POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

struct VSOut
{
    float4 Pos : SV_Position;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};


VSOut main(VSIn In)
{
    VSOut Out = (VSOut) 0.0f;
    
    //ÇÈ¼¿ ÁÂÇ¥
 
    float4 vPos = float4(In.Pos * 2.0f, 1.0f);
   
    Out.Pos = vPos;
    Out.UV = In.UV;
    
    return Out;
}