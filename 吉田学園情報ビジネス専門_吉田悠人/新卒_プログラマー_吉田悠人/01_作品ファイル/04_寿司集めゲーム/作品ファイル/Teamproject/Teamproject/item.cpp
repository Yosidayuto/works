//=============================================================================
//
// アイテムベース [item.cpp]
// Author : 齋藤大行
//
//=============================================================================

//=============================================================================
// ヘッダーファイル
//=============================================================================
#include "item.h"
#include "player.h"
#include "shield.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define ITEM_HIT (10.0f)	//プレイヤーの当たり判定

//=============================================================================
// コンストラクタ
//=============================================================================
CItem::CItem(int nPriority)
{
	SetObjType(OBJTYPE_ITEM);
}

//=============================================================================
// デストラクタ
//=============================================================================
CItem::~CItem()
{
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CItem::Update(void)
{
	Collision();
}


//=============================================================================
// 当たり判定関数
//=============================================================================
void CItem::Collision(void)
{
	//シーンのポインター
	CScene* pTop[PRIORITY_MAX] = {};
	//nextのポインタ
	CScene* pNext = NULL;
	//位置取得
	D3DXVECTOR3 pos = GetPos();

	//topがどこにあるか確認
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
					if (PlayerPos.x + ITEM_HIT>pos.x
						&&PlayerPos.x - ITEM_HIT<pos.x
						&&PlayerPos.z + ITEM_HIT>pos.z
						&&PlayerPos.z - ITEM_HIT<pos.z)
					{
						//タイプ取得
						ITEM type = GetType();

						//アイテムの効果（タイプ）
						ItemEffect(((CPlayer*)pNext));
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
// アイテムタイプ設定
//=============================================================================
void CItem::SetItem(ITEM item)
{
	m_ItemType = item;
}
