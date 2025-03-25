//∫§≈Õ∑Œ ≥—∞‹¡Ÿ∞≈¿” float4 æ∆¥‘
//struct Vertex[3]
//{
//    Vector3 pos;
//    Vector4 color;
//};

struct VSIn
{
    //Ω√∏‡∆Ω¿∏∑Œ ±∏∫–
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

cbuffer Transform : register(b0)
{
    float4 Position;
}


VSOut main(VSIn In)
{
    VSOut Out = (VSOut)0.0f;//√ ±‚»≠
    
    Out.Pos = float4(In.Pos, 1.0f);
    
    //Out.Pos.z *= Pos.z;
    //Out.Pos.x *= Pos.z;
    //Out.Pos.y *= Pos.z;
    
    //Out.Pos.x += Pos.x;
    //Out.Pos.y += Pos.y;
    //
    //Out.Color = In.Color;
    Out.UV = In.UV;
    //Out.UV.x += 0.2f;
    Out.Color = In.Color;

    return Out;
}