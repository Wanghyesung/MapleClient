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
    float3 WorldPos : POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

//렌더 타겟으로
float4 main(VSOut In) : SV_TARGET
{
    //return In.Color;
    float4 color = (float4) 0.f;
    //들어오는 UV좌표로 텍스쳐 보간해서 리턴
    //cos(100.0f);
    
    //dot()
    
    color = albedoTexture.Sample(pointSampler, In.UV);
  
    if (color.a <= 0.0f)
        discard;
    
    return color;
}