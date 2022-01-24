//=============================================================================
//
//	タイトル背景[title bg.cpp]
//	Author:吉田　悠人
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "title bg.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// 静的メンバー変数
//=============================================================================
TEXTURE_DATA CTitleBg::m_TextureData = { NULL,"data/TEXTURE/title.png" };

//=============================================================================
// コンストラクタ
//=============================================================================
CTitleBg::CTitleBg(int nPriorit)
{
}

//=============================================================================
// テクスチャ読み込み
//=============================================================================
HRESULT CTitleBg::Load(void)
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
void CTitleBg::Unload(void)
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
CTitleBg * CTitleBg::Create(void)
{
	//メモリ確保
	CTitleBg *pTitleBg = NULL;
	pTitleBg = new CTitleBg;

	//NULLチェック
	if (pTitleBg != NULL)
	{
		//位置設定
		pTitleBg->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f));
		//サイズ設定
		pTitleBg->SetSize(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
		//テクスチャ設定
		pTitleBg->BindTexture(m_TextureData.m_Texture);
		//初期化処理
		pTitleBg->Init();
	}
	return pTitleBg;
}

