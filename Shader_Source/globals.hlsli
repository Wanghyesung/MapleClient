cbuffer Transform : register(b0)
{
    //float4 Position;
    //열 우선 행렬
    row_major matrix WorldMatrix;
    row_major matrix ViewMatrix;
    row_major matrix ProjectionMatrix;
}

//.1

cbuffer Grid : register(b2)
{
    float4 CameraPosition;
    float2 CameraScale;
    float2 Resolution;
}

cbuffer Animator : register(b3)
{
    float2 SpriteLeftTop;
    float2 SpriteSize;
    float2 SpriteOffset;
    float2 AtlasSize;
    uint AnimationType;
}

cbuffer ParticleSystem : register(b4)
{
    uint elementCount;
    float elapsedTime;
    float deltaTime;
    int padd2;
}

cbuffer Player : register(b5)
{
    float4 Dir;
    float4 PlayerColor;
}

cbuffer Monster : register(b6)
{
    float4 MonsterDir;
}

cbuffer UI : register(b7)
{
    float4 Size;
}

cbuffer Object : register(b8)
{
    float4 ObjectDir;
    float4 ObjectColor;
}

cbuffer Noise : register(b9)
{
    float4 noiseTextureSize;
}

struct LightAtrribute
{
    float4 color;
    float4 position;
    float4 direction;
    
    uint type;
    float radius;
    float angle;
    int pad;
    
};

struct Particle
{
    float4 position;
    float4 direction;
    
    float endTime;
    float time;
    float speed;
    uint active;
};

struct ParicleShared
{
    uint ActiveSharedCount;
};

StructuredBuffer<LightAtrribute> lightsAttribute : register(t13);
StructuredBuffer<Particle> particles : register(t14);

//SamplerState에서는 유한한 픽셀 크기를 가질 수 밖에 없는 텍스쳐의 각 픽셀 사이를 어떻게 처리할 것인지 결정하는 State인 것이다. (UV좌표로 변환)
Texture2D albedoTexture : register(t0);
Texture2D atlasTexture : register(t12);
Texture2D noiseTexture : register(t15);

SamplerState pointSampler : register(s0);
SamplerState anisotropicSampler : register(s1);

static float GaussianFilter[5][5] =
{
    0.003f, 0.0133f, 0.0219f, 0.0133f, 0.003f,
    0.0133f, 0.0596f, 0.0983f, 0.0596f, 0.0133f,
    0.0219f, 0.0983f, 0.1621f, 0.0983f, 0.0219f,
    0.0133f, 0.0596f, 0.0983f, 0.0596f, 0.0133f,
    0.003f, 0.0133f, 0.0219f, 0.0133f, 0.003f,
};

float4 GaussianBlur(float2 UV)
{
    float4 Out = (float4) 0.0f;
    
    if (1.f < UV.x)
        UV.x = frac(UV.x);
    else if (UV.x < 0.0f)
        UV.x = 1.0f + frac(UV.x);
        
    if (1.f < UV.y)
        UV.y = frac(UV.y);
    else if (UV.y < 0.0f)
        UV.y = 1.0f + frac(UV.y);
    
    int2 iUV = UV * noiseTextureSize.xy;
    iUV -= int2(2, 2);
    
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            int2 idx = int2(iUV.y + i, iUV.x + j);
            Out += noiseTexture[idx] * GaussianFilter[i][j];
        }
    }
    
    return Out;
}


void CalculateLight2D(in out float4 lightColor, float3 position, int idx)
{
    if(0 == lightsAttribute[idx].type)
    {
        //바로 모든 색에 인자로 들어온 color값 넣기
        lightColor += lightsAttribute[idx].color;
    }
    
    else if( 1== lightsAttribute[idx].type)
    {
        float fLen = distance(position.xy, lightsAttribute[idx].position.xy);
        
        if(fLen < lightsAttribute[idx].radius)
        {
            //lightarribute 위치에 가까운 위치일수록 밝게 보이게
            float fRatio = 1.f - (fLen / lightsAttribute[idx].radius);
            lightColor += lightsAttribute[idx].color * fRatio;
        }
    }
    else if (2 == lightsAttribute[idx].type)
    {
        float fLen = distance(position.xy, lightsAttribute[idx].position.xy);
        
        if (fLen < lightsAttribute[idx].radius)
        {
            float fRatio = 1.f - (fLen / lightsAttribute[idx].radius);
            lightColor -= lightsAttribute[idx].color * fRatio;
        }
    }
    else
    {
        lightColor = float4(1.f, 1.f, 1.f, 1.f);
    }
    
}