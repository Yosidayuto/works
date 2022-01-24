//=============================================================================
//
// アイテム[shield.h]
// Author : 齋藤大行
//
//=============================================================================
//=============================================================================
//インクルードファイル
//=============================================================================
#include "shield.h"
#include "resource manager.h"
#include "manager.h"
#include "renderer.h"
#include "scoreup.h"
#include "player.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CShield::CShield()
{
}

//=============================================================================
// 生成処理関数
//=============================================================================
CShield * CShield::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//メモリー確保
	CShield *pShield;
	pShield = new CShield;

	//Resourceの呼び出し
	CResource* pResource = CManager::GetResource();
	MODELDATA Model = pResource->ModelLoad(pShield->m_nShieldModel);

	//NULLチェック
	if (pShield != NULL)
	{
		pShield->SetPos(pos);			// 位置設定
		pShield->SetSize(size);			// サイズ設定
		pShield->SetItem(ITEM_SHIELD);
		pShield->SetModelData(Model);	// モデル設定
		pShield->Init();				//初期化処理
	}
	return pShield;
}

void CShield::ItemEffect(CPlayer* pPlayer)
{
	//シールドの処理
	pPlayer->ShieldGet();
}


