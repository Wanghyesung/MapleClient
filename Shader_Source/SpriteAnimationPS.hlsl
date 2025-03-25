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


float4 main(VSOut In) : SV_TARGET
{
    float4 color = (float4) 0.0f;
    
    // 1200 1032 // 120 130
    // 1080 -> 540
    // -540 + 1200 
    
    color = albedoTexture.Sample(anisotropicSampler, In.UV);
    if (AnimationType == 1)
    {
        // lt : 1
        // sz = -0.25
        //diff = -0.13  0.375     0.625
        
        float2 diff = (AtlasSize - SpriteSize) / 2.0f;
        float2 UV = (SpriteLeftTop - diff - SpriteOffset)
                + (AtlasSize * In.UV);
    
        if (UV.x < SpriteLeftTop.x || UV.x > SpriteLeftTop.x + SpriteSize.x
            || UV.y < SpriteLeftTop.y || UV.y > SpriteLeftTop.y + SpriteSize.y)
            discard;
      
        UV.x *= Dir.x;
      
   
        color = atlasTexture.Sample(anisotropicSampler, UV);

        color *= PlayerColor;
        
        float4 lightColor = float4(1.f, 1.f, 1.f, 1.f);
    
        for (int i = 0; i < 2; i++)
        {
            CalculateLight2D(lightColor, In.WorldPos, i);
        }
    
        color *= lightColor;

        if (color.a <= 0.0f)
            discard;
        
    }
    
    return color;
}