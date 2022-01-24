//=============================================================================
//
//	ウェポンUI[weapon ui.h]
//	Author:吉田　悠人
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "weapon ui.h"
#include "renderer.h"
#include "manager.h"
#include "bullet icon.h"
#include "laser icon.h"
#include "homing icon.h"

//=============================================================================
// 静的メンバー変数
//=============================================================================
TEXTURE_DATA CWeaponUi::m_TextureData = { NULL ,"data/TEXTURE/UI_WeaponFrame.png" };

//=============================================================================
// コンストラクト
//=============================================================================
CWeaponUi::CWeaponUi(int nPriorit) :CScene2d(nPriorit)
{
	m_pWeaponIcon = NULL;

}

//=============================================================================
// テクスチャロード処理
//=============================================================================
HRESULT CWeaponUi::Load(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, m_TextureData.m_cFileName, &m_TextureData.m_Texture);
	return S_OK;
}

//=============================================================================
// テクスチャ破棄処理
//=============================================================================
void CWeaponUi::Unload(void)
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
CWeaponUi * CWeaponUi::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//メモリ確保
	CWeaponUi* pWeaponUi = NULL;
	pWeaponUi = new CWeaponUi;

	//NULLチェック
	if (pWeaponUi != NULL)
	{
		//位置設定
		pWeaponUi->SetPos(pos);
		//大きさ設定
		pWeaponUi->SetSize(size);
		//テクスチャの設定
		pWeaponUi->BindTexture(m_TextureData.m_Texture);
		//初期化処理
		pWeaponUi->Init();
	}
	return pWeaponUi;
}

////=============================================================================
//// 初期化処理
////=============================================================================
//HRESULT CWeaponUi::Init(void)
//{
//	//初期化処理
//	CScene2d::Init();
//	return S_OK;
//}
//
////=============================================================================
//// 終了処理
////=============================================================================
//void CWeaponUi::Uninit(void)
//{
//	CScene2d::Uninit();
//	if (m_pWeaponIcon != NULL)
//	{
//		m_pWeaponIcon->Uninit();
//	}
//}
//
////=============================================================================
//// 更新処理
////=============================================================================
//void CWeaponUi::Update(void)
//{
//	//アップデート処理
//	CScene2d::Update();
//	if (m_pWeaponIcon != NULL)
//	{
//		m_pWeaponIcon->Update();
//	}
//
//}
//
////=============================================================================
//// 描画処理
////=============================================================================
//void CWeaponUi::Draw(void)
//{
//	//描画処理
//	CScene2d::Draw();
//	if (m_pWeaponIcon != NULL)
//	{
//		m_pWeaponIcon->Draw();
//	}
//}
//
//=============================================================================
// タイプセッター
//=============================================================================
WEAPON_TYPE CWeaponUi::GetIconType(void)
{
	return m_IconType;
}

//=============================================================================
// アイコン切り替え処理
//=============================================================================
void CWeaponUi::TypeChange(WEAPON_TYPE Type)
{
	//現在のアイコン終了処理
	if (m_pWeaponIcon != NULL)
	{
		m_pWeaponIcon->Uninit();
		m_pWeaponIcon = NULL;
	}

	//タイプ変更
	m_IconType = Type;

	//現在のアイコン生成処理
	switch (m_IconType)
	{
	case WEAPONS_MODE_NONE:
		m_pWeaponIcon = NULL;
		break;
	case WEAPONS_MODE_BUTTOL:
		m_pWeaponIcon = CBulletIcon::Create(GetPos(), GetSize());
		break;
	case WEAPONS_MODE_LASER:
		m_pWeaponIcon = CLaserIcon::Create(GetPos(), GetSize());
		break;
	case WEAPONS_MODE_HOMING:
		m_pWeaponIcon = CHomingIcon::Create(GetPos(), GetSize());
		break;
	}
}

