//=============================================================================
//
// マップ管理の処理 [map_manager.cpp]
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
#include "map_manager.h"
#include "resource manager.h"
#include "map.h"
#include "locationpoint.h"
#include "game.h"
#include "player.h"
#include "player control.h"
#include "Fieldmanager.h"
#include "MapEdgeMask.h"
#include "MapEdgeOverlay.h"
#include "MapEdgeMaskOut.h"
#include "timer.h"
#include "ebi.h"
#include "egg.h"
#include "ikura.h"
#include "salmon.h"
#include "tuna.h"
#include "scoreup.h"
#include "shield.h"
#include <time.h>


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAP_LOCATION_VALUE		(0.34f) //マップ表示の現在位置補正値
#define MAP_SHRINK_TIME			(10)	//この秒数おきに縮んでく
#define MAP_SHIRINK_SIZE		(2.0f)	//縮むスピード
#define MAP_SHIRINK_TIME_VALUE	(60)	//1縮小で縮む量（フレーム）
#define MAP_LAST_SIZE			(50.0f) //最後のマップサイズ
#define MAX_SUSHI_SPAWN			(30*7)	//餌のスポーンまでの最大時間
#define MIN_SUSHI_SPAWN			(30*2)	//餌のスポーンまでの最低時間
#define MAX_SUSHI_NUMBER		(10)		//餌がスポーンするときの最大個数
//*****************************************************************************
// 静的メンバー変数初期化
//*****************************************************************************
int CMapManager::m_nSushiProb[CFoodBase::TYPE_MAX] =
{
	//寿司の出現確率
	20,				
	20,
	20,
	20,
	20,
};
//寿司の最大確率
int CMapManager::m_nMaxSushiProb = m_nSushiProb[CFoodBase::TYPE_EBI] + m_nSushiProb[CFoodBase::TYPE_EGG] + m_nSushiProb[CFoodBase::TYPE_IKURA] + m_nSushiProb[CFoodBase::TYPE_SALMON] + m_nSushiProb[CFoodBase::TYPE_TUNA];

int CMapManager::m_nItemProb[CItem::ITEM_MAX]=
{
	//アイテムの出現確率
	50,		//スコアアップ
	50		//シールド
};
int CMapManager::m_nMaxItemProb = m_nItemProb[CItem::ITEM_SCOREUP] + m_nItemProb[CItem::ITEM_SHIELD];
int CMapManager::m_nSpawnItemCount[CGame::GAMESTATE_MAX] =
{
	0,
	5,
	3,
	3,
	2,
	1
};
//=============================================================================
// コンストラクタ
//=============================================================================
CMapManager::CMapManager(int nPriority) : CScene(nPriority)
{
    m_originPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_pMapEdgeMask	= nullptr;
	m_pFieldManager = nullptr;
	m_nShrinkCount = 1;
	m_bShirnk = false;
	m_nSushiSpawn = 0;		// 寿司のスポーンする時間の初期化
	m_nSpawnSushiCount = 0;	// 寿司のスポーンする時間までのカウントの初期化
}

//=============================================================================
// デストラクタ
//=============================================================================
CMapManager::~CMapManager()
{

}

//=============================================================================
// 生成処理
//=============================================================================
CMapManager * CMapManager::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size)
{
    CMapManager *pMap = nullptr;

    pMap = new CMapManager;
    if (pMap != nullptr)
    {
        pMap->m_originPos = Pos;
        pMap->m_MapSize = Size;
        pMap->Init();
    }
    return pMap;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CMapManager::Init(void)
{
	//現在の状態を取得
	m_GameState = CGame::GetGameState();
    //ステージ生成
    m_pFieldManager = CFieldManager::Create(D3DXVECTOR3(0.0f, -50.0f, 0.0f), m_MapSize);
    //ステージ生成（現在のフィールド）
    m_pMapEdgeMask = CMapEdgeMask::Create(D3DXVECTOR3(0.0f, -50.0f, 0.0f), m_MapSize);
    //ステージ生成（フィールド外側）
    CMapEdgeOverlay::Create(D3DXVECTOR3(0.0f, -49.0f, 0.0f), m_MapSize * 2.0f);
    //ミニマップ生成
    CMap::Create(m_originPos,D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT,0.0f));

    //プレイヤー位置の生成
    m_pLocationPoint[0] = CLocationPoint::Create(m_originPos, D3DXVECTOR3(20.0f, 20.0f, 0.0f),0);
    //プレイヤー位置の生成
    m_pLocationPoint[1] = CLocationPoint::Create(m_originPos, D3DXVECTOR3(20.0f, 20.0f, 0.0f), 1);
    //プレイヤー位置の生成
    m_pLocationPoint[2] = CLocationPoint::Create(m_originPos, D3DXVECTOR3(20.0f, 20.0f, 0.0f), 2);
    //プレイヤー位置の生成
    m_pLocationPoint[3] = CLocationPoint::Create(m_originPos, D3DXVECTOR3(20.0f, 20.0f, 0.0f), 3);
    return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CMapManager::Uninit(void)
{
    Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CMapManager::Update(void)
{
	//1フレーム前の状態を格納しておく
	CGame::GAME_STATE OldGameState = m_GameState;
	//現在の状態を取得
	m_GameState = CGame::GetGameState();
	//収縮時間が来たか調べる
	if (m_GameState != OldGameState)//異なっていたら収縮開始
	{
		m_bShirnk = true;
	}
	
	if (m_bShirnk == true && m_nShrinkCount < MAP_SHIRINK_TIME_VALUE)
	{
		if (m_MapSize.x > MAP_LAST_SIZE)//最小サイズになるまで縮ませる
		{
			//ステージ収縮
			m_MapSize.x -= MAP_SHIRINK_SIZE;
			m_MapSize.y -= MAP_SHIRINK_SIZE;
			m_MapSize.z -= MAP_SHIRINK_SIZE;
			m_nShrinkCount++;
		}
	}
	else if (m_bShirnk == true && m_nShrinkCount >= MAP_SHIRINK_TIME_VALUE)
	{
		m_bShirnk = false;	//収縮状態を元に戻す
		m_nShrinkCount = 0;	//初期化
		ItemSpawn();		//アイテムの生成
	}

    //サイズセット
    m_pMapEdgeMask->SetSize(m_MapSize);
    m_pFieldManager->SetSize(m_MapSize);

    for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
    {
        //プレイヤーの位置取得
        D3DXVECTOR3 pos = CManager::GetPlayerControl()->GetPlayer(nCount)->GetPos();
        //プレイヤーの現在位置をセット
        m_pLocationPoint[nCount]->SetPos(D3DXVECTOR3(m_originPos.x + pos.x * MAP_LOCATION_VALUE, m_originPos.y - pos.z * MAP_LOCATION_VALUE, 0.0f));
    }

	//餌の生成処理
	SushiSpawn();

}
//=============================================================================
// 描画処理
//=============================================================================
void CMapManager::Draw(void)
{
    
}

//=============================================================================
// 寿司のランダム生成処理関数
//=============================================================================
void CMapManager::SushiSpawn(void)
{
	//カウントダウン
	m_nSpawnSushiCount++;
	//カウントが一定に達したらランダムにスポーン
	if (m_nSpawnSushiCount>m_nSushiSpawn)
	{
		//エリアの半径
		float fRadius = (m_MapSize.x / 2) - 50;//(ココの数値を範囲制限の円の半径にするそして余裕をもって-50)
		//中心値
		D3DXVECTOR3 centre = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//(ココの数値を範囲制限の円の中心を取得)
		
		srand((unsigned int)time(NULL));			//ランダム関数の初期化
		int nNumber = rand() % MAX_SUSHI_NUMBER + 1; //ランダムに何個の寿司をスポーンさせるか決める(+1は確実に一つ餌を出すため)

		//ランダムに決めた個数分スポーンさせる
		for (int nSushiNumber = 0; nSushiNumber < nNumber; nSushiNumber++)
		{
			float fAngle = (float)(rand() % 360 + 1);	//ランダムで角度を決める
			
			float nDistance = (float)(rand() % (int)fRadius);	//ランダムな距離を取得

			//ランダムリスポーン位置
			D3DXVECTOR3 random = centre + D3DXVECTOR3((nDistance*cos(fAngle)), 0.0f, (nDistance*sin(fAngle)));

			//ランダムにどの寿司をスポーンさせるか決める
			int nSpawn = rand() % m_nMaxSushiProb;				//ランダムに値を取得

			int nProd = 0;//確率用の変数
			
			//どの寿司がスポーンするか
			for (int nSushi = 0; nSushi < (int)(CFoodBase::TYPE_MAX); nSushi++)
			{
				//確率を足してく
				nProd += m_nSushiProb[nSushi];
				//確率の確認
				if (nSpawn <= nProd)
				{
					//カウント初期化
					m_nSpawnSushiCount = 0;
					//ランダムに次のスポーン時間を決める
					m_nSushiSpawn = rand() % MAX_SUSHI_SPAWN + 1;

					//最小値より低ければ
					if (m_nSushiSpawn<MIN_SUSHI_SPAWN)
					{
						//最小値に合わせる
						m_nSushiSpawn = MIN_SUSHI_SPAWN;
					}

					//寿司のスポーン生成
					switch (nSushi)
					{
					case CFoodBase::TYPE_EBI:
						CEbi::Create(random, D3DXVECTOR3(10.0f, 10.0f, 10.0f));
						break;
					case CFoodBase::TYPE_EGG:
						CEgg::Create(random, D3DXVECTOR3(10.0f, 10.0f, 10.0f));
						break;
					case CFoodBase::TYPE_IKURA:
						CIkura::Create(random, D3DXVECTOR3(10.0f, 10.0f, 10.0f));
						break;
					case CFoodBase::TYPE_SALMON:
						CSalmon::Create(random, D3DXVECTOR3(10.0f, 10.0f, 10.0f));
						break;
					case CFoodBase::TYPE_TUNA:
						CTuna::Create(random, D3DXVECTOR3(10.0f, 10.0f, 10.0f));
						break;
					}
					break;
				}
			
			}
		}
	}
}

//=============================================================================
// アイテムのランダム生成処理関数
//=============================================================================
void CMapManager::ItemSpawn(void)
{
	//カウントが一定に達したらランダムにスポーン
	for(int nCoutn=0; nCoutn<m_nSpawnItemCount[m_GameState]; nCoutn++)
	{
		//エリアの半径
		float fRadius = (m_MapSize.x / 2) - 50;//(ココの数値を範囲制限の円の半径にするそして余裕をもって-50)
		 //中心値
		D3DXVECTOR3 centre = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//(ココの数値を範囲制限の円の中心を取得)

		//ランダム角度
		srand((unsigned int)time(NULL));			//ランダム関数の初期化
		float fAngle = (float)(rand() % 360 + 1);	//ランダムで角度を決める

		//ランダムな距離
		int nDistance = rand() % (int)fRadius;		//ランダムな距離を取得

		//ランダムリスポーン位置
		D3DXVECTOR3 random = centre + D3DXVECTOR3((float)(nDistance*cos(fAngle)), 0.0f, (float)(nDistance*sin(fAngle)));

		//ランダムにどのアイテムをスポーンさせるか決める
		int nSpawn = rand() % m_nMaxItemProb;			//ランダムに値を取得

		int nProd = 0;//確率用の変数

		//どのアイテムがスポーンするか
		for (int nItem = 0; nItem < CItem::ITEM_MAX; nItem++)
		{
			// 確率を足してく
			nProd += m_nItemProb[nItem];
			// 確率の確認
			if (nSpawn <= nProd)
			{
				//アイテムのスポーン生成
				switch (nItem)
				{
				case CItem::ITEM_SCOREUP:	//スコアアップ生成
					CScoreup::Create(random, D3DXVECTOR3(1.0f, 1.0f, 1.0f));
					break;
				case CItem::ITEM_SHIELD:	//シールド生成
					CShield::Create(random, D3DXVECTOR3(1.0f, 1.0f, 1.0f));
					break;
				}
				break;
			}
		}
	}

}
