//=============================================================================
//
//	レーザーアイコン[laser icon.cpp]
//	Author:吉田　悠人
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "laser icon.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// 静的メンバー変数
//=============================================================================
TEXTURE_DATA CLaserIcon::m_TextureData = { NULL,"data/TEXTURE/UI_Laser.png" };
//=============================================================================
// コンストラクト
//=============================================================================
CLaserIcon::CLaserIcon()
{

}

//=============================================================================
// テクスチャロード処理
//=============================================================================
HRESULT CLaserIcon::Load(void)
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
void CLaserIcon::Unload(void)
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
CLaserIcon * CLaserIcon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//メモリ確保
	CLaserIcon* pLaserIcon=NULL;
	pLaserIcon = new CLaserIcon;

	//NULLチェック
	if (pLaserIcon != NULL)
	{
		//位置設定
		pLaserIcon->SetPos(D3DXVECTOR3(pos.x, pos.y, pos.z));
		//サイズ設定
		pLaserIcon->SetSize(D3DXVECTOR3(size.x, size.y, size.z));
		//テクスチャ設定
		pLaserIcon->BindTexture(m_TextureData.m_Texture);

		//初期化処理
		pLaserIcon->Init();

	}
	return pLaserIcon;
}

