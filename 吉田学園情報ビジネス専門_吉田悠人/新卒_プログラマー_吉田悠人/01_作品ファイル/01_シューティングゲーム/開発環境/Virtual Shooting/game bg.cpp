//=============================================================================
//
//	ゲーム背景[game bg.cpp]
//	Author:吉田　悠人
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "game bg.h"	
#include "manager.h"	
#include "renderer.h"	
#include "scene.h"
//=============================================================================
// 静的メンバー変数
//=============================================================================
TEXTURE_DATA CGameBg::m_TextureData = { NULL,"data/TEXTURE/background_gameoutside_0.png" };

//=============================================================================
// コンストラクタ
//=============================================================================
CGameBg::CGameBg(int nPriorit) :CBgc(nPriorit)
{
	//タイプ処理
	CScene::SetObjType(CScene::OBJ_TYPE_NONE);
}

//=============================================================================
// テクスチャ読み込み
//=============================================================================
HRESULT CGameBg::Load(void)
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
void CGameBg::Unload(void)
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
CGameBg * CGameBg::Create(void)
{
	//メモリ確保
	CGameBg *pGameBg = NULL;
	pGameBg = new CGameBg;

	//NULLチェック
	if (pGameBg != NULL)
	{
		//位置設定
		pGameBg->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f));
		//サイズ設定
		pGameBg->SetSize(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
		//テクスチャ設定
		pGameBg->BindTexture(m_TextureData.m_Texture);
		//初期化処理
		pGameBg->Init();
	}

	return pGameBg;
}