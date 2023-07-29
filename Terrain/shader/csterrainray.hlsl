/**-------------------------------------------
* 地形データテクスチャから
* 選択ピクセル(頂点インデックス番号)を選び出す
* こんなんいらくて、頂点のポイントからワールド座標だして、
* それをスクリーン座標に変えて、カーソルポイントとの距離で近い頂点を選んで
* その選ばれた頂点で一番カーソルに近いやつを選択すればOKってことやわ
---------------------------------------------*/

#define WIDE_MENBER 64

SamplerState g_sampler : register(s0);	// サンプラー

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
[numthreads(WIDE_MENBER,2,1)]
void CS_Main(   
                uint3 did : SV_DispatchThreadID,
                uint3 gtd : SV_GroupThreadID, 
                uint3 gid : SV_GroupID
            )
{
    // x:テクスチャXサイズ y:テクスチャYサイズ
	uint2 MapInfo;

    g_heightMap.GetDimensions(MapInfo.x,MapInfo.y);

    uint id = did.x + gtd.y * MapInfo.x;

    // このスレッドの最近接点初期化
    stbuf[id].crosspos.x = 0.0f;
    stbuf[id].crosspos.y = 0.0f;
    stbuf[id].crosspos.z = 0.0f;
    stbuf[id].crosspos.w = -1.0f;
    
 
    float3      p1;
    float3      p2;
    float3      p3;
 
    float3      p1p2;
    float3      p2p3;
    float3      p3p1;

    float3      plane_vec;
    float       plane_d;


 
    float wwideinfo = World.x - (MapInfo.x * World.w / 2); 
    float2 uvoneval;
    uvoneval.x = 1.0f / (float)MapInfo.x;
    uvoneval.y = 1.0f / (float)MapInfo.y;
    
    float2 uv;
    
    // スレッドグループで分割数分けして
    // 横16スレッドグループ使用(これはテクスチャサイズによって変わる)
    // 縦64スレッド
    // つまり1024スレッド使用
    // テクスチャ幅/スレッド幅
    for (uint x = 0; x < MapInfo.x; x++)
    {       
        // 頂点ワールド座標X = スレッドID(縦側になる) * 頂点間幅 - テクスチャ幅 / 2 * 頂点間幅 + テレインワールド座標
        p1.z = (did.x * World.w + (World.w * gtd.y)) + wwideinfo; 
        p2.z = p1.z; 
        p3.z = (World.w * (1 - (float)gtd.y*2)) + p1.z; 
       // 頂点ワールド座標X = 頂点X番号 * 頂点間幅 - テクスチャ幅 / 2 * 頂点間幅 + テレインワールド座標
        p1.x = (x * World.w+(World.w*gtd.y)) + wwideinfo;
        p2.x = (World.w*(1-(float)gtd.y*2)) + p1.x; 
        p3.x = p2.x; 

        // 頂点ワールド座標y = uvからハイトマップをサンプル
        
        uv.x = (float)(x+gtd.y) * uvoneval.x;
        uv.y = (float)(did.x+gtd.y) * uvoneval.y;

        p1.y = g_heightMap.SampleLevel(g_sampler,uv,0);

        uv.x = (float)(x+(1-(float)gtd.y*2)) * uvoneval.x;

        p2.y = g_heightMap.SampleLevel(g_sampler,uv,0);

        uv.y = (float)(did.x+(1-(float)gtd.y*2)) * uvoneval.y;

        p3.y = g_heightMap.SampleLevel(g_sampler,uv,0);

        p1p2 = p2 - p1;
		p2p3 = p3 - p2;
        p3p1 = p1 - p3;

		plane_vec = cross(p2p3, p1p2);

		plane_vec = normalize(plane_vec);		

		plane_d = -(plane_vec.x * p1.x + plane_vec.y * p1.y + plane_vec.z * p1.z);
        
    	float _dot = dot(plane_vec, EVec.xyz);			// 分母

		if (abs(_dot) < 0.00001f) {
			// 平行
			continue;
		}
           
		float dot2 = dot(plane_vec, StartPos.xyz);			// 分子

		float t = -(dot2 + plane_d) / _dot;

        float3 ans = StartPos.xyz + EVec.xyz * t;

        p1 = ans - p1;
        p2 = ans - p2;
        p3 = ans - p3;
        
       
        if (dot(cross(p1p2, p1), plane_vec) > 0) {
            continue;
        }		// 為す角度が鈍角
     
        if (dot(cross(p2p3, p2), plane_vec) > 0) {
            continue;
        }		// 為す角度が鈍角

  
        if (dot(cross(p3p1, p3), plane_vec) > 0) {
            continue;
        }		// 為す角度が鈍角

        
        float3 len = ans - StartPos.xyz;
   
        if (dot(EVec.xyz, len) < 0.0f) continue;

        float leng = (len.x * len.x) + (len.y * len.y) + (len.z * len.z);

        // 最短距離ヒットポイント算出
        if  ( stbuf[id].crosspos.w == -1.0f)
        {
            stbuf[id].crosspos.x = x;
            stbuf[id].crosspos.y = did.x;
            stbuf[id].crosspos.w = leng;
            continue;
        }
        if  (stbuf[id].crosspos.w < leng)
        {
            stbuf[id].crosspos.x = x;
            stbuf[id].crosspos.y = did.x;          
            stbuf[id].crosspos.w = leng;
        }
    }
}