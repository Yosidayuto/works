//=============================================================================
//
// ゴールブロックベース [goal block base.cpp]
// Author : 吉田悠人
//
//=============================================================================

//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "goal block base.h"
#include "renderer.h"
#include "model.h"
#include "child.h"
#include "item block base.h"
#include "fade.h"
#include "player.h"
#include "particle.h"
#include "inputcontroller.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CGoalBlockBase::CGoalBlockBase()
{
	SetObjType(OBJTYPE_GOAL);
	m_MapType	= CGame::MAP_TYPE_1;
	m_bGoal		= true;
}
//=============================================================================
// デストラクタ
//=============================================================================
CGoalBlockBase::~CGoalBlockBase()
{
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CGoalBlockBase::Init(void)
{
	CBlockBase::Init();
	SetPriority(PRIORITY_OBJECT_TILE);
	GetModel()->SetPriority(PRIORITY_OBJECT_TILE);
	return S_OK;
}

//=============================================================================
// 更新関数
//=============================================================================
void CGoalBlockBase::Update(void)
{
	CBlockBase::Update();

	if (m_bGoal)
	{
		GoalCollision();
	}
}

//=============================================================================
// ゴールの当たり判定関数
//=============================================================================
void CGoalBlockBase::GoalCollision(void)
{
	//現在の位置取得
	D3DXVECTOR3 pos = GetPosition();
	CParticle*pParticle = NULL;
	CChild * pChild = dynamic_cast<CChild*>(GetTop()[PRIORITY_OBJECT_CHILD]);

	while (pChild != NULL)
	{
		if (pChild->GetIsActive())
		{
			// ワールド座標の取得
			CModel::MODELDATA modelData = pChild->GetModel()->GetModelData();
			D3DXVECTOR3 worldPos = D3DXVECTOR3(modelData.mtxWorld._41, modelData.mtxWorld._42, modelData.mtxWorld._43);

			//範囲に入ると(Y軸は高さ分+と誤差をなくすために+1)
			if (pos.x + GOAL_RANGE>worldPos.x
				&&pos.x - GOAL_RANGE<worldPos.x
				&&pos.y + GOAL_RANGE*2.0f+1>worldPos.y
				&&pos.z + GOAL_RANGE>worldPos.z
				&&pos.z - GOAL_RANGE<worldPos.z)
			{	

				for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
				{
					//パーティクルの処理
					pParticle = CParticle::Cretae(pos, worldPos, D3DXVECTOR3(10.0f, 10.0f, 10.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CParticle::PARTICLE_TYPE_2);
				}

				//ゴール処理
				Goal();
				// コントローラー十字キーの値の取得
				CInputJoyStick* pJoyInput = (CInputJoyStick*)CManager::GetInputController();
				pJoyInput->SetVibration(0);

				//プレイヤーのゴールに当たった時の処理
				CPlayer::GetPlayer()->Goal();
			}
		}
		//次のポインタを取得
		pChild = dynamic_cast<CChild*>(pChild->GetNext());
	}

}

//=============================================================================
// アイテムサーチ関数
//=============================================================================
bool CGoalBlockBase::ItemSearch(void)
{
	CItemBlockBase * pItem = dynamic_cast<CItemBlockBase*>(GetTop()[PRIORITY_OBJECT_ITEM]);

	while (pItem != NULL)
	{
		return false;
	}
	
	return true;
}

//=============================================================================
// ゴール処理関数
//=============================================================================
void CGoalBlockBase::Goal(void)
{
	//フェード取得
	CFade*	pFade = CManager::GetFadeout();

	//アイテムがないか
	if (ItemSearch())
	{
		//ステージのフェード
		if (m_MapType < CGame::MAP_TYPE_3)
		{
			//次のステージにフェード
			pFade->SetWhiteout(CGame::MAP_TYPE(m_MapType+1));
		}
	}
}

//=============================================================================
// マップセッター
//=============================================================================
void CGoalBlockBase::SetMapType(CGame::MAP_TYPE MapType)
{
	m_MapType = MapType;
}

//=============================================================================
// マップゲット
//=============================================================================
CGame::MAP_TYPE CGoalBlockBase::GetMapType(void)
{
	return m_MapType;
}

//=============================================================================
// ゴール機能セッター
//=============================================================================
void CGoalBlockBase::SetGoal(bool bGoal)
{
	m_bGoal = bGoal;
}


//=============================================================================
// ゴール機能ゲッター
//=============================================================================
bool CGoalBlockBase::GetGoal(void)
{
	return m_bGoal;
}
