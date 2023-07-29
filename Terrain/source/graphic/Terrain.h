#pragma once

#include	<DirectXMath.h>
#include	<wrl/client.h>
#include	<d3d11.h>
#include	<vector>
#include    "../core/MyVariables.h"
#include	"../directx/DX11Util.h"
#include	"Shader.h"
#include	"ShaderBank.h"

using Microsoft::WRL::ComPtr;

constexpr UINT NUM_ELEMENTS = 128;

class GpuTerrain
{
public:
    void Init();
    void NewMap();
    void SetPenSRV(std::string _str);
    void Draw(const MyEngine::float3& _camerapos);

    void SetMaxLength(const float& _length);
    float GetMaxLength();

protected:

    //-----------------------------------------------------------------

    std::vector<float> m_HeightMapBuffer;
    
    // 高さマップ
#ifdef USE_WICTEX
    ComPtr<ID3D11Resource> m_pHeightMapT2DBuf;
#else
    ComPtr<ID3D11Texture2D> m_pHeightMapT2DSRBuf;
    ComPtr<ID3D11Texture2D> m_pHeightMapT2DUABuf;
    ComPtr<ID3D11Texture2D> m_pNormalAndTexT2DSRBuf;
    ComPtr<ID3D11Texture2D> m_pNormalAndTexT2DUABuf;
#endif // USE_WICTEX

    // 高さマップSRV
    ComPtr<ID3D11ShaderResourceView> m_pHeightMapT2DBufSRV;
    ComPtr<ID3D11UnorderedAccessView> m_pHeightMapT2DBufUAV;

    ComPtr<ID3D11ShaderResourceView> m_pNormalAndTexT2DBufSRV;
    ComPtr<ID3D11UnorderedAccessView> m_pNormalAndTexT2DBufUAV;

    UINT m_heightMapDivSize = 1024;
    //-----------------------------------------------------------------

    // 頂点データ
    struct Vertex {
        DirectX::XMFLOAT3	Pos;
        
        DirectX::XMFLOAT2	Uv;
    };

    std::vector<Vertex>	m_vertex;			//　頂点データ
    ComPtr<ID3D11Buffer> m_vertexBuffer;

    //--------------------------------------------------------------------------
    struct DivFactor {
        float factor[4];
        float inside[4];
    };
    std::vector<DivFactor>	m_factor;			//　分割数計算値用のバッファ
    ComPtr<ID3D11Buffer> m_factorStructBuffer;
    ComPtr<ID3D11ShaderResourceView> m_factorStructBufferSRV;
    //--------------------------------------------------------------------------
    

    // 頂点シェーダ
    ComPtr<ID3D11VertexShader> m_vertexShader;
    // 頂点レイアウト
    ComPtr<ID3D11InputLayout> m_inputLayout;
    
    // ハル
    ComPtr<ID3D11HullShader> m_hullShader;
    // ドメイン
    ComPtr<ID3D11DomainShader> m_domainShader;

    // ピクセル
    ComPtr<ID3D11PixelShader> m_pixelShader;

    //---------------------------------------------------------------
    // 高さマップのパッチごとの値を得るCS
    ComPtr<ID3D11ComputeShader> m_heightComputeShader;
    // レイとの交差判定を取得するCS
    ComPtr<ID3D11ComputeShader> m_crossComputeShader;

    struct Anser {
        XMFLOAT4 factor;
    };
    struct ConstantMapProperty
    {
        // xyz:テレインワールド座標 w:地面隙間サイズ
        XMFLOAT4 World;
        // カメラSpos
        XMFLOAT4 StartPos;
        // カメラベクトル
        XMFLOAT4 EVec;
    };

    Anser getdata[16 * 16];
    Anser crossdata[16 * 64 * 2];

    ComPtr<ID3D11Buffer> m_ansstrcuturedBuf;
    ComPtr<ID3D11UnorderedAccessView> m_ansstrcuturedUAV;

    ComPtr<ID3D11Buffer> m_crossstrcuturedBuf;
    ComPtr<ID3D11UnorderedAccessView> m_crossstrcuturedUAV;

    ConstantMapProperty m_constantMapProperty;
    ComPtr<ID3D11Buffer> m_constantMapPropertyBuf;

    ComPtr<ID3D11SamplerState>m_samplerstate;
    //---------------------------------------------------------------

    // テレインエディタCS
    ComPtr<ID3D11ComputeShader> m_terrainEditComputeShader;


    struct ConstantEditProperty
    {
        // xy:uv z:range w:係数
        XMFLOAT4 UVAndRangeAndCoef;
        // セットするID x:テクスチャID y:TypeID 
        XMFLOAT4 SetId;
    };
    
    ConstantEditProperty m_constantEditProperty;
    ComPtr<ID3D11Buffer> m_constantEditPropertyBuf;

    //---------------------------------------------------------------
    std::unordered_map<std::string,ComPtr<ID3D11Resource>> m_pentex;
    ComPtr<ID3D11ShaderResourceView> m_pentexsrv;

    // 2の乗数
    float m_div = 16;
    float m_divsize = 2;

    float m_minLength = 0.5f;
    float m_maxLength = 85.0f;

    bool CreateIndexAndVertexBuffer();
    bool CreateHeightmapCS();
    bool CreateCrossPointCS();
    bool CreateEditCS();
    bool CreateShader();
    bool CreateCSUseSampler();
    bool CreatePexTexture();
    void UpdateFactor(const MyEngine::float3& _camerapos);
    void UpdateEditConstantData(const ConstantEditProperty& _Data);
    void CalHeighmapCS();
    void CalCrossPointCS();
    void CalEditCS();
};

