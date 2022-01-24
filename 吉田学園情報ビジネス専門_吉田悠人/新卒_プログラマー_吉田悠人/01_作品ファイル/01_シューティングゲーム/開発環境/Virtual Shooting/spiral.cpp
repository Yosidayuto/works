//=============================================================================
//
// ショット(円状)処理 [spira.cpp]
// Author : 吉田悠人
//
//=============================================================================
//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "shots base.h"
#include "scene.h"
#include "scene2d.h"
#include "spiral.h"
#include "enemy bullet.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define SPIRAL_SPEED			(7.0f)		//弾速

//=============================================================================
// コンストラクト
//=============================================================================
CSpiral::CSpiral()
{
	m_nBullet = 0;
	memset(m_bBullet, false, sizeof(m_bBullet));
}

//=============================================================================
// 生成処理
//=============================================================================
CSpiral * CSpiral::Create(CScene2d* Scene2d)
{
	//メモリの確保
	CSpiral* pSpiral = NULL;
	pSpiral = new CSpiral;
	
	//NULLチェック
	if (pSpiral != NULL)
	{
		pSpiral->m_pScene2d = Scene2d;
		//位置設定
		pSpiral->SetPos(Scene2d->GetPos());
		//向き設定
		pSpiral->Tracking(SPIRAL_SPEED);
	}

	return pSpiral;
}

//=============================================================================
// ショット処理
//=============================================================================
void CSpiral::Shots(void)
{
	//位置取得
	D3DXVECTOR3 pos = GetPos();
	//向き取得
	D3DXVECTOR3 rot = GetRot();

	//カウントプラス
	m_nBullet++;

	//ショット処理
	for (int nBullet = 0; nBullet < MAX_SPIRAL; nBullet++)
	{
		//弾丸を撃ちだすまでのカウント＆弾を撃ちだしたか
		if (m_nBullet == nBullet)
		{
			rot.x = sinf((0.2f*nBullet))*7.0f;
			rot.y = cosf((0.2f*nBullet))*7.0f;

			//バレット生成
			CEnemyBullet::Create(pos, rot);
			//バレット使用状態に
			m_bBullet[nBullet] = true;
		}
	}

	//終了
	if (m_bBullet[MAX_SPIRAL-1] == true)
	{
		SetShotsEnd(true);
		return;
	}
}

