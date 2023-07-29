/**-------------------------------------------
* �����}�b�v����p�b�`���Ƃ̌W���ɕK�v�ȏ����v�Z���ďo��
---------------------------------------------*/

#define WIDE_MENBER 16

SamplerState g_sampler : register(s0);	// �T���v���[�BCLAMP���g���ׂ��B

// �n�C�g�}�b�v�B�^��float�ɂ��邱��
Texture2D<float> g_heightMap : register(t0);

// �p�b�`���̍����̑S�����A�ō��l�A�Œ�l�A�ő卂�፷
struct Anser
{
    float4 factor;
};

RWStructuredBuffer<Anser> stbuf : register(u0);

[numthreads(WIDE_MENBER,1,1)]
void CS_Main(   
                uint3 did : SV_DispatchThreadID,
                uint3 gtd : SV_GroupThreadID,   // Y�����Ƃ���
                uint3 gid : SV_GroupID          // X�����Ƃ���
            )
{
    // ���̃X���b�h�̍ŋߐړ_������
    stbuf[did.x].factor.x = 0;
    stbuf[did.x].factor.y = 0;
    stbuf[did.x].factor.z = 0;
    stbuf[did.x].factor.w = 0;    

    // �e�N�X�`���T�C�Y�̏��擾�ƁA1�p�b�`�̑傫�����v�Z
    uint2 texsize;

    g_heightMap.GetDimensions(texsize.x,texsize.y);
    uint divsizex =texsize.x / WIDE_MENBER;
    uint divsizey =texsize.y / WIDE_MENBER;


    // �p�b�`���̍�����S�����A�ō��l�A�Œ�l�A�ő卂�፷�̌v�Z����
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