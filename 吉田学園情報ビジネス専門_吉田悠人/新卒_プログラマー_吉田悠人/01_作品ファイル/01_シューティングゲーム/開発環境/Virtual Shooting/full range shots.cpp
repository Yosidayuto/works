//=============================================================================
//
// 全方位ショット処理 [full range shots.cpp]
// Author : 吉田悠人
//
//=============================================================================
//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "shots base.h"
#include "scene.h"
#include "scene2d.h"
#include "full range shots.h"
#include "enemy bullet.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define SHOTS_SPEED			(4.0f)		//弾速
#define SHOTS_NUMBER		(10)		//ショットの回数
#define SHOTS_BULLET		(20)		//一回に撃つ弾丸数

//=============================================================================
// コンストラクト
//=============================================================================
CFullRange::CFullRange()
{
	m_nBullet = 0;
	memset(m_bBullet, false, sizeof(m_bBullet));
}

//=============================================================================
// 生成処理
//=============================================================================
CFullRange * CFullRange::Create(D3DXVECTOR3 pos)
{
	//メモリの確保
	CFullRange* pFullRange = NULL;
	pFullRange = new CFullRange;

	//NULLチェック
	if (pFullRange != NULL)
	{
		//位置設定
		pFullRange->SetPos(pos);
		//向き設定
		pFullRange->Tracking(SHOTS_SPEED);
	}

	return pFullRange;
}

//=============================================================================
// ショット処理
//=============================================================================
void CFullRange::Shots(void)
{
	//位置取得
	D3DXVECTOR3 pos = GetPos();
	//向き取得
	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	//カウントプラス
	m_nBullet++;

	//ショット処理
	for (int nNumber = 0; nNumber < SHOTS_NUMBER; nNumber++)
	{
		//十回の間隔の処理
		if (m_nBullet == SHOTS_NUMBER * nNumber)
		{
			//一回に撃ちだす弾の処理
			for (int nBullet = 0; nBullet < SHOTS_BULLET; nBullet++)
			{
				//向きを設定
				rot.x = sinf(Tracking() + (2.0f*nBullet + (SHOTS_BULLET*(nNumber + 1))))*SHOTS_SPEED;
				rot.y = cosf(Tracking() + (2.0f*nBullet + (SHOTS_BULLET*(nNumber + 1))))*SHOTS_SPEED;
				//バレット生成
				CEnemyBullet::Create(pos, rot);
				//バレット使用状態に
				m_bBullet[nBullet + (SHOTS_BULLET*(nNumber + 1))] = true;

			}
		}
	}

	//終了
	if (m_bBullet[MAX_FULL_RANGE-1] == true)
	{
		SetShotsEnd(true);
		return;
	}
}

