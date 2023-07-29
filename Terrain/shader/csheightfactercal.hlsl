/**-------------------------------------------
* 高さマップからパッチごとの係数に必要な情報を計算して出す
---------------------------------------------*/

#define WIDE_MENBER 16

SamplerState g_sampler : register(s0);	// サンプラー。CLAMPを使うべし。

// ハイトマップ。型をfloatにすること
Texture2D<float> g_heightMap : register(t0);

// パッチ内の高さの全合成、最高値、最低値、最大高低差
struct Anser
{
    float4 factor;
};

RWStructuredBuffer<Anser> stbuf : register(u0);

[numthreads(WIDE_MENBER,1,1)]
void CS_Main(   
                uint3 did : SV_DispatchThreadID,
                uint3 gtd : SV_GroupThreadID,   // Y方向とする
                uint3 gid : SV_GroupID          // X方向とする
            )
{
    // このスレッドの最近接点初期化
    stbuf[did.x].factor.x = 0;
    stbuf[did.x].factor.y = 0;
    stbuf[did.x].factor.z = 0;
    stbuf[did.x].factor.w = 0;    

    // テクスチャサイズの情報取得と、1パッチの大きさを計算
    uint2 texsize;

    g_heightMap.GetDimensions(texsize.x,texsize.y);
    uint divsizex =texsize.x / WIDE_MENBER;
    uint divsizey =texsize.y / WIDE_MENBER;


    // パッチ内の高さを全合成、最高値、最低値、最大高低差の計算する
    float h=0;
    float4 tmpf4;
    float2 uv;
    for (uint y = 0; y < divsizey; y++)
    {       
        for (uint x = 0; x < divsizex; x++)
        {       
            uv.x=(float)(x+gid.x*divsizex)/(float)texsize.x;
            uv.y=(float)(y+gtd.x*divsizey)/(float)texsize.y;
       
            h = g_heightMap.SampleLevel(g_sampler,uv,0);
            stbuf[did.x].factor.x += h;
            
            stbuf[did.x].factor.y = max(stbuf[did.x].factor.y,h);
            stbuf[did.x].factor.z = min(stbuf[did.x].factor.z,h);
            
            uv.x=(float)(x+gid.x*divsizex)/(float)texsize.x;
            uv.y=(float)(y+1+gtd.x*divsizey)/(float)texsize.y;
       
            tmpf4.x = g_heightMap.SampleLevel(g_sampler,uv,0);

            uv.x=(float)(x+1+gid.x*divsizex)/(float)texsize.x;
            uv.y=(float)(y+gtd.x*divsizey)/(float)texsize.y;
       
            tmpf4.y = g_heightMap.SampleLevel(g_sampler,uv,0);

            uv.x=(float)(x-1+gid.x*divsizex)/(float)texsize.x;
            uv.y=(float)(y+gtd.x*divsizey)/(float)texsize.y;

            tmpf4.z = g_heightMap.SampleLevel(g_sampler,uv,0);                   
            
            uv.x=(float)(x+gid.x*divsizex)/(float)texsize.x;
            uv.y=(float)(y-1+gtd.x*divsizey)/(float)texsize.y;
       
            tmpf4.w = g_heightMap.SampleLevel(g_sampler,uv,0);

            stbuf[did.x].factor.w = abs( h - tmpf4.x );
            stbuf[did.x].factor.w = max(stbuf[did.x].factor.w,abs( h - tmpf4.y ));
            stbuf[did.x].factor.w = max(stbuf[did.x].factor.w,abs( h - tmpf4.z ));
            stbuf[did.x].factor.w = max(stbuf[did.x].factor.w,abs( h - tmpf4.w ));
        }
    }

    stbuf[did.x].factor.x /= divsizex * divsizey;
}