//=============================================================================
//
//	ゲームスクロール背景[game scroll bg.cpp]
//	Author:吉田　悠人
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "game scroll bg.h"	
#include "manager.h"	
#include "renderer.h"	
#include "scene.h"
//=============================================================================
//マクロ定義
//=============================================================================
#define SCROLL_SPEED (0.001f)
//=============================================================================
// 静的メンバー変数
//=============================================================================
TEXTURE_DATA CGameScrollBg::m_TextureData = { NULL,	"data/TEXTURE/background_game_0.png"};

//=============================================================================
// コンストラクタ
//=============================================================================
CGameScrollBg::CGameScrollBg(int nPriorit) :CBgc(nPriorit)
{
	//タイプ処理
	CScene::SetObjType(CScene::OBJ_TYPE_NONE);
}

//=============================================================================
// テクスチャ読み込み
//=============================================================================
HRESULT CGameScrollBg::Load(void)
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
void CGameScrollBg::Unload(void)
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
CGameScrollBg * CGameScrollBg::Create(void)
{
	//メモリ確保
	CGameScrollBg *pGameScrollBg = NULL;
	pGameScrollBg = new CGameScrollBg;
	
	//NULLチェック
	if (pGameScrollBg != NULL)
	{
		//位置設定
		pGameScrollBg->SetPos(D3DXVECTOR3(STAGE_POS, SCREEN_HEIGHT / 2.0f, 0.0f));
		//サイズ設定
		pGameScrollBg->SetSize(D3DXVECTOR3(STAGE_SIZE, SCREEN_HEIGHT, 0.0f));
		//テクスチャ設定
		pGameScrollBg->BindTexture(m_TextureData.m_Texture);
		//初期化処理
		pGameScrollBg->Init();
	}

	return pGameScrollBg;
}

//=============================================================================
// 更新処理
//=============================================================================
void CGameScrollBg::Update(void)
{
	CBgc::Update();
	ScrollY(SCROLL_SPEED);
}
