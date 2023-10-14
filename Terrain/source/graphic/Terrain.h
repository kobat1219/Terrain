#pragma once

#include	<vector>
#include    <unordered_map>
#include    "../core/MyVariables.h"
#include	"../directx/DX11Util.h"
#include	"Shader.h"

using Microsoft::WRL::ComPtr;

class Terrain
{
public:
    void Init();
    void NewMap();
    void Draw(const MyEngine::float3& _camerapos);
    void UpdateEditConstantData();
    void CalNewMapCS();

    // setter
    void SetMaxLength(const float& _length);
    void SetSeed(const int& _seed);
    void SetUVScale(const float& _scale);
    void SetTexHeight(const MyEngine::float2& _texh);

    // getter
    float               GetMaxLength();
    int                 GetSeed();
    float               GetUVScale();
    MyEngine::float2    GetTexHeight();

private:
    bool CreateIndexAndVertexBuffer();
    bool CreateNewMapCS();
    bool CreateShader();
    bool CreateCSUseSampler();
    bool LoadGraundTexture();
    bool CreateConstantBufferEditData();
    void UpdateFactor(const MyEngine::float3& _camerapos);

private: // variables
    //--Shader------------------------------------------------------------------------
    
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

    //--VertexBuffer---------------------------------------------------------------

    // 頂点データ
    struct Vertex 
    {
        DirectX::XMFLOAT3	Pos;
        DirectX::XMFLOAT2	Uv;
    };

    std::vector<Vertex>	m_vertex;			//　頂点データ
    ComPtr<ID3D11Buffer> m_vertexBuffer;

    //--ConstantDataBuffer-------------------------------------------------------------
 
    struct ConstantEditProperty
    {
        // x:uvscale y:seed zw:texheight
        XMFLOAT4 UVScaleAndSeedAndTexHeight = { 8,0,-1.5f,0.5f };
    };

    ConstantEditProperty m_constantEditProperty;
    ComPtr<ID3D11Buffer> m_constantEditPropertyBuf;

    //--DivisionFactorBuffer------------------------------------------------------------------------
    
    struct DivFactor {
        float factor[4];
        float inside[4];    // float*4でないといけない。
    };
    std::vector<DivFactor>	m_factor;			//　分割数計算値用のバッファ
    ComPtr<ID3D11Buffer> m_factorStructBuffer;
    ComPtr<ID3D11ShaderResourceView> m_factorStructBufferSRV;

    //--MapTextureResource---------------------------------------------------------------
    
    // 高さマップ
    ComPtr<ID3D11Texture2D> m_pHeightMapT2DSRBuf;
    ComPtr<ID3D11Texture2D> m_pHeightMapT2DUABuf;

    // 高さマップSRV,UAV
    ComPtr<ID3D11ShaderResourceView> m_pHeightMapT2DBufSRV;
    ComPtr<ID3D11UnorderedAccessView> m_pHeightMapT2DBufUAV;

    // マップテクスチャ幅 1024*1024px
    UINT m_MapTextureDivSize = 1024;

    //--GraundTextureResource-------------------------------------------------------------

    std::unordered_map<std::string, ComPtr<ID3D11Resource>> m_gtex;
    std::unordered_map<std::string, ComPtr<ID3D11ShaderResourceView>> m_gtexsrv;

    const int gtexvalue = 3;

    const std::vector<std::string> gtexname = 
    {
        "sand",
        "moss",
        "snow"
    };
    const std::vector<std::string> gtexpath = 
    {
        "assets/gtex/sand.png",
        "assets/gtex/moss.png",
        "assets/gtex/snow.png"
    };

    //--ComputeShader-------------------------------------------------------------
    // 高さマップのパッチごとの値を得るCS
    ComPtr<ID3D11ComputeShader> m_newmapComputeShader;

    // ComputeShader用のサンプラー
    ComPtr<ID3D11SamplerState>m_samplerstate;

    //--Parameta-------------------------------------------------------------

    // 2の乗数
    float m_div = 16;
    float m_divsize = 2;

    float m_minLength = 0.5f;
    float m_maxLength = 85.0f;

};

