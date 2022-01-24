//=============================================================================
//
//	ロード背景[load bg.cpp]
//	Author:吉田　悠人
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "load bg.h"	
#include "manager.h"	
#include "renderer.h"	
#include "scene.h"
//=============================================================================
// 静的メンバー変数
//=============================================================================
TEXTURE_DATA CLoadBg::m_TextureData = { NULL, "data/TEXTURE/LoadBg.png" };

//=============================================================================
// コンストラクタ
//=============================================================================
CLoadBg::CLoadBg() 
{
	//タイプ処理
	CScene::SetObjType(CScene::OBJ_TYPE_NONE);
}


//=============================================================================
// テクスチャ読み込み
//=============================================================================
HRESULT CLoadBg::Load(void)
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
void CLoadBg::Unload(void)
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
CLoadBg * CLoadBg::Create(void)
{
	//メモリ確保
	CLoadBg *pLoadBg = NULL;
	pLoadBg = new CLoadBg;

	//NULLチェック
	if (pLoadBg != NULL)
	{
		//位置設定
		pLoadBg->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f));
		//サイズ設定
		pLoadBg->SetSize(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
		//テクスチャ設定
		pLoadBg->BindTexture(m_TextureData.m_Texture);
		//初期化処理
		pLoadBg->Init();
	}

	return pLoadBg;
}