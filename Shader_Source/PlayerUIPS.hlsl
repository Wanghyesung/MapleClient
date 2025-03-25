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

//Texture2D albedoTexture : register(t0);
////SamplerState에서는 유한한 픽셀 크기를 가질 수 밖에 없는 텍스쳐의 각 픽셀 사이를 어떻게 처리할 것인지 결정하는 State인 것이다. (UV좌표로 변환)
//SamplerState pointSampler : register(s0);
//SamplerState anisotropicSampler : register(s1);

//렌더 타겟으로
float4 main(VSOut In) : SV_TARGET
{
    //return In.Color;
    float4 color = (float4) 0.f;
    //들어오는 UV좌표로 텍스쳐 보간해서 리턴
    //cos(100.0f);
    
    //dot()
    float fRatio = Size.x / 100.f;
    if (In.UV.x > fRatio)
        discard;
    
    color = albedoTexture.Sample(pointSampler, In.UV);
    
    if (color.a <= 0.0f)
        discard;
    
    return color;
}