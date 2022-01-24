//=============================================================================
//
// フィールド管理 [fieldmanager.cpp]
// Author : 林川紗梨夏
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "fieldmanager.h"
#include "resource manager.h"
#include "map.h"
#include "locationpoint.h"
#include "game.h"
#include "player.h"
#include "floor.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAP_SIZE (500.0f)		//マッぷサイズ
#define PLAYER_HIT_SIZE (5.0f)	//マッぷサイズ


//=============================================================================
// コンストラクタ
//=============================================================================
CFieldManager::CFieldManager(int nPriority) : CScene(nPriority)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CFieldManager::~CFieldManager()
{

}

//=============================================================================
// 生成処理
//=============================================================================
CFieldManager * CFieldManager::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size)
{
	CFieldManager *pMap = nullptr;

	pMap = new CFieldManager;
	if (pMap != nullptr)
	{
		pMap->m_size = Size;
		pMap->Init();
	}
	return pMap;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CFieldManager::Init(void)
{
	//床生成
	CFloor::Create(D3DXVECTOR3(0.0f, -50.0f, 0.0f), D3DXVECTOR3(m_size.x, m_size.z, m_size.z));
	m_originsize = m_size;//マップ最大のサイズを格納しておく
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CFieldManager::Uninit(void)
{
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CFieldManager::Update(void)
{
	//端当たり判定
	EdgeCollision();

}
//=============================================================================
// 描画処理
//=============================================================================
void CFieldManager::Draw(void)
{

}

void CFieldManager::SetSize(D3DXVECTOR3 Size)
{
	m_size = Size;
}

//=============================================================================
// 端死亡処理
//=============================================================================
void CFieldManager::EdgeCollision(void)
{
	CScene* pTop[PRIORITY_MAX] = {};
	CScene* pNext = nullptr;
	D3DXVECTOR3 distance; //プレイヤーと敵の距離
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		//リスト先頭取得
		pTop[nCount] = *(CScene::GetTop() + nCount);
	}

	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		if (pTop[nCount] != nullptr)
		{
			pNext = pTop[nCount];
			while (pNext != nullptr)
			{
				//pNext(CScene)をCPlayerにダウンキャスト
				CPlayer * pPlayer = dynamic_cast<CPlayer*> (pNext);
				if (pPlayer != nullptr)
				{
					distance = pPlayer->GetPos();//マップの原点が０、０なのでこのままプレイヤーの位置入れる

					//敵とプレイヤーの距離がそれぞれの半径の和より大きかったらマップからはみ出てる
					if (powf(distance.x, 2) + powf(distance.z, 2)
						>= pow(((m_size.x / 2) + PLAYER_HIT_SIZE), 2))
					{
						//死亡処理（マップ収縮２５％以下なら）
						//それ以外はリスポーン
						pPlayer->BarrierHit();
					}
					
				}
				//次の対象を読み込む
				pNext = pNext->GetNext();
			}
		}
	}
}