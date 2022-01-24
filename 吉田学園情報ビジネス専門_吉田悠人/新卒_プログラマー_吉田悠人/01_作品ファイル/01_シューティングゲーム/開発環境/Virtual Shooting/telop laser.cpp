//=============================================================================
//
//	レーザーテロップ[telop laser.cpp]
//	Author:吉田　悠人
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "telop laser.h"
#include "telop.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// 静的メンバー変数
//=============================================================================
TEXTURE_DATA CTelopLaser::m_TextureData = { NULL,"data/TEXTURE/Telop_Laser.png" };
//=============================================================================
// コンストラクト
//=============================================================================
CTelopLaser::CTelopLaser(int nPriorit) :CScene2d(nPriorit)
{
}

//=============================================================================
// テクスチャロード処理
//=============================================================================
HRESULT CTelopLaser::Load(void)
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
void CTelopLaser::Unload(void)
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
CTelopLaser * CTelopLaser::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//メモリ確保
	CTelopLaser* pTelopLaser = NULL;
	pTelopLaser = new CTelopLaser;

	//NULLチェック
	if (pTelopLaser != NULL)
	{
		//位置設定
		pTelopLaser->SetPos(D3DXVECTOR3(pos.x - TELOP_X_SIZE, pos.y, pos.z));
		//サイズ設定
		pTelopLaser->SetSize(D3DXVECTOR3(size.x - TELOP_X_SIZE / 2, size.y, size.z));
		//テクスチャ設定
		pTelopLaser->BindTexture(m_TextureData.m_Texture);

		//初期化処理
		pTelopLaser->Init();


	}
	return pTelopLaser;
}
