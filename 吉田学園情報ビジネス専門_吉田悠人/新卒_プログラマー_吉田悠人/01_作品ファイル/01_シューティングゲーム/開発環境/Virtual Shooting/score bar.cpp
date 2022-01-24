//=============================================================================
//
//	スコア背景[score bar.cpp]
//	Author:吉田　悠人
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "score bar.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// 静的メンバー変数
//=============================================================================
TEXTURE_DATA CScoreBar::m_TextureData = { NULL,"data/TEXTURE/UI_score.png" };
//=============================================================================
// コンストラクト
//=============================================================================
CScoreBar::CScoreBar(int nPriorit) :CScene2d(nPriorit)
{

}

//=============================================================================
// テクスチャロード処理
//=============================================================================
HRESULT CScoreBar::Load(void)
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
// テクスチャ破棄処理
//=============================================================================
void CScoreBar::Unload(void)
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
CScoreBar * CScoreBar::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//メモリ確保
	CScoreBar* pScoreBar = NULL;
	pScoreBar = new CScoreBar;

	//NULLチェック
	if (pScoreBar != NULL)
	{
		//位置設定
		pScoreBar->SetPos(D3DXVECTOR3(pos.x, pos.y, pos.z));
		//サイズ設定
		pScoreBar->SetSize(D3DXVECTOR3(size.x, size.y, size.z));
		//テクスチャ設定
		pScoreBar->BindTexture(m_TextureData.m_Texture);
		//初期化処理
		pScoreBar->Init();
	}
	return pScoreBar;
}

