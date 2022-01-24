//=============================================================================
//
//	ウェポンマネージャー[weapon manager.cpp]
//	Author:吉田　悠人
//
//=============================================================================
//=============================================================================
//インクルードファイル
//=============================================================================
#include "weapon manager.h"
#include "weapon ui.h"
#include "player data.h"
#include "manager.h"
#include "bullet icon.h"
#include "laser icon.h"
#include "homing icon.h"
//=============================================================================
// コンストラクト
//=============================================================================
CWeaponManager::CWeaponManager()
{
	ZeroMemory(m_pWeaponUi, sizeof(m_pWeaponUi));
}

//=============================================================================
// デストラクト
//=============================================================================
CWeaponManager::~CWeaponManager()
{
}

//=============================================================================
// テクスチャロード処理
//=============================================================================
HRESULT CWeaponManager::Load(void)
{
	CBulletIcon::Load();
	CWeaponUi::Load();
	CLaserIcon::Load();
	CHomingIcon::Load();
	return S_OK;
}

//=============================================================================
// テクスチャ破棄処理
//=============================================================================
void CWeaponManager::Unload(void)
{
	CBulletIcon::Unload();
	CWeaponUi::Unload();
	CLaserIcon::Unload();
	CHomingIcon::Unload();
}

//=============================================================================
// 生成処理
//=============================================================================
CWeaponManager * CWeaponManager::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//メモリの確保
	CWeaponManager* pWeaponManager = NULL;
	pWeaponManager = new CWeaponManager;
	//NULLチェック
	if (pWeaponManager != NULL)
	{
		//位置設定
		pWeaponManager->m_pos = pos;
		//サイズ設定
		pWeaponManager->m_size = size;
		//初期化処理
		pWeaponManager->Init();
	}
	return pWeaponManager;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CWeaponManager::Init(void)
{
	
	//UI生成
	for (int nCountWeapon = 0; nCountWeapon < MAX_WEAPON; nCountWeapon++)
	{
		//UIの横幅
		int Interval =(int)((m_size.x * nCountWeapon)*1.5f);
		//生成
		m_pWeaponUi[nCountWeapon] = CWeaponUi::Create(D3DXVECTOR3(m_pos.x + Interval, m_pos.y, m_pos.z), m_size);
	}
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CWeaponManager::Uninit(void)
{
}

//=============================================================================
// 更新処理
//=============================================================================
void CWeaponManager::Update(void)
{
	CPlayerData *pPlayer = CManager::GetPlayer();
	if (m_pWeaponUi[0] != NULL)
	{
		//左装備
		if (m_pWeaponUi[0]->GetIconType() != pPlayer->GetWeaponData().Left)
		{
			m_pWeaponUi[0]->TypeChange(pPlayer->GetWeaponData().Left);
		}

	}
	if (m_pWeaponUi[1] != NULL)
	{
		//右装備
		if (m_pWeaponUi[1]->GetIconType() != pPlayer->GetWeaponData().Right)
		{
			m_pWeaponUi[1]->TypeChange(pPlayer->GetWeaponData().Right);
		}

	}

}

//=============================================================================
// 描画処理
//=============================================================================
void CWeaponManager::Draw(void)
{
}
