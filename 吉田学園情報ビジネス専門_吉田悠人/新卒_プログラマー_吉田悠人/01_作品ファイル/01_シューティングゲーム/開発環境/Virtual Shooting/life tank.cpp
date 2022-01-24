//=============================================================================
//
//	ライフタンク[life tank.h]
//	Author:吉田　悠人
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "life tank.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// 静的メンバー変数
//=============================================================================
TEXTURE_DATA CLifeTank::m_TextureData = { NULL,"data/TEXTURE/UI_Life.png" };
//=============================================================================
// コンストラクト
//=============================================================================
CLifeTank::CLifeTank(int nPriorit) :CScene2d(nPriorit)
{

}

//=============================================================================
// テクスチャロード処理
//=============================================================================
HRESULT CLifeTank::Load(void)
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
void CLifeTank::Unload(void)
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
CLifeTank * CLifeTank::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//メモリ確保
	CLifeTank* pLifeTank = NULL;
	pLifeTank = new CLifeTank;

	//NULLチェック
	if (pLifeTank != NULL)
	{
		//位置設定
		pLifeTank->SetPos(D3DXVECTOR3(pos.x, pos.y, pos.z));
		//サイズ設定
		pLifeTank->SetSize(D3DXVECTOR3(size.x, size.y, size.z));
		//初期化処理
		pLifeTank->Init();
	}
	return pLifeTank;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CLifeTank::Init(void)
{
	//テクスチャ設定
	BindTexture(m_TextureData.m_Texture);
	//アイコンの初期化処理
	CScene2d::Init();

	return S_OK;
}

