#include"explosion.h"
#include"manager.h"
#include"renderer.h"
//=============================================================================
//マクロ定義
//=============================================================================
#define EXPLOSION_SIZE	(150)	//マックスサイズ
#define MAX_PATTERN		(8)		//アニメーションの最大枚数
#define MAX_PATTERN_X	(2)		//アニメーション横の最大枚数
#define MAX_PATTERN_Y	(5)		//アニメーション縦の最大枚数

//=============================================================================
//静的メンバー変数
//=============================================================================
TEXTURE_DATA CExplosion::m_TextureData = {NULL,"data/TEXTURE/Explosion.png" };
//=============================================================================
//コンストラクタ
//=============================================================================
CExplosion::CExplosion(int nPriorit) :CScene2d(nPriorit)
{
	//初期化処理
	m_nCounterAnim = 0;
	m_nPatternAnimX = 0;
	m_nPatternAnimY = 0;

	//タイプ処理
	CScene::SetObjType(CScene::OBJ_TYPE_NONE);

}

//=============================================================================
//テクスチャ読み込み処理
//=============================================================================
HRESULT CExplosion::Load(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, m_TextureData.m_cFileName, &m_TextureData.m_Texture);
	return S_OK;
}

//=============================================================================
//テクスチャ破棄処理
//=============================================================================
void CExplosion::Unload(void)
{
	//テクスチャの破棄
	if (m_TextureData.m_Texture != NULL)
	{
		m_TextureData.m_Texture->Release();
		m_TextureData.m_Texture = NULL;
	}
}


//=============================================================================
//生成処理
//=============================================================================
CExplosion * CExplosion::Create(D3DXVECTOR3 Pos)
{
	//メモリ確保
	CExplosion *pExplosion = NULL;
	pExplosion = new CExplosion;

	//NULLチェック
	if (pExplosion != NULL)
	{
		//位置セット
		pExplosion->SetPos(Pos);
		//初期化処理
		pExplosion->Init();
	}
	return pExplosion;
}

//=============================================================================
//初期化処理
//=============================================================================
HRESULT CExplosion::Init(void)
{
	D3DXVECTOR2 Texture[4];

	//サイズ
	SetSize(D3DXVECTOR3(EXPLOSION_SIZE / 2, EXPLOSION_SIZE / 2, 0.0f));

	//初期化処理
	CScene2d::Init();
	Texture[0] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)MAX_PATTERN_X), m_nPatternAnimY*(1.0f / (float)MAX_PATTERN_Y));
	Texture[1] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)MAX_PATTERN_X) + (1.0f / (float)MAX_PATTERN_X), m_nPatternAnimY*(1.0f / (float)MAX_PATTERN_Y));
	Texture[2] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)MAX_PATTERN_X), m_nPatternAnimY*(1.0f / (float)MAX_PATTERN_Y) + (1.0f / (float)MAX_PATTERN_Y));
	Texture[3] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)MAX_PATTERN_X) + (1.0f / (float)MAX_PATTERN_X), m_nPatternAnimY*(1.0f / (float)MAX_PATTERN_Y) + (1.0f / (float)MAX_PATTERN_Y));
	TextureAnim(Texture);

	//テクスチャの設定
	BindTexture(m_TextureData.m_Texture);

	return S_OK;
}

//=============================================================================
//更新処理
//=============================================================================
void CExplosion::Update(void)
{
	D3DXVECTOR2 Texture[4];

	Texture[0] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)MAX_PATTERN_X), m_nPatternAnimY*(1.0f / (float)MAX_PATTERN_Y));
	Texture[1] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)MAX_PATTERN_X)+ (1.0f / (float)MAX_PATTERN_X), m_nPatternAnimY*(1.0f / (float)MAX_PATTERN_Y));
	Texture[2] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)MAX_PATTERN_X), m_nPatternAnimY*(1.0f / (float)MAX_PATTERN_Y) + (1.0f / (float)MAX_PATTERN_Y));
	Texture[3] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)MAX_PATTERN_X)+ (1.0f / (float)MAX_PATTERN_X), m_nPatternAnimY*(1.0f / (float)MAX_PATTERN_Y) + (1.0f / (float)MAX_PATTERN_Y));

	TextureAnim(Texture);
	//アニメーションカウント
	m_nCounterAnim++;
	if (m_nCounterAnim %2)
	{
		//アニメーションの絵を次の絵に変える
		m_nPatternAnimX++;
		m_nCounterAnim = 0;
		if (m_nPatternAnimX == MAX_PATTERN_X)
		{
			m_nPatternAnimX = 0;
			m_nPatternAnimY++;
			if (m_nPatternAnimY == MAX_PATTERN_Y)
			{
				m_nPatternAnimY = 0;
				Uninit();
			}
		}
	}
	
}
