#include "globals.hlsli"
RWStructuredBuffer<Particle> ParticleBuffer : register(u0);
RWStructuredBuffer<ParicleShared> ParticleSharedBuffer : register(u1);

[numthreads(128, 1, 1)]
void main( uint3 DTid : SV_DispatchThreadID )
{
    //128
    if (elementCount <= DTid.x)
        return;
    
    
    if (ParticleBuffer[DTid.x].active == 0)
    {
        while (0 < ParticleSharedBuffer[0].ActiveSharedCount)
        {
            int origin = ParticleSharedBuffer[0].ActiveSharedCount;
            int exchange = origin - 1;
            
            // 쓰레드 동기화 Interlock 관련 함수
            //InterlockedExchange(ParticleSharedBuffer[0].ActiveSharedCount
            //    , exchange, exchange);
            
            //대상을 비교 값과 개별적으로 비교합니다. 동일한 경우 대상을 입력 값으로 덮어씁니다.
            //원래 값은 대상의 원래 값으로 설정됩니다.
            //대상값, 비교깂 입력값 원래값
            InterlockedCompareExchange(ParticleSharedBuffer[0].ActiveSharedCount,
            origin, exchange, exchange);
            
            if(origin == exchange)
            {
                ParticleBuffer[DTid.x].active = 1;
                break;
            }
            
            // 랜덤값으로 위치와 방향을 설정한다.
            // 샘플링을 시도할 UV 를 계산한다.
            float4 vRandom = (float4) 0.f;
            
            float2 vUV = float2((float) DTid.x / elementCount, 0.5f);
            vUV.x += elapsedTime;
            vUV.y += sin((vUV.x + elapsedTime) * 3.141592f + 2.f * 10.f) * 0.5f;
            
            vRandom = float4
            (
            GaussianBlur(vUV + float2(0.f, 0.f)).x
                , GaussianBlur(vUV + float2(0.1f, 0.f)).x
                , GaussianBlur(vUV + float2(0.2f, 0.f)).x
                , GaussianBlur(vUV + float2(0.3f, 0.f)).x
            );

            ParticleBuffer[DTid.x].position.xyz = vRandom.xyz * 3.0f * deltaTime;
            ParticleBuffer[DTid.x].position.x -= 0.65f;
            ParticleBuffer[DTid.x].position.y -= 1.4f;
            ParticleBuffer[DTid.x].position.z = 0.0f;
           
            
            ParticleBuffer[DTid.x].endTime = vRandom.xyz * 10.0f;
            ParticleBuffer[DTid.x].speed = vRandom.xyz * 2.0f;
        }
    }
    else
    {
        if (ParticleBuffer[DTid.x].time >= ParticleBuffer[DTid.x].endTime)
        {
            ParticleBuffer[DTid.x].active = 0;
            ParticleBuffer[DTid.x].time = 0.f;

        }
        else
        {
            ParticleBuffer[DTid.x].position 
           += ParticleBuffer[DTid.x].direction * ParticleBuffer[DTid.x].speed * deltaTime;

            ParticleBuffer[DTid.x].time += deltaTime;
        }

    }
     
}