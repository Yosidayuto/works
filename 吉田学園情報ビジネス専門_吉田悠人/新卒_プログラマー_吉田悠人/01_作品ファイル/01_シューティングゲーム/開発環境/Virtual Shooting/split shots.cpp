//=============================================================================
//
// 分裂ショット処理 [split shots.cpp]
// Author : 吉田悠人
//
//=============================================================================
//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "shots base.h"
#include "scene.h"
#include "scene2d.h"
#include "split shots.h"
#include "enemy bullet.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define SHOTS_FIRST_SPEED	(3.5f)	// 初弾の弾速
#define SHOTS_SPEED			(0.7f)	// 初弾以外の弾速

#define SHOTS_NUMBER		(10)	// ショットの回数
#define SHOTS_TIME			(20)	// 攻撃の時間の間隔

//=============================================================================
// コンストラクト
//=============================================================================
CSplitShots::CSplitShots()
{
	m_pEnemyBullet = NULL;
	m_nBullet = 0;
	memset(m_bBullet, false, sizeof(m_bBullet));
}

//=============================================================================
// 生成処理
//=============================================================================
CSplitShots * CSplitShots::Create(D3DXVECTOR3 pos)
{
	//メモリの確保
	CSplitShots* pSplitShots = NULL;
	pSplitShots = new CSplitShots;

	//NULLチェック
	if (pSplitShots != NULL)
	{
		//位置設定
		pSplitShots->SetPos(pos);
		//向き設定
		pSplitShots->Tracking(SHOTS_SPEED);
	}
	return pSplitShots;
}

//=============================================================================
// ショット処理
//=============================================================================
void CSplitShots::Shots(void)
{
	//位置取得
	D3DXVECTOR3 pos = GetPos();
	//向き取得
	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//カウントプラス
	m_nBullet++;

	//ショット処理
	if (m_pEnemyBullet==NULL)
	{
		m_pEnemyBullet = CEnemyBullet::Create(pos, D3DXVECTOR3(0.0f, SHOTS_FIRST_SPEED, 0.0f));
	}
	//初弾のNULLチェック
	if (m_pEnemyBullet != NULL)
	{
		//10回分のショット処理
		for (int nNumber = 0; nNumber<SHOTS_NUMBER; nNumber++)
		{
			if (m_nBullet == (SHOTS_TIME)  * (nNumber))
			{
					//初弾が通った後に右左に弾を撃つ
					CEnemyBullet::Create(m_pEnemyBullet->GetPos(), D3DXVECTOR3(SHOTS_SPEED, 0.0f, 0.0f));
					CEnemyBullet::Create(m_pEnemyBullet->GetPos(), D3DXVECTOR3(-SHOTS_SPEED, 0.0f, 0.0f));
					m_bBullet[nNumber] = true;
					m_bBullet[SHOTS_NUMBER + nNumber] = true;

			}
		}
	}
	//終了
	if (m_bBullet[MAX_SPLIT_SHOTS - 1] == true)
	{
		SetShotsEnd(true);
		return;
	}
}
