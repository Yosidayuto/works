//=============================================================================
//
//	ライフテロップ[telop life.cpp]
//	Author:吉田　悠人
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "telop life.h"
#include "telop.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// 静的メンバー変数
//=============================================================================
TEXTURE_DATA CTelopLife::m_TextureData = { NULL,"data/TEXTURE/Telop_LifeUp.png" };
//=============================================================================
// コンストラクト
//=============================================================================
CTelopLife::CTelopLife(int nPriorit) :CScene2d(nPriorit)
{
}

//=============================================================================
// テクスチャロード処理
//=============================================================================
HRESULT CTelopLife::Load(void)
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
void CTelopLife::Unload(void)
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
CTelopLife * CTelopLife::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//メモリ確保
	CTelopLife* pTelopLife = NULL;
	pTelopLife = new CTelopLife;

	//NULLチェック
	if (pTelopLife != NULL)
	{
		//位置設定
		pTelopLife->SetPos(D3DXVECTOR3(pos.x - TELOP_X_SIZE, pos.y, pos.z));
		//サイズ設定
		pTelopLife->SetSize(D3DXVECTOR3(size.x - TELOP_X_SIZE / 2, size.y, size.z));
		//テクスチャ設定
		pTelopLife->BindTexture(m_TextureData.m_Texture);

		//初期化処理
		pTelopLife->Init();

	}

	return pTelopLife;
}
