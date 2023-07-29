/**-------------------------------------------
* �n�`�f�[�^�e�N�X�`������
* �I���s�N�Z��(���_�C���f�b�N�X�ԍ�)��I�яo��
* ����Ȃ񂢂炭�āA���_�̃|�C���g���烏�[���h���W�����āA
* ������X�N���[�����W�ɕς��āA�J�[�\���|�C���g�Ƃ̋����ŋ߂����_��I���
* ���̑I�΂ꂽ���_�ň�ԃJ�[�\���ɋ߂����I�������OK���Ă��Ƃ��
---------------------------------------------*/

#define WIDE_MENBER 64

SamplerState g_sampler : register(s1);	// �T���v���[

// �n�C�g�}�b�v
Texture2D<float> g_heightMap : register(t0);

cbuffer ConstantMapProperty : register(b10)
{
    // xyz:�e���C�����[���h���W w:�n�ʌ��ԃT�C�Y
    float4 World;
    // �J����Spos
	float4 StartPos;
    // �J�����x�N�g��
    float4 EVec;
};

struct Anser
{
    float4 crosspos;
};

RWStructuredBuffer<Anser> stbuf : register(u0);

// �\����
[numthreads(WIDE_MENBER,1,1)]
void CS_Main(   
                uint3 did : SV_DispatchThreadID,    // did.x���������̃��C��ID
                uint3 gtd : SV_GroupThreadID,       // gtd.x���������O���[�v���X���b�h
                uint3 gid : SV_GroupID
            )
{
    // x:�e�N�X�`��X�T�C�Y y:�e�N�X�`��Y�T�C�Y
	uint2 MapInfo;

    g_heightMap.GetDimensions(MapInfo.x,MapInfo.y);

    // ���̃X���b�h�̍ŋߐړ_������
    stbuf[did.x].crosspos.w = -1.0f;
    // stbuf[did.x].crosspos.x = StartPos.x;
    // stbuf[did.x].crosspos.z = EVec.y;
    float3      p1;

    // ���_���[���h���WX = �X���b�hID(�c���ɂȂ�) * ���_�ԕ� - �e�N�X�`���� / 2 * ���_�ԕ� + �e���C�����[���h���W
    p1.z = (did.x * World.w) + World.z - (MapInfo.y * World.w / 2); 

    float wwideinfo = World.x - (MapInfo.x * World.w / 2); 
    float2 uvoneval;
    uvoneval.x = 1.0f / (float)MapInfo.x;
    uvoneval.y = 1.0f / (float)MapInfo.y;

    // �X���b�h�O���[�v�ŕ�������������
    // ��16�X���b�h�O���[�v�g�p(����̓e�N�X�`���T�C�Y�ɂ���ĕς��)
    // �c64�X���b�h
    // �܂�1024�X���b�h�g�p
    // �e�N�X�`����/�X���b�h��
    float2 uv;    
    for (uint x = 0; x < MapInfo.x; x++)
    {       
        // ���_���[���h���WX = ���_X�ԍ� * ���_�ԕ� - �e�N�X�`���� / 2 * ���_�ԕ� + �e���C�����[���h���W
        p1.x = (x * World.w) + wwideinfo;
        
        // ���_���[���h���Wy = uv����n�C�g�}�b�v���T���v��
        
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

        // �J�����x�N�g���Ƃ̋���
        float len = length(_p1);

        // �ŒZ�����q�b�g�|�C���g�Z�o
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