//=============================================================================
//
//	チュートリアル背景[tutorial bg.cpp]
//	Author:吉田　悠人
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "tutorial bg.h"
#include "manager.h"
#include "renderer.h"
//=============================================================================
//マクロ定義
//=============================================================================
#define TEXTURE_X (0.25f)

//=============================================================================
// 静的メンバー変数
//=============================================================================
TEXTURE_DATA CTutorialBg::m_TextureData = { NULL,"data/TEXTURE/tutorial.png" };

//=============================================================================
// コンストラクタ
//=============================================================================
CTutorialBg::CTutorialBg(int nPriorit)
{
	m_fTexture = 0.0f;
}

//=============================================================================
// テクスチャ読み込み
//=============================================================================
HRESULT CTutorialBg::Load(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		m_TextureData.m_cFileName,
		&m_TextureData.m_Texture);

	return S_OK;
}

//=============================================================================
// テクスチャの破棄
//=============================================================================
void CTutorialBg::Unload(void)
{
	//テクスチャの破棄
	if (m_TextureData.m_Texture != NULL)
	{
		m_TextureData.m_Texture->Release();
		m_TextureData.m_Texture = NULL;
	}
}

//=============================================================================
// 生成処理
//=============================================================================
CTutorialBg * CTutorialBg::Create(void)
{
	//メモリ確保
	CTutorialBg *pTutorialBg = NULL;
	pTutorialBg = new CTutorialBg;

	//NULLチェック
	if (pTutorialBg != NULL)
	{
		//位置設定
		pTutorialBg->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f));
		//サイズ設定
		pTutorialBg->SetSize(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
		//テクスチャ設定
		pTutorialBg->BindTexture(m_TextureData.m_Texture);
		//初期化処理
		pTutorialBg->Init();
	}

	return pTutorialBg;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTutorialBg::Init(void)
{

	D3DXVECTOR2 Texture[4];
	//テクスチャ処理
	Texture[0] = D3DXVECTOR2(0.0f, 0.0f);
	Texture[1] = D3DXVECTOR2(TEXTURE_X, 0.0f);
	Texture[2] = D3DXVECTOR2(0.0f, 1.0f);
	Texture[3] = D3DXVECTOR2(TEXTURE_X, 1.0f);

	//初期化処理
	CBgc::Init();

	//テクスチャUV処理
	TextureAnim(Texture);

	return S_OK;
}

//=============================================================================
// テクスチャ移動
//=============================================================================
void CTutorialBg::TextureMove(bool bScroll)
{
	if (bScroll == true)
	{
		m_fTexture++;
	}
	else
	{
		m_fTexture--;
	}
	if (m_fTexture<0)
	{
		m_fTexture = 0.0f;
	}
	D3DXVECTOR2 Texture[4];	//テクスチャ
	Texture[0] = D3DXVECTOR2(TEXTURE_X*m_fTexture, 0.0f);
	Texture[1] = D3DXVECTOR2(TEXTURE_X*m_fTexture + TEXTURE_X, 0.0f);
	Texture[2] = D3DXVECTOR2(TEXTURE_X*m_fTexture, 1.0f);
	Texture[3] = D3DXVECTOR2(TEXTURE_X*m_fTexture + TEXTURE_X, 1.0f);
	TextureAnim(Texture);
}
