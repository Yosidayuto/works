//=============================================================================
//
// 食べ物ベース [food base.cpp]
// Author : 吉田悠人
//
//=============================================================================

//=============================================================================
// ヘッダーファイル
//=============================================================================
#include "food base.h"
#include "player.h"
#include "sound.h"
#include "manager.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define FOOD_HIT (5.0f)	//プレイヤーの当たり判定

//=============================================================================
// コンストラクタ
//=============================================================================
CFoodBase::CFoodBase(int nPriority) : CBillboard(nPriority)
{
	SetObjType(OBJTYPE_SUSHI);								// オブジェクトタイプ設定
	m_nPoint = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CFoodBase::~CFoodBase()
{

}

//=============================================================================
// 更新処理関数
//=============================================================================
void CFoodBase::Update(void)
{
	//プレイヤーとの当たり判定
	Collision();
}

//=============================================================================
// 当たり判定関数
//=============================================================================
void CFoodBase::Collision(void)
{
	//シーン取得用
	CScene* pTop[PRIORITY_MAX] = {};
	//次チェックするシーンのポインタ
	CScene* pNext = NULL;
	//位置取得
	D3DXVECTOR3 pos = GetPos();

	//topのアドレスを取得
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		pTop[nCount] = *(CScene::GetTop() + nCount);
	}

	//オブジェクト探査
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		if (pTop[nCount] != NULL)
		{
			pNext = pTop[nCount];
			//その描画優先度のオブジェクトがなくなるまでループ
			while (pNext != NULL)
			{
				if (pNext->GetObjType() == CScene::OBJTYPE_PLAYER)
				{
					//プレイヤーの位置取得
					D3DXVECTOR3 PlayerPos = ((CPlayer*)pNext)->GetPos();
					
					//プレイヤーが近くにいるか
					if (PlayerPos.x + FOOD_HIT>pos.x
						&&PlayerPos.x - FOOD_HIT<pos.x
						&&PlayerPos.z + FOOD_HIT>pos.z
						&&PlayerPos.z - FOOD_HIT<pos.z)
					{
			
						//取得音
						CSound *pSound = CManager::GetSound();
						pSound->PlaySound(CSound::LABEL_SE_GETSUSHI);

						//パーツを追加
						((CPlayer*)pNext)->AddParts(m_FoodType);

						//スコアアップ状態ならもう一度追加
						if (((CPlayer*)pNext)->GetScoreUp() == true)
						{
							((CPlayer*)pNext)->AddParts(m_FoodType);
						}
						//終了処理で消す
						Uninit();
						return;
					}
				}
				//次のオブジェクトのポインタを更新
				pNext = pNext->GetNext();
			}
		}
	}

}

//=============================================================================
// ポイントセッター関数
//=============================================================================
void CFoodBase::SetPoint(int nPoint)
{
	m_nPoint = nPoint;
}
