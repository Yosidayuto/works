//=============================================================================
//
// ショット処理 [shots.cpp]
// Author : 吉田悠人
//
//=============================================================================
//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "shots base.h"
#include "scene.h"
#include "scene2d.h"
#include "buckshot.h"
#include "enemy bullet.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define SHOTS_SPEED			(7.0f)		//弾速

//=============================================================================
// コンストラクト
//=============================================================================
CBuckShot::CBuckShot()
{
	m_nBullet = 0;
	memset(m_bBullet, false, sizeof(m_bBullet));
}

//=============================================================================
// 生成処理
//=============================================================================
CBuckShot * CBuckShot::Create(D3DXVECTOR3 pos)
{
	//メモリの確保
	CBuckShot* pBuckShot = NULL;
	pBuckShot = new CBuckShot;

	//NULLチェック
	if (pBuckShot != NULL)
	{
		//位置設定
		pBuckShot->SetPos(pos);
		//向き設定
		pBuckShot->Tracking(SHOTS_SPEED);
	}
	return pBuckShot;
}

//=============================================================================
// ショット処理
//=============================================================================
void CBuckShot::Shots(void)
{
	//位置取得
	D3DXVECTOR3 pos = GetPos();
	//向き取得
	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f,0.0f,0.0f);

	//カウントプラス
	m_nBullet++;

	//ショット処理
	for (int nBullet = 0; nBullet < MAX_BUCK_SHOT; nBullet++)
	{
		//弾丸を撃ちだすまでのカウント＆弾を撃ちだしたか
		if (m_nBullet == 2 * nBullet
			&& m_bBullet[nBullet] == false)
		{
			//向きをランダム
			Random(5.0f);
			//ランダムな向きを取得
			rot = GetRot();
			//バレット生成
			CEnemyBullet::Create(pos, rot);
			//バレット使用状態に
			m_bBullet[nBullet] = true;
		}
	}

	//終了
	if (m_bBullet[MAX_BUCK_SHOT -1] == true)
	{
		SetShotsEnd(true);
		return;
	}
}

