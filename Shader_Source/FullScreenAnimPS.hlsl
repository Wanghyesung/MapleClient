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
float4 main(VSOut In) : SV_TARGET
{
    float4 color = (float4) 0.0f;
    
    // 1200 1032 // 120 130
    // 1080 -> 540
    // -540 + 1200 
    
    color = albedoTexture.Sample(anisotropicSampler, In.UV);
    if (AnimationType == 1)
    {
        // 1) In.UV ∈ [0,1] → 스프라이트 내부 UV
        float2 spriteUV = SpriteLeftTop 
                        + (In.UV * SpriteSize)
                        + SpriteOffset;

        // 2) 스프라이트 외부는 잘라내기
        if (spriteUV.x < 0 || spriteUV.x > 1 ||
            spriteUV.y < 0 || spriteUV.y > 1)
        {
            discard;
        }

        // 3) 올바른 UV로 샘플
        color = atlasTexture.Sample(anisotropicSampler, spriteUV);
        color *= ObjectColor;
        
        if (color.a <= 0.0f)
            discard;
    }
    
    return color;
}