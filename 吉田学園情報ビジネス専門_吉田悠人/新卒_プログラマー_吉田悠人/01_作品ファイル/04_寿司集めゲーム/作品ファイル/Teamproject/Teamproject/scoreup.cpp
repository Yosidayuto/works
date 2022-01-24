//=============================================================================
//
// アイテム[shield.h]
// Author : 齋藤大行
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "scoreup.h"
#include "resource manager.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CScoreup::CScoreup()
{
}

//=============================================================================
// 生成処理関数
//=============================================================================
CScoreup * CScoreup::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//メモリー確保
	CScoreup *pScoreup;
	pScoreup = new CScoreup;

	//Resourceの呼び出し
	CResource* pResource = CManager::GetResource();
	MODELDATA Model = pResource->ModelLoad(pScoreup->m_nScoreupModel);

	//NULLチェック
	if (pScoreup != NULL)
	{
		pScoreup->SetPos(pos);			// 位置設定
		pScoreup->SetSize(size);		// サイズ設定7
		pScoreup->SetItem(ITEM_SCOREUP);
		pScoreup->SetModelData(Model);	// モデル設定

		pScoreup->Init();				//初期化処理
	}
	return pScoreup;
}

void CScoreup::ItemEffect(CPlayer* pPlayer)
{
	//スコアアップの処理
	pPlayer->ScoreUpGet();
}


