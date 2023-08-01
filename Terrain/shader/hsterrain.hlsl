#include "common.hlsl"

struct DivideParam{
	float factor[4];
	float inside[4];	
};

StructuredBuffer<DivideParam> g_divideStruct:register(t10);
//
//
//ハルシェーダーコンスタント
HS_CONSTANT_OUTPUT HSConstant( InputPatch<VS_OUTPUT, 4> ip, uint pid : SV_PrimitiveID )
{
	HS_CONSTANT_OUTPUT Out;

	Out.factor[0] = g_divideStruct[pid].factor[0];
	Out.factor[1] = g_divideStruct[pid].factor[1];
	Out.factor[2] = g_divideStruct[pid].factor[2];
	Out.factor[3] = g_divideStruct[pid].factor[3];

	Out.inner_factor[0] = g_divideStruct[pid].inside[0];//u 縦の分割数（横のラインを何本ひくか）
	Out.inner_factor[1] = g_divideStruct[pid].inside[0];//v

	return Out;
}
//
//
//ハルシェーダー
[domain("quad")]
[partitioning("pow2")]
[outputtopology("triangle_cw")]
[outputcontrolpoints(4)]
[patchconstantfunc("HSConstant")]
HS_OUTPUT HS( InputPatch<VS_OUTPUT, 4> ip, uint cpid : SV_OutputControlPointID, uint pid : SV_PrimitiveID )
{
	HS_OUTPUT Out;
	Out.pos = ip[cpid].Pos;
	Out.uv = ip[cpid].Tex;
	return Out;
}