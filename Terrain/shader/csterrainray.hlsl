/**-------------------------------------------
* �n�`�f�[�^�e�N�X�`������
* �I���s�N�Z��(���_�C���f�b�N�X�ԍ�)��I�яo��
* ����Ȃ񂢂炭�āA���_�̃|�C���g���烏�[���h���W�����āA
* ������X�N���[�����W�ɕς��āA�J�[�\���|�C���g�Ƃ̋����ŋ߂����_��I���
* ���̑I�΂ꂽ���_�ň�ԃJ�[�\���ɋ߂����I�������OK���Ă��Ƃ��
---------------------------------------------*/

#define WIDE_MENBER 64

SamplerState g_sampler : register(s0);	// �T���v���[

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
[numthreads(WIDE_MENBER,2,1)]
void CS_Main(   
                uint3 did : SV_DispatchThreadID,
                uint3 gtd : SV_GroupThreadID, 
                uint3 gid : SV_GroupID
            )
{
    // x:�e�N�X�`��X�T�C�Y y:�e�N�X�`��Y�T�C�Y
	uint2 MapInfo;

    g_heightMap.GetDimensions(MapInfo.x,MapInfo.y);

    uint id = did.x + gtd.y * MapInfo.x;

    // ���̃X���b�h�̍ŋߐړ_������
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
    
    // �X���b�h�O���[�v�ŕ�������������
    // ��16�X���b�h�O���[�v�g�p(����̓e�N�X�`���T�C�Y�ɂ���ĕς��)
    // �c64�X���b�h
    // �܂�1024�X���b�h�g�p
    // �e�N�X�`����/�X���b�h��
    for (uint x = 0; x < MapInfo.x; x++)
    {       
        // ���_���[���h���WX = �X���b�hID(�c���ɂȂ�) * ���_�ԕ� - �e�N�X�`���� / 2 * ���_�ԕ� + �e���C�����[���h���W
        p1.z = (did.x * World.w + (World.w * gtd.y)) + wwideinfo; 
        p2.z = p1.z; 
        p3.z = (World.w * (1 - (float)gtd.y*2)) + p1.z; 
       // ���_���[���h���WX = ���_X�ԍ� * ���_�ԕ� - �e�N�X�`���� / 2 * ���_�ԕ� + �e���C�����[���h���W
        p1.x = (x * World.w+(World.w*gtd.y)) + wwideinfo;
        p2.x = (World.w*(1-(float)gtd.y*2)) + p1.x; 
        p3.x = p2.x; 

        // ���_���[���h���Wy = uv����n�C�g�}�b�v���T���v��
        
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
        
    	float _dot = dot(plane_vec, EVec.xyz);			// ����

		if (abs(_dot) < 0.00001f) {
			// ���s
			continue;
		}
           
		float dot2 = dot(plane_vec, StartPos.xyz);			// ���q

		float t = -(dot2 + plane_d) / _dot;

        float3 ans = StartPos.xyz + EVec.xyz * t;

        p1 = ans - p1;
        p2 = ans - p2;
        p3 = ans - p3;
        
       
        if (dot(cross(p1p2, p1), plane_vec) > 0) {
            continue;
        }		// �ׂ��p�x���݊p
     
        if (dot(cross(p2p3, p2), plane_vec) > 0) {
            continue;
        }		// �ׂ��p�x���݊p

  
        if (dot(cross(p3p1, p3), plane_vec) > 0) {
            continue;
        }		// �ׂ��p�x���݊p

        
        float3 len = ans - StartPos.xyz;
   
        if (dot(EVec.xyz, len) < 0.0f) continue;

        float leng = (len.x * len.x) + (len.y * len.y) + (len.z * len.z);

        // �ŒZ�����q�b�g�|�C���g�Z�o
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