//=============================================================================
//
//	ホーミングアイコン[homing icon.cpp]
//	Author:吉田　悠人
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "homing icon.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// 静的メンバー変数
//=============================================================================
TEXTURE_DATA CHomingIcon::m_TextureData = { NULL,"data/TEXTURE/UI_Homing.png" };
//=============================================================================
// コンストラクト
//=============================================================================
CHomingIcon::CHomingIcon()
{

}

//=============================================================================
// テクスチャロード処理
//=============================================================================
HRESULT CHomingIcon::Load(void)
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
void CHomingIcon::Unload(void)
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
CHomingIcon * CHomingIcon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//メモリ確保
	CHomingIcon* pHomingIcon=NULL;
	pHomingIcon = new CHomingIcon;

	//NULLチェック
	if (pHomingIcon != NULL)
	{
		//位置設定
		pHomingIcon->SetPos(D3DXVECTOR3(pos.x, pos.y, pos.z));
		//サイズ設定
		pHomingIcon->SetSize(D3DXVECTOR3(size.x, size.y, size.z));
		//テクスチャ設定
		pHomingIcon->BindTexture(m_TextureData.m_Texture);

		//初期化処理
		pHomingIcon->Init();

	}

	return pHomingIcon;
}
