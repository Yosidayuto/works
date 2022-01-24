//=============================================================================
//
//	セレクト背景[select bg.cpp]
//	Author:吉田　悠人
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "select bg.h"	
#include "manager.h"	
#include "renderer.h"	
#include "scene.h"
//=============================================================================
// 静的メンバー変数
//=============================================================================
TEXTURE_DATA CSelectBg::m_TextureData = { NULL,"data/TEXTURE/background_Select.png" };

//=============================================================================
// コンストラクタ
//=============================================================================
CSelectBg::CSelectBg(int nPriorit) :CBgc(nPriorit)
{
	//タイプ処理
	CScene::SetObjType(CScene::OBJ_TYPE_NONE);
}

//=============================================================================
// テクスチャ読み込み
//=============================================================================
HRESULT CSelectBg::Load(void)
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
void CSelectBg::Unload(void)
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
CSelectBg * CSelectBg::Create(void)
{
	//メモリ確保
	CSelectBg *pSelectBg = NULL;
	pSelectBg = new CSelectBg;

	//NULLチェック
	if (pSelectBg != NULL)
	{
		//位置設定
		pSelectBg->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f));
		//サイズ設定
		pSelectBg->SetSize(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
		//テクスチャ設定
		pSelectBg->BindTexture(m_TextureData.m_Texture);
		//初期化処理
		pSelectBg->Init();
	}
	return pSelectBg;
}
