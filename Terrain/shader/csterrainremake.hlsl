/**-------------------------------------------
* ハイトマップのテクスチャをノイズで生成する
---------------------------------------------*/
#include	"common.hlsl"

// noise https://karanokan.info/2019/02/16/post-2202/

float2 rand(float2 st, int seed)
{
    float2 s = float2(dot(st, float2(127.1, 311.7)) + seed, dot(st, float2(269.5, 183.3)) + seed);
    return -1 + 2 * frac(sin(s) * 43758.5453123);
}
 
float noise(float2 st, int seed)
{
    float2 p = floor(st);
    float2 f = frac(st);
 
    float w00 = dot(rand(p, seed), f);
    float w10 = dot(rand(p + float2(1, 0), seed), f - float2(1, 0));
    float w01 = dot(rand(p + float2(0, 1), seed), f - float2(0, 1));
    float w11 = dot(rand(p + float2(1, 1), seed), f - float2(1, 1));
				
    float2 u = f * f * (3 - 2 * f);
 
    return lerp(lerp(w00, w10, u.x), lerp(w01, w11, u.x), u.y);
}

#define WIDE_VALUE 1024

// ハイトマップ
RWTexture2D<float> g_heightMap : register(u0);

[numthreads(1,1,1)]
void CS_Main(   
                uint3 did : SV_DispatchThreadID
            )
{     
    float2 uv;

    uv.y = (float) did.x / (float) WIDE_VALUE;
    
    for (uint x = 0; x < WIDE_VALUE; x++)
    {       
        uv.x = (float) x / (float) WIDE_VALUE;

        g_heightMap[uint2(x, did.x)] = noise(uv * EditProperty.x, EditProperty.y);
    }

    // 一旦全スレッド高さ変更待ち
    GroupMemoryBarrierWithGroupSync();
}