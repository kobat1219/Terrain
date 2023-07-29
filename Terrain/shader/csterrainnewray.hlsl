/**-------------------------------------------
* 地形データテクスチャから
* 選択ピクセル(頂点インデックス番号)を選び出す
* こんなんいらくて、頂点のポイントからワールド座標だして、
* それをスクリーン座標に変えて、カーソルポイントとの距離で近い頂点を選んで
* その選ばれた頂点で一番カーソルに近いやつを選択すればOKってことやわ
---------------------------------------------*/

#define WIDE_MENBER 64

SamplerState g_sampler : register(s1);	// サンプラー

// ハイトマップ
Texture2D<float> g_heightMap : register(t0);

cbuffer ConstantMapProperty : register(b10)
{
    // xyz:テレインワールド座標 w:地面隙間サイズ
    float4 World;
    // カメラSpos
	float4 StartPos;
    // カメラベクトル
    float4 EVec;
};

struct Anser
{
    float4 crosspos;
};

RWStructuredBuffer<Anser> stbuf : register(u0);

// 構造体
[numthreads(WIDE_MENBER,1,1)]
void CS_Main(   
                uint3 did : SV_DispatchThreadID,    // did.xが走査線のラインID
                uint3 gtd : SV_GroupThreadID,       // gtd.xが走査線グループ内スレッド
                uint3 gid : SV_GroupID
            )
{
    // x:テクスチャXサイズ y:テクスチャYサイズ
	uint2 MapInfo;

    g_heightMap.GetDimensions(MapInfo.x,MapInfo.y);

    // このスレッドの最近接点初期化
    stbuf[did.x].crosspos.w = -1.0f;
    // stbuf[did.x].crosspos.x = StartPos.x;
    // stbuf[did.x].crosspos.z = EVec.y;
    float3      p1;

    // 頂点ワールド座標X = スレッドID(縦側になる) * 頂点間幅 - テクスチャ幅 / 2 * 頂点間幅 + テレインワールド座標
    p1.z = (did.x * World.w) + World.z - (MapInfo.y * World.w / 2); 

    float wwideinfo = World.x - (MapInfo.x * World.w / 2); 
    float2 uvoneval;
    uvoneval.x = 1.0f / (float)MapInfo.x;
    uvoneval.y = 1.0f / (float)MapInfo.y;

    // スレッドグループで分割数分けして
    // 横16スレッドグループ使用(これはテクスチャサイズによって変わる)
    // 縦64スレッド
    // つまり1024スレッド使用
    // テクスチャ幅/スレッド幅
    float2 uv;    
    for (uint x = 0; x < MapInfo.x; x++)
    {       
        // 頂点ワールド座標X = 頂点X番号 * 頂点間幅 - テクスチャ幅 / 2 * 頂点間幅 + テレインワールド座標
        p1.x = (x * World.w) + wwideinfo;
        
        // 頂点ワールド座標y = uvからハイトマップをサンプル
        
        uv.x = (float)x * uvoneval.x;
        uv.y = (float)did.x * uvoneval.y;

        p1.y = g_heightMap.SampleLevel(g_sampler,uv,0);

        float lenSqv = (EVec.x * EVec.x) + (EVec.y * EVec.y) + (EVec.z * EVec.z);
        float tans = 0.0f;
        if (lenSqv > 0.0f)
        {
            float3 _p1 = {
                p1.x - StartPos.x,
                p1.y - StartPos.y,
                p1.z - StartPos.z
            };

            tans = dot(EVec.xyz, _p1) / lenSqv;
        }
        float3 hans = {
            StartPos.x + tans * EVec.x,
            StartPos.y + tans * EVec.y,
            StartPos.z + tans * EVec.z
        };

        float3 _p1 = {
            hans.x - p1.x,
            hans.y - p1.y,
            hans.z - p1.z
        };

        // カメラベクトルとの距離
        float len = length(_p1);

        // 最短距離ヒットポイント算出
        if  ( stbuf[did.x].crosspos.w == -1.0f)
        {
            stbuf[did.x].crosspos.x = x;
            stbuf[did.x].crosspos.y = did.x;
            stbuf[did.x].crosspos.z = length(p1-StartPos.xyz);
            stbuf[did.x].crosspos.w = len;
            continue;
        }

        if  (stbuf[did.x].crosspos.w > len)
        {
            float lenp2s = length(p1-StartPos.xyz);
            if (stbuf[did.x].crosspos.z > lenp2s)
            {
                stbuf[did.x].crosspos.x = x;
                stbuf[did.x].crosspos.y = did.x;
                stbuf[did.x].crosspos.z = lenp2s;
                stbuf[did.x].crosspos.w = len;
            }           
        }
    }
}