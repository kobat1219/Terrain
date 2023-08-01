#include "common.hlsl"

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

//
//
//ドメインシェーダー
[domain("quad")]
DS_OUTPUT DS( HS_CONSTANT_OUTPUT In, float2 UV : SV_DomaInLocation, const OutputPatch<HS_OUTPUT, 4> patch )
{
	DS_OUTPUT Out;
	
	// UV
	float2 top_uv = lerp(patch[0].uv, patch[1].uv, UV.x);
	float2 bottom_uv = lerp(patch[3].uv, patch[2].uv, UV.x);
    float2 uv = float2(lerp(top_uv, bottom_uv, UV.y));
	Out.uv=uv;

	// 高さマップから取得
    float4 height = g_Tex[0].SampleLevel(g_SamplerLinear, uv, 0);

	// 
	float3 top_u = lerp(patch[0].pos, patch[1].pos, UV.x);
	float3 bottom_u = lerp(patch[3].pos, patch[2].pos, UV.x);
	
	Out.pos = float4(lerp(top_u, bottom_u, UV.y), 1);
	
    Out.pos.y += noise(uv, 0)*2;
	
    Out.wpos = Out.pos;
	
	// ワールド行列、ビュー行列、プロジェクション行列を出来た座標に掛け合わせる
	matrix mulmat=World;
	mulmat=mul(mulmat,View);
	mulmat=mul(mulmat,Projection);
	Out.pos = mul(Out.pos,(mulmat));	
	
    Out.normal=g_Tex[1].SampleLevel( g_SamplerLinear,uv,0 );

	return Out;
}