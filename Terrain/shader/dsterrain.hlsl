#include "common.hlsl"

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
    float height = g_Tex[3].SampleLevel(g_SamplerLinear, uv, 0);

	// 
	float3 top_u = lerp(patch[0].pos, patch[1].pos, UV.x);
	float3 bottom_u = lerp(patch[3].pos, patch[2].pos, UV.x);
	
	Out.pos = float4(lerp(top_u, bottom_u, UV.y), 1);
	
    Out.pos.y = height;
	
    Out.wpos = Out.pos;
	
	// ワールド行列、ビュー行列、プロジェクション行列を出来た座標に掛け合わせる
	matrix mulmat=World;
	mulmat=mul(mulmat,View);
	mulmat=mul(mulmat,Projection);
	Out.pos = mul(Out.pos,(mulmat));	
	
    Out.normal = g_Tex[4].SampleLevel(g_SamplerLinear, uv, 0);

	return Out;
}