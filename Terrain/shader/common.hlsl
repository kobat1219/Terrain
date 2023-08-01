Texture2D g_Tex[8] : register(t0);				    // �e�N�X�`��
SamplerState g_SamplerLinear : register(s0);	// �T���v���[

//--------------------------------------------------------------------------------------
// �R���X�^���g�o�b�t�@
//--------------------------------------------------------------------------------------
cbuffer ConstantBufferWorld : register(b0)
{
	matrix World;
}

cbuffer ConstantBufferView : register(b1)
{
	matrix View;
}

cbuffer ConstantBufferProjection : register(b2)
{
	matrix Projection;
}

cbuffer ConstantBufferMaterial : register(b3)
{
	float4	ambientMaterial;
	float4	diffuseMaterial;
	float4	specularMaterial;
}

cbuffer ConstantBufferLight : register(b4)
{
	float4 LightDirection;			// ���̕���
	float4 EyePos;					// ���_�ʒu
	float4 Ambient;
}

cbuffer ConstantBufferViewPort : register(b5)
{
    uint4 ViewportWidth;        // �r���[�|�[�g��
    uint4 ViewportHeight;       // �r���[�|�[�g����
};

cbuffer ConstantTerrainParam : register(b6)
{
	float g_fMinDistance : packoffset(c0);
	float g_fMaxDistance : packoffset(c1);
	int g_iMaxDevide : packoffset(c2);
};
//--------------------------------------------------------------------------------------
// �\���̒�`
//--------------------------------------------------------------------------------------
struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;
	float4 Color : COLOR0;
	float2 Tex : TEXCOORD;
	float4 WPos : TEXCOORD1;
	float4 Normal : TEXCOORD2;
};

struct VS_INPUT
{
	float4 Pos : POSITION;
	float4 Color : COLOR;
	float2 Tex : TEXCOORD;
	float4 Normal : NORMAL;
	uint svid : SV_InstanceID;
};

struct InstanceMtx
{
	uint id[4];

	matrix mtx;
};

struct HS_CONSTANT_OUTPUT
{
	float factor[4]  : SV_TessFactor;
	float inner_factor[2] : SV_InsideTessFactor;
};

struct HS_OUTPUT
{
	float3 pos  : POSITION;
	float2 uv :TEXCOORD0;
};

struct DS_OUTPUT
{
	float4 pos : SV_POSITION;
	float2 uv:TEXCOORD0;
	float4 normal : TEXCOORD1;
    float4 wpos : TEXCOORD2;
};
