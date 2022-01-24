//=============================================================================
//
// ボスベース処理 [boss base.cpp]
// Author : 吉田悠人
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "boss base.h"
#include "score.h"
#include "game.h"
#include "player.h"
#include "shots base.h"
#include "shots.h"
#include "spiral.h"
#include "buckshot.h"
#include "full range shots.h"
#include "split shots.h"
#include "boss type1.h"
#include "boss type2.h"
#include "boss type3.h"

#include <time.h>


//=============================================================================
// コンストラクト
//=============================================================================
CBossBase::CBossBase(int nPriorit)
{
	m_nLife				= 0;
	m_Score				= 0;
	m_nCoolTime			= 0;
	m_nLimitCoolTime	= 0;
	m_pShots			= NULL;
	m_Stats				= STATS_MODE_NORMAL;
	m_Shots				= BOSS_PATTERN_NONE;
	SetObjType(OBJ_TYPE_BOSS);				//タイプ処理
}

//=============================================================================
// テクスチャロード処理
//=============================================================================
HRESULT CBossBase::Load(void)
{
	CBossType1::Load();
	CBossType2::Load();
	CBossType3::Load();
	return S_OK;
}

//=============================================================================
// テクスチャ破棄処理
//=============================================================================
void CBossBase::Unload(void)
{
	CBossType1::Unload();
	CBossType2::Unload();
	CBossType3::Unload();
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CBossBase::Init(void)
{
	//エフェクト生成
	Effect();
	//初期化処理
	CScene2d::Init();
	return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void CBossBase::Update(void)
{
	CScene2d::Update();
	//当たり判定
	Hit();

	//ショットの更新
	if (m_pShots != NULL)
	{
		m_pShots->Update();
	}

	//ステータ管理
	StatasManage();
}

//=============================================================================
// ダメージ処理
//=============================================================================
void CBossBase::Damage(int nDamage)
{
	//状態確認
	if (m_Stats == STATS_MODE_NORMAL)
	{
		//ライフダメージ
		m_nLife -= nDamage;

		//ライフが0なら
		if (m_nLife > 0)
		{
			//死亡状態に移行
			m_Stats = STATS_MODE_DAMAGE;
			return;
		}
		//ダメージ状態に移行
		m_Stats = STATS_MODE_DEATH;
	}

}

//=============================================================================
// エネミーの状態管理処理
//=============================================================================
void CBossBase::StatasManage(void)
{

	switch (m_Stats)
	{
	case STATS_MODE_NORMAL:
		//ダメージカラー処理
		SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		break;
	case STATS_MODE_DAMAGE:
		//ダメージカラー処理
		SetCol(D3DXCOLOR(1.0f, 0.5f, 0.5f, 0.0f));
		//ステータセット
		m_Stats = STATS_MODE_NORMAL;
		break;
	case STATS_MODE_DEATH:
		//スコアポインタ取得
		CScore *pScore = CGame::GetScore();
		//スコア加算
		pScore->AddScore(m_Score);
		//死亡エフェクト生成
		DisEffect();
	
		//終了
		CBossBase::Uninit();
		break;
	}

}

//=============================================================================
// ショット判定
//=============================================================================
void CBossBase::Bullet(void)
{
	//位置取得
	D3DXVECTOR3 pos = GetPos();
	
	//攻撃パターン
	switch (m_Shots)
	{
	case BOSS_PATTERN_NONE:


		//クールタイム処理
		if (CoolTime())
		{	
			//ランダム関数の初期化
			srand((unsigned)time(NULL));
			if (m_pShots == NULL)
			{
				//ランダムに次の行動を決める
				m_Shots = (BOSS_PATTERN)(rand() % BOSS_PATTERN_SPIRAL + BOSS_PATTERN_SHOTS);
			}
		}
		
		break;
	case  BOSS_PATTERN_SHOTS:
		m_pShots = CShots::Create(this);
		m_Shots = BOSS_PATTERN_NONE;
		break;
	case BOSS_PATTERN_All_DIR:
		m_pShots = CFullRange::Create(pos);
		m_Shots = BOSS_PATTERN_NONE;
		break;
	case BOSS_PATTERN_BUCKSHOT:
		m_pShots= CBuckShot::Create(pos);
		m_Shots = BOSS_PATTERN_NONE;
		break;

	case  BOSS_PATTERN_SPLIT:
		m_pShots = CSplitShots::Create(pos);
		m_Shots = BOSS_PATTERN_NONE;
		break;

	case  BOSS_PATTERN_SPIRAL:
		m_pShots = CSpiral::Create(this);
		m_Shots = BOSS_PATTERN_NONE;
		break;
	}
}

//=============================================================================
// 攻撃時のクールタイム
//=============================================================================
bool CBossBase::CoolTime(void)
{

	if (m_pShots!=NULL)
	{
		//攻撃が終わっていたら
		if (m_pShots->GetShotsEnd())
		{
			m_pShots = NULL;
		}
	}
	//NULLであれば
	else
	{
		//クールタイム加算
		m_nCoolTime++;
	}

	//クールタイムが一定に達したら
	if (m_nCoolTime>= m_nLimitCoolTime)
	{
		//クールタイムの初期化
		m_nCoolTime = 0;
		return true;
	}
	return false;
}


//=============================================================================
// 当たり判定
//=============================================================================
void CBossBase::Hit(void)
{
	//オブジェクト取得用
	CScene* pTop[PRIORITY_MAX] = {};
	//次チェックするオブジェクトのポインタ
	CScene* pNext = NULL;
	//位置取得
	D3DXVECTOR3 pos = GetPos();
	//サイズ取得
	D3DXVECTOR3 size = GetSize();

	//topのアドレスを取得
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		pTop[nCount] = *(CScene::GetTop() + nCount);
	}

	//プレイヤーとの当たり判定
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		if (pTop[nCount] != NULL)
		{
			pNext = pTop[nCount];
			//その描画優先度のオブジェクトがなくなるまでループ
			while (pNext != NULL)
			{
				//オブジェクトのタイプがプレイヤーなら
				if (pNext->GetObjType() == OBJ_TYPE_PLAYER)
				{
					D3DXVECTOR3 Playerpos = ((CScene2d*)pNext)->GetPos();
					//当たり判定
					if (Playerpos.x > pos.x - size.x / 2
						&& Playerpos.x  < pos.x + size.x / 2
						&& Playerpos.y > pos.y - size.y / 2
						&& Playerpos.y < pos.y + size.y / 2)
					{
						((CPlayer*)pNext)->Damage(1);
					}
				}
				//次のオブジェクトのポインタを更新
				pNext = pNext->GetNext();

			}
		}

	}

}

//=============================================================================
// クールタイムセッター
//=============================================================================
void CBossBase::SetCoolTime(int nCoolTime)
{
	m_nLimitCoolTime = nCoolTime;
}

//=============================================================================
// クールタイムゲッター
//=============================================================================
int CBossBase::GetCoolTime(void)
{
	return m_nLimitCoolTime;
}

//=============================================================================
// ライフセッター
//=============================================================================
void CBossBase::SetLife(int nLife)
{
	m_nLife = nLife;
}

//=============================================================================
// ライフセッター
//=============================================================================
int CBossBase::GetLife(void)
{
	return m_nLife;
}

//=============================================================================
// スコアセッター
//=============================================================================
void CBossBase::SetScore(int nScore)
{
	m_Score = nScore;
}

//=============================================================================
// スコアゲッター
//=============================================================================
int CBossBase::GetScore(void)
{
	return m_Score;
}

//=============================================================================
// 攻撃パターンセッター
//=============================================================================
void CBossBase::SetPattern(BOSS_PATTERN type)
{
	m_Shots = type;
}

//=============================================================================
// 攻撃パターンゲッター
//=============================================================================
BOSS_PATTERN CBossBase::GetPattern(void)
{
	return m_Shots;
}
