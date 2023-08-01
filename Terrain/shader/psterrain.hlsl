#include	"common.hlsl"


float4 main( DS_OUTPUT input ) : SV_Target
{
	
	//float4 diffuse = max(0.5, abs(sin(input.pos.y*2+0.5f))+0.2f)/*= diffuseMaterial * d*/;
	
	//float val = min(step(0.01, abs(input.pos.x % 2)), step(0.01, abs(input.pos.z % 2)));
	
	float3 N = normalize(input.normal);
	float3 Ld = normalize(LightDirection);
	
	float L = dot(Ld, N);

	float4 col={1,1,1,1}; 
	// col.r=1;
	// col.g=1;
	// col.b=1;
	//(g_Tex[2].Sample(g_SamplerLinear,input.Tex)*input.Color.r)+(g_Tex[1].Sample(g_SamplerLinear,input.Tex)*input.Color.g)+(g_Tex[0].Sample(g_SamplerLinear,input.Tex)*input.Color.b);
	
	//col.a = 1;
	float2 uv=input.uv;
    float3 wpos = input.wpos;
	//uv*=16.0f;
    col = lerp(g_Tex[0].SampleLevel(g_SamplerLinear, uv, 0),
			lerp(g_Tex[1].SampleLevel(g_SamplerLinear, uv, 0),
				g_Tex[2].SampleLevel(g_SamplerLinear, uv, 0),
					clamp(wpos.y , 0, 1))
						, clamp((wpos.y+0.5f), 0, 1));
    //col = g_Tex[1].SampleLevel(g_SamplerLinear, uv, 0);
    //col = g_Tex[2].SampleLevel(g_SamplerLinear, uv, 0);
	//col *= diffuse * val;
    //col *= L;
    //col *= noise(uv, 0)*10;
	col.a=1;

	return col;
;
}