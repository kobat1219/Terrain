/**-------------------------------------------
* �􂢏o���ꂽ�ړ_����A�e�N�X�`���̃f�[�^���y���̃e�N�X�`���ŏ���������
---------------------------------------------*/

#define WIDE_MENBER 16

SamplerState g_sampler : register(s0);	// �T���v���[
// �n�C�g�}�b�v
RWTexture2D<float> g_heightMap : register(u0);
// �@���}�b�v
RWTexture2D<float4> g_nomalMap : register(u1);
// �J���[�}�b�v(1�e���C���ɂ�4���C���[�܂�)
RWTexture2D<float4> g_colorMap : register(u1);

// �y���e�N�X�`��
Texture2D g_penTexture:register(t0);

cbuffer ConstantUpdateMapProperty : register(b11)
{
    // xy:uv z:range w:�W��
    float4 UVAndRangeAndCoef;
    // �Z�b�g����ID x:�e�N�X�`��ID y:TypeID 
	float4 SetId;
};

// �\����
[numthreads(1,1,1)]
void CS_Main(   
                uint3 did : SV_DispatchThreadID
            )
{
    // x:�e�N�X�`��X�T�C�Y y:�e�N�X�`��Y�T�C�Y
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
    // 1�p�b�`���X�V���邪�A�p�b�`�̏ꏊ������o���Ȃ��Ƃ����Ȃ�
    // ����ōX�V���ׂ��p�b�`������POSITION���킩����
 
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

    // ��БS�X���b�h�����ύX�҂�
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