//=============================================================================
//
// ゴール処理 [trap.cpp]
// Author : 吉田悠人
//
//=============================================================================


//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "goal.h"
#include "explosion.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "fade.h"
#include "sound.h"

//*****************************************************************************
//　静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CGoal::CGoal()
{
	m_GameMode = {};
	m_pTexture = NULL;
	SetObjType(OBJTYPE_NONE);
}


//=============================================================================
// 生成関数
// CManager::MODE Mode（次のステージ設定）
//=============================================================================
CGoal * CGoal::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, CManager::MODE Mode)
{
	//メモリ確保
	CGoal* pGoal = NULL;
	pGoal = new CGoal;

	//メモリが確保されているか
	if (pGoal!=NULL)
	{
		//位置設定
		pGoal->SetPosition(pos);
		//向き設定
		pGoal->SetRotation(rot);
		//サイズ設定
		pGoal->SetSize(size);
		//ゴールした際の次のマップ
		pGoal->m_GameMode = Mode;

		//色設定
		for (int nMesh = 0; nMesh < MESH_Y_BLOCK + 1; nMesh++)
		{
			pGoal->SetColor(D3DXCOLOR(col.r, col.g, col.b, nMesh*0.1f), nMesh);
		}

		//初期化処理
		pGoal->Init();
	}
	return pGoal;
}



//=============================================================================
// 更新関数
//=============================================================================
void CGoal::Update(void)
{
	//メッシュのカラー変更
	CMeshCylinder::ColorAnimation();
	//ゴール判定
	HitGoal();
	//メッシュのアップデート
	CMeshCylinder::Update();
}

//=============================================================================
// ゴール判定関数
//=============================================================================
void CGoal::HitGoal(void)
{
	//プレイヤーの位置取得
	D3DXVECTOR3 Playerpos = CManager::GetPlayer()->GetPos();

	//当たり判定
	if (GetPos().x+(GetSize().x/2)>Playerpos.x
		&&GetPos().x - (GetSize().x / 2)<Playerpos.x
		&&GetPos().z + (GetSize().z / 2)> Playerpos.z
		&&GetPos().z - (GetSize().z / 2)< Playerpos.z)
	{
		//サウンドの取得
		CSound * pSound = CManager::GetSound();
		pSound->StopSound();

		//次のステージ遷移
		CManager::GetFade()->SetFade(m_GameMode);
		Uninit();
	}
}

