#include "globals.hlsli"

struct VSIn
{
    float3 Pos : POSITION;
    float2 UV : TEXCOORD;
};

struct VSOut
{
    float4 Pos : SV_Position;
    float2 UV : TEXCOORD;
    float2 GridPos : POSITION;
};

VSOut main(VSIn In)
{
    VSOut Out = (VSOut) 0.f;
    float2 gridPos = float2(0.f, 0.f);
    gridPos.x = In.Pos.x  * Resolution.x + CameraPosition.x * CameraScale.x;
    gridPos.y = In.Pos.y  * Resolution.y + CameraPosition.y * CameraScale.y;
    
    const float meshScale = 2.f;
    Out.Pos = float4(In.Pos.xy * meshScale, 0.999f, 1.f);//가장 뒷쪽에 그리게
    Out.UV = In.UV;
    Out.GridPos = gridPos;
    
    return Out;
}