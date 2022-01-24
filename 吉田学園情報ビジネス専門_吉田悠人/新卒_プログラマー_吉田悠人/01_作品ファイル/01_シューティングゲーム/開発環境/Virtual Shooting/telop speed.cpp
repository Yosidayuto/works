//=============================================================================
//
//	スピードテロップ[telop speed.cpp]
//	Author:吉田　悠人
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "telop speed.h"
#include "telop.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// 静的メンバー変数
//=============================================================================
TEXTURE_DATA CTelopSpeed::m_TextureData = { NULL,"data/TEXTURE/Telop_SpeedUp.png" };
//=============================================================================
// コンストラクト
//=============================================================================
CTelopSpeed::CTelopSpeed(int nPriorit) :CScene2d(nPriorit)
{
}

//=============================================================================
// テクスチャロード処理
//=============================================================================
HRESULT CTelopSpeed::Load(void)
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
void CTelopSpeed::Unload(void)
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
CTelopSpeed * CTelopSpeed::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//メモリ確保
	CTelopSpeed* pTelopSpeed = NULL;
	pTelopSpeed = new CTelopSpeed;

	//NULLチェック
	if (pTelopSpeed != NULL)
	{
		//位置設定
		pTelopSpeed->SetPos(D3DXVECTOR3(pos.x - TELOP_X_SIZE, pos.y, pos.z));
		//サイズ設定
		pTelopSpeed->SetSize(D3DXVECTOR3(size.x - TELOP_X_SIZE / 2, size.y, size.z));
		//初期化処理
		pTelopSpeed->Init();
		//テクスチャ設定
		pTelopSpeed->BindTexture(m_TextureData.m_Texture);

	}
	return pTelopSpeed;
}
