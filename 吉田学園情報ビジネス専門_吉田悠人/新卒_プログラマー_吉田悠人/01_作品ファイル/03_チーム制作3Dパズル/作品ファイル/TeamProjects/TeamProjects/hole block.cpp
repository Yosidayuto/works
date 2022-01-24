//=============================================================================
//
// 砂ブロック [sand block.cpp]
// Author : 吉田悠人
//
//=============================================================================

//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "hole block.h"
#include "resource manager.h"
#include "manager.h"
#include "renderer.h"
#include "object.h"
#include "model.h"
#include "model object.h"
#include "fade.h"
#include "sprout block.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CHoleBlock::CHoleBlock()
{
}
//=============================================================================
// デストラクタ
//=============================================================================
CHoleBlock::~CHoleBlock()
{
}


//=============================================================================
// 生成関数
//=============================================================================
CHoleBlock * CHoleBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, CGame::MAP_TYPE MapType)
{
	//メモリ確保
	CHoleBlock* pHoleBlock = NULL;
	pHoleBlock = new CHoleBlock;
	//リソース確保
	CResource* pResource = CManager::GetResource();
	CModel::MODELDATA Model = pResource->ModelLoad(pHoleBlock->m_nModel);

	//NULLチェック
	if (pHoleBlock != NULL)
	{
		//位置設定
		pHoleBlock->SetPosition(D3DXVECTOR3(pos.x, pos.y - BLOCK_HEIGHT, pos.z));
		//向き設定
		pHoleBlock->SetRotation(rot);
		//カラー設定
		pHoleBlock->SetScale(size);
		//マップ設定
		pHoleBlock->SetMapType(MapType);
		//モデル設定
		pHoleBlock->SetModelData(Model);
		//初期化処理
		pHoleBlock->Init();
	}

	return pHoleBlock;
}

//=============================================================================
// 更新関数
//=============================================================================
void CHoleBlock::Update(void)
{
	CGoalBlockBase::Update();
	GoalCollision();
}

//=============================================================================
// ゴール処理関数
//=============================================================================
void CHoleBlock::Goal(void)
{
	//フェード取得
	CFade*	pFade = CManager::GetFadeout();
	//位置取得
	D3DXVECTOR3 pos = GetPosition();

	//パーティクル生成
	
	//終了処理
	CHoleBlock::Uninit();

	//芽ブロック生成
	CSproutBlock::Create(D3DXVECTOR3(pos.x, 0, pos.z), GetRotation(), GetScale());

	//アイテムがないか
	if (ItemSearch())
	{
		//ステージのフェード
		if (GetMapType() < CGame::MAP_TYPE_3)
		{
			//次のステージにフェード
			pFade->SetWhiteout(CGame::MAP_TYPE(GetMapType() + 1));

		}
	}

}

