#include	"common.hlsl"


float4 PS( DS_OUTPUT input ) : SV_Target
{	
    float2 uv = input.uv * EditProperty.x;

    float3 wpos = input.wpos;

    float4 col = lerp(g_Tex[0].SampleLevel(g_SamplerLinear, uv, 0),
			lerp(g_Tex[1].SampleLevel(g_SamplerLinear, uv, 0),
				g_Tex[2].SampleLevel(g_SamplerLinear, uv, 0),
					clamp(wpos.y + EditProperty.z, 0, 1))
						, clamp(wpos.y + EditProperty.w, 0, 1));
	
	col.a=1;

	return col;
;
}