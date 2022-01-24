//=============================================================================
//
//	バレットアイコン[bullet icon.cpp]
//	Author:吉田　悠人
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "bullet icon.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// 静的メンバー変数
//=============================================================================
TEXTURE_DATA CBulletIcon::m_TextureData = {NULL,"data/TEXTURE/UI_Bullet.png"};
//=============================================================================
// コンストラクト
//=============================================================================
CBulletIcon::CBulletIcon()
{

}


//=============================================================================
// テクスチャロード処理
//=============================================================================
HRESULT CBulletIcon::Load(void)
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
void CBulletIcon::Unload(void)
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
CBulletIcon * CBulletIcon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//メモリ確保
	CBulletIcon* pBulletIcon = NULL;
	pBulletIcon = new CBulletIcon;

	//NULLチェック
	if (pBulletIcon != NULL)
	{
		//位置設定
		pBulletIcon->SetPos(D3DXVECTOR3(pos.x, pos.y, pos.z));
		//サイズ設定
		pBulletIcon->SetSize(D3DXVECTOR3(size.x, size.y, size.z));
		//テクスチャ設定
		pBulletIcon->BindTexture(m_TextureData.m_Texture);

		//初期化処理
		pBulletIcon->Init();
	}
	return pBulletIcon;
}
