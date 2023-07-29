/**-------------------------------------------
* 洗い出された接点から、テクスチャのデータをペンのテクスチャで書き換える
---------------------------------------------*/

#define WIDE_MENBER 16

SamplerState g_sampler : register(s0);	// サンプラー
// ハイトマップ
RWTexture2D<float> g_heightMap : register(u0);
// 法線マップ
RWTexture2D<float4> g_nomalMap : register(u1);
// カラーマップ(1テレインにつき4レイヤーまで)
RWTexture2D<float4> g_colorMap : register(u1);

// ペンテクスチャ
Texture2D g_penTexture:register(t0);

cbuffer ConstantUpdateMapProperty : register(b11)
{
    // xy:uv z:range w:係数
    float4 UVAndRangeAndCoef;
    // セットするID x:テクスチャID y:TypeID 
	float4 SetId;
};

// 構造体
[numthreads(1,1,1)]
void CS_Main(   
                uint3 did : SV_DispatchThreadID
            )
{
    // x:テクスチャXサイズ y:テクスチャYサイズ
	uint2 MapInfo;

    g_heightMap.GetDimensions(MapInfo.x,MapInfo.y);
    
    uint2 loopsize;
    loopsize.x = MapInfo.x / WIDE_MENBER;
    loopsize.y = MapInfo.y / WIDE_MENBER;

    int2 pos;
    pos.x = UVAndRangeAndCoef.x - UVAndRangeAndCoef.z;
    pos.y = UVAndRangeAndCoef.y - UVAndRangeAndCoef.z;

    pos.x = pos.x / loopsize.x + step(pos.x % loopsize.x,1);
    pos.y = pos.y / loopsize.y + step(pos.y % loopsize.y,1);

    pos.x=pos.x*loopsize.x+loopsize.x*did.x;
    pos.y=pos.y*loopsize.y+loopsize.y*did.y;

    uint maxx = min(pos.x+loopsize.x,UVAndRangeAndCoef.x + UVAndRangeAndCoef.z-1);
    uint maxy = min(pos.y+loopsize.y,UVAndRangeAndCoef.y + UVAndRangeAndCoef.z-1);

    pos.x=max(pos.x,UVAndRangeAndCoef.x - UVAndRangeAndCoef.z);
    pos.y=max(pos.y,UVAndRangeAndCoef.y - UVAndRangeAndCoef.z);
    // 1パッチ分更新するが、パッチの場所を割り出さないといけない
    // これで更新すべきパッチ部分のPOSITIONがわかった
 
    float2 uv;
    float4 pencol;

    for (uint x = pos.x; x < maxx; x++)
    {       
        for (uint y = pos.y; y < maxy; y++)
        {
            uv.x=((float)UVAndRangeAndCoef.x + UVAndRangeAndCoef.z-(float)x)/((float)UVAndRangeAndCoef.z*2.0f);
            uv.y=((float)UVAndRangeAndCoef.y + UVAndRangeAndCoef.z-(float)y)/((float)UVAndRangeAndCoef.z*2.0f);

            pencol=g_penTexture.SampleLevel(g_sampler,uv,0);
            g_heightMap[uint2(x,y)] += pencol.a*UVAndRangeAndCoef.w;
            float4 tmp={g_nomalMap[uint2(x,y)].x,g_nomalMap[uint2(x,y)].y,g_nomalMap[uint2(x,y)].z,pencol.a*SetId.x+(1.0f-pencol.a)*g_nomalMap[uint2(x,y)].w};
            g_nomalMap[uint2(x,y)]=tmp;
        }
    }

    // 一片全スレッド高さ変更待ち
    GroupMemoryBarrierWithGroupSync();

    for (x = pos.x; x < maxx; x++)
    {       
        for (uint y = pos.y; y < maxy; y++)
        {

            float3 du = { 1, 0, (g_heightMap[uint2(x+1,y)] - g_heightMap[uint2(x-1,y)])};
            float3 dv = { 0, 1, (g_heightMap[uint2(x,y+1)] - g_heightMap[uint2(x,y-1)])};

            float3 vr = normalize(cross(du, dv)) * 0.75 + 0.25;
            float4 tmp={vr.x,vr.y,vr.z,g_nomalMap[uint2(x,y)].w};
            g_nomalMap[uint2(x,y)]=tmp;
            
        }
    }
}