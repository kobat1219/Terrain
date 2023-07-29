//--------------------------------------------------------------------------------------
// vsstage.fx
//--------------------------------------------------------------------------------------
#include	"psvscommon.hlsl"
//--------------------------------------------------------------------------------------
// 頂点シェーダー
//--------------------------------------------------------------------------------------
VS_OUTPUT main(float4 Pos : POSITION,float2 Tex : TEXCOORD)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	output.Pos = Pos;
	output.Tex=Tex;
    
	return output;
}