//=============================================================================
//
// リザルトエフェクト(寿司が降ってくる) [result effect.h]
// Author : 吉田悠人
//
//=============================================================================
//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "result effect.h"
#include "food base.h"
#include "floor.h"
#include "ebi.h"
#include "egg.h"
#include "ikura.h"
#include "salmon.h"
#include "tuna.h"
#include "sushi model.h"
#include "sushi bg.h"
#include <time.h>

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_SPAWN_COUNT (10)	//寿司生成のカウント
#define MOVE_SPEED (5)
//=============================================================================
// コンストラクタ
//=============================================================================
CResultEffect::CResultEffect(int nPriority):CScene(nPriority)
{
	for (int nSushi = 0; nSushi < MAX_SUSHI_EFFECT; nSushi++)
	{
		m_pSushi[nSushi] = nullptr;
	}
	m_nSpawnCount = 0;
	m_nSushiCount = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CResultEffect::~CResultEffect()
{
}

//=============================================================================
// 生成処理
//=============================================================================
CResultEffect * CResultEffect::Create()
{
	//メモリ確保
	CResultEffect* pResultEffect = nullptr;
	pResultEffect = new CResultEffect;

	//NULLチェック
	if (pResultEffect != nullptr)
	{
		pResultEffect->Init();
	}

	return pResultEffect;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CResultEffect::Init(void)
{
	CSushiBg::Create(D3DXVECTOR3(0.0f, -700.0f, 0.0f), D3DXVECTOR3(1600.0f, 1200.0f, 0.0f));
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CResultEffect::Uninit(void)
{
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CResultEffect::Update(void)
{
	//寿司のランダム生成処理
	RandomSpawn();
	////寿司の移動処理
	//MoveSushi();
	////寿司の画面外処理
	//Offscreen();

}

//=============================================================================
// 描画処理関数
//=============================================================================
void CResultEffect::Draw(void)
{

}

//=============================================================================
// 寿司のランダム生成処理関数
//=============================================================================
void CResultEffect::RandomSpawn(void)
{

	////取得した数値が１より下の場合
	//if (m_nSpawnCount>MAX_SPAWN_COUNT)
	//{
	//	//生成位置
	//	D3DXVECTOR3 pos;
	//	//ランダムでX位置を設定
	//	float XPosRandom = (float)(rand() % 500 * 2) - 500 ;
	//	pos = D3DXVECTOR3(XPosRandom, -250.0f, 300.0f);
	//	
	//	for (int nSushi = 0; nSushi < MAX_SUSHI_EFFECT; nSushi++)
	//	{
	//		if (m_pSushi[nSushi] == NULL)
	//		{
	//			//ランダムにどの寿司をスポーンさせるか決める
	//			srand(nSushi);
	//			int nSushiType = rand() % 3;			//ランダムに値を取得
	//			//寿司のスポーン生成
	//			m_pSushi[nSushi] = CSushiModel::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f), nSushiType);
	//			
	//			//現在の寿司の数をプラス
	//			m_nSushiCount += 1;

	//			//数値の初期化
	//			m_nSpawnCount = 0;
	//			return;
	//		}
	//	}
	//}

	//カウントアップ
	m_nSpawnCount++;
	if (m_nSpawnCount % MAX_SPAWN_COUNT == 0)
	{
			//生成位置
			D3DXVECTOR3 pos;
			//ランダムでX位置を設定
			float XPosRandom = (float)(rand() % 500 * 2) - 500 ;
			pos = D3DXVECTOR3(XPosRandom, -250.0f, 300.0f);
			
			//ランダムにどの寿司をスポーンさせるか決める
			srand(m_nSpawnCount);
			int nSushiType = rand() % 3;			//ランダムに値を取得
			//寿司のスポーン生成
			CSushiModel::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f), nSushiType);
	}
}

//=============================================================================
// 寿司の移動処理
//=============================================================================
void CResultEffect::MoveSushi(void)
{
	for (int nSushi = 0; nSushi < MAX_SUSHI_EFFECT; nSushi++)
	{
		if (m_pSushi[nSushi] != NULL)
		{
			//位置取得
			D3DXVECTOR3 pos = m_pSushi[nSushi]->GetPos();
			//位置の更新
			pos.z -= MOVE_SPEED;
			//位置セット
			m_pSushi[nSushi]->SetPos(pos);
		}
	}
}

//=============================================================================
// 寿司の画面外処理関数
//=============================================================================
void CResultEffect::Offscreen(void)
{
	for (int nSushi = 0; nSushi < MAX_SUSHI_EFFECT; nSushi++)
	{
		if (m_pSushi[nSushi] != NULL)
		{
			//位置取得
			D3DXVECTOR3 pos = m_pSushi[nSushi]->GetPos();
			//画面外に出ているか
			if (pos.y>SCREEN_HEIGHT + 40)
			{
				//画面外にいる時に消去
				m_pSushi[nSushi]->Uninit();
				m_pSushi[nSushi] = NULL;
				//最大数を減らす
				m_nSushiCount -= 1;
			}
		}
	}
}
