//=============================================================================
//
// エネミーベース処理 [enemy base.cpp]
// Author : 吉田悠人
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "enemy base.h"
#include "score.h"
#include "game.h"
#include "player.h"
#include "enemy type1.h"
#include "enemy type2.h"
#include "enemy type3.h"
#include "enemy type4.h"
#include "shots.h"
#include "spiral.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define PLAYER_HIT_DAMAGE (1)	//プレイヤーにぶつかった時のダメージ
//=============================================================================
// コンストラクト
//=============================================================================
CEnemyBase::CEnemyBase(int nPriorit)
{
	m_nInTime		= 0;
	m_nLife			= 0;
	m_Score			= 0;
	m_nCount		= 0;
	m_bAttack		= false;
	m_fRot			= 0.0f;
	m_Stats			= STATS_MODE_NORMAL;
	m_Shots			= BULLET_PATTERN_NONE;
	m_pShotsBase	= NULL;

	SetObjType(OBJ_TYPE_ENEMY);				//タイプ処理
}


//=============================================================================
// テクスチャロード処理
//=============================================================================
HRESULT CEnemyBase::Load(void)
{
	CEnemyType1::Load();
	CEnemyType2::Load();
	CEnemyType3::Load();
	CEnemyType4::Load();

	return S_OK;
}

//=============================================================================
// テクスチャ破棄処理
//=============================================================================
void CEnemyBase::Unload(void)
{
	CEnemyType1::Unload();
	CEnemyType2::Unload();
	CEnemyType3::Unload();
	CEnemyType4::Unload();
}


//=============================================================================
// 更新処理
//=============================================================================
void CEnemyBase::Update(void)
{
	CScene2d::Update();
	//カウントアップ
	m_nCount++;

	//当たり判定
	Hit();
	//移動処理
	Move();
	//ステータ管理
	StatasManage();
	//ショットの更新
	if (m_pShotsBase!=NULL)
	{
		m_pShotsBase->Update();
	}
}

//=============================================================================
// ダメージ処理
//=============================================================================
void CEnemyBase::Damage(int nDamage)
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
void CEnemyBase::StatasManage(void)
{
	switch (m_Stats)
	{
	case STATS_MODE_NORMAL:
		//ダメージカラー処理
		//SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		break;
	case STATS_MODE_DAMAGE:
		//ダメージカラー処理
		//SetCol(D3DXCOLOR(1.0f, 0.5f, 0.5f, 0.0f));

		m_Stats = STATS_MODE_NORMAL;

		break;
	case STATS_MODE_DEATH:
		//スコアポインタ取得
		CScore *pScore = CGame::GetScore();
		//スコア加算
		pScore->AddScore(m_Score);
		//終了
		CEnemyBase::Uninit();
		break;
	}

}

//=============================================================================
// 回転処理
//=============================================================================
void CEnemyBase::Rotate(void)
{
	
	//向きセット
	SetRot(m_fRot);
	//回転角度プラス
	m_fRot += 2.0f;
	//回転角度が一定に達したら
	if (m_fRot>360.0f)
	{
		//角度初期化
		m_fRot = 0;
	}

}

//=============================================================================
// ショット判定
//=============================================================================
void CEnemyBase::Bullet(void)
{
	//位置取得
	D3DXVECTOR3 pos = GetPos();
	
	//カウントが攻撃時間を過ぎると
	if (m_nCount>m_nAttackTime)
	{
		//攻撃をしているか
		if (!m_bAttack)
		{
			//攻撃のタイプ分け
			switch (m_Shots)
			{
			case BULLET_PATTERN_SHOTS:
				m_pShotsBase = CShots::Create(this);
				m_Shots = BULLET_PATTERN_NONE;
				break;
			case BULLET_PATTERN_SPIRAL:
				m_pShotsBase = CSpiral::Create(this);
				m_Shots = BULLET_PATTERN_NONE;
				break;
			}
			m_bAttack = true;
		}
	}

}

//=============================================================================
// 当たり判定
//=============================================================================
void CEnemyBase::Hit(void)
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
						((CPlayer*)pNext)->Damage(PLAYER_HIT_DAMAGE);
					}
				}
				//次のオブジェクトのポインタを更新
				pNext = pNext->GetNext();

			}
		}

	}

}

//=============================================================================
// 移動処理
//=============================================================================
void CEnemyBase::Move(void)
{
	//位置取得
	D3DXVECTOR3 pos = GetPos();
	//サイズ取得
	D3DXVECTOR3 size = GetSize();

	//移動位置
	//if (m_nMoveCount<m_nPointer+1)
	//{
	//	//目標の位置方向取得
	//	fAngle = atan2f((-pos.x + m_movePointer[m_nMoveCount].x), (-pos.y + m_movePointer[m_nMoveCount].y));
	//	//目標までの移動
	//	m_move.x = sinf(fAngle) * m_fSpeed[m_nMoveCount];
	//	m_move.y = cosf(fAngle) * m_fSpeed[m_nMoveCount];
	//	//位置更新
	//	pos += m_move;
	//	//位置設定
	//	SetPos(pos);
	//
	//	
	//	if (pos.x + 5.0f>m_movePointer[m_nMoveCount].x
	//		&&pos.x - 5.0f<m_movePointer[m_nMoveCount].x
	//		&&pos.y + 5.0f>m_movePointer[m_nMoveCount].y
	//		&&pos.y - 5.0f<m_movePointer[m_nMoveCount].y)
	//	{
	//		//次の位置
	//		m_nMoveCount++;
	//	}
	//}

	//出現時間を過ぎてから行動する
	if (m_nCount>m_nInTime)
	{
		//行動パターン
		switch (m_MovePattern)
		{
		case ENEMY_MOVE_RETURN:		//Uターン
			//カウントがアクションタイムを越していないとき
			if (m_nCount<m_nActionTime
				&&m_nCount < m_nOutTime)
			{
				//移動量セット
				pos += D3DXVECTOR3(0.0f, 1.0f, 0.0f)*m_fSpped;
			}
			//カウントが一定になったら
			if (m_nCount > m_nOutTime)
			{
				//移動量セット
				pos += D3DXVECTOR3(0.0f, -1.0f, 0.0f)*m_fSpped;
			}
			//位置セット
			SetPos(pos);
			break;

			
		case ENEMY_MOVE_STRAIGHT:	//直進
			//移動量セット
			pos += D3DXVECTOR3(0.0f, 1.0f, 0.0f)*m_fSpped;
			//位置セット
			SetPos(pos);
			break;

		case ENEMY_MOVE_RIGHT:		//右に曲がる
			//移動量セット
			pos += D3DXVECTOR3(0.0f, 1.0f, 0.0f)*m_fSpped;
			//カウントが一定に達したら
			if (m_nCount>m_nActionTime)
			{
				//移動量セット
				pos.x += 3.0;
			}
			//位置セット
			SetPos(pos);
			break;

		case ENEMY_MOVE_LEFT:		//左に曲がる
			//移動量セット
			pos += D3DXVECTOR3(0.0f, 1.0f, 0.0f)*m_fSpped;
			//カウントが一定に達したら
			if (m_nCount>m_nActionTime)
			{
				//移動量セット
				pos.x += -3.0;
			}
			//位置セット
			SetPos(pos);

			break;

		case ENEMY_MOVE_RIGHT_SLIDE://右に向かって横移動
			//移動量セット
			pos += D3DXVECTOR3(1.0f, 0.0f, 0.0f)*m_fSpped;
			//位置セット
			SetPos(pos);
			break;

		case ENEMY_MOVE_LEFT_SLIDE:	//左に向かって横移動
			//移動量セット
			pos += D3DXVECTOR3(-1.0f, 0.0f, 0.0f)*m_fSpped;
			//位置セット
			SetPos(pos);
			break;

		case ENEMY_MOVE_RIGHT_STOP:	//右に向かって横移動(途中で一度止まる)
			//カウントがアクションタイムを越していないとき
			if (m_nCount<m_nActionTime
				&&m_nCount < m_nOutTime)
			{
				//移動量セット
				pos += D3DXVECTOR3(1.0f, 0.0f, 0.0f)*m_fSpped;
			}
			//カウントが一定になったら
			if (m_nCount > m_nOutTime)
			{
				//移動量セット
				pos += D3DXVECTOR3(1.0f, 0.0f, 0.0f)*m_fSpped;
			}
			//位置セット
			SetPos(pos);
			break;
		
		case ENEMY_MOVE_LEFT_STOP:	//左に向かって横移動(途中で一度止まる)
			//カウントがアクションタイムを越していないとき
			if (m_nCount<m_nActionTime
				&&m_nCount < m_nOutTime)
			{
				//移動量セット
				pos += D3DXVECTOR3(-1.0f, 0.0f, 0.0f)*m_fSpped;
			}
			//カウントが一定になったら
			if (m_nCount > m_nOutTime)
			{
				//移動量セット
				pos += D3DXVECTOR3(-1.0f, 0.0f, 0.0f)*m_fSpped;
			}
			//位置セット
			SetPos(pos);
			break;
		}
	}

	//画面外処理
	if (pos.y > SCREEN_HEIGHT + (size.y / 2)					// 画面下
		|| pos.y< 0 - (size.y / 2)								// 画面上
		|| pos.x >(STAGE_POS + STAGE_SIZE / 2) + (size.x / 2)	// 画面右
		|| pos.x < (STAGE_POS - STAGE_SIZE / 2) - (size.x / 2))	// 画面左
	{
		//アクションカウントが0になっていたら
		if (m_nCount >= m_nActionTime)
		{
			//終了
			CEnemyBase::Uninit();

		}
	}

}

//=============================================================================
// 行動パターンセッター
//=============================================================================
void CEnemyBase::SetMovePattern(ENEMY_MOVE_PATTERN MovePattern)
{
	m_MovePattern =	MovePattern;
}

//=============================================================================
// 攻撃パターンセッター
//=============================================================================
void CEnemyBase::SetAttackPattern(ENEMY_ATTACK_PATTERN AttackPaattern)
{
	m_Shots = AttackPaattern;
}

//=============================================================================
// 出現時間セッター
//=============================================================================
void CEnemyBase::SetInTime(int nInTime)
{
	m_nInTime = nInTime;
}

//=============================================================================
// 行動時間セッター
//=============================================================================
void CEnemyBase::SetActionTime(int nActionTime)
{
	m_nActionTime = nActionTime;
}

//=============================================================================
// 攻撃時間セッター
//=============================================================================
void CEnemyBase::SetAttackTime(int nAttackTime)
{
	m_nAttackTime = nAttackTime;
}

//=============================================================================
// 帰還時間セッター
//=============================================================================
void CEnemyBase::SetOutTime(int nOutTime)
{
	m_nOutTime = nOutTime;
}

//=============================================================================
// ライフセッター
//=============================================================================
void CEnemyBase::SetLife(int nLife)
{
	m_nLife = nLife;
}

//=============================================================================
// ライフセッター
//=============================================================================
int CEnemyBase::GetLife(void)
{
	return m_nLife;
}

//=============================================================================
// スコアセッター
//=============================================================================
void CEnemyBase::SetScore(int nScore)
{
	m_Score = nScore;
}

//=============================================================================
// スコアゲッター
//=============================================================================
int CEnemyBase::GetScore(void)
{
	return m_Score;
}

//=============================================================================
// スピードセッター
//=============================================================================
void CEnemyBase::SetSpeed(float nSpeed)
{
	m_fSpped = nSpeed;
}

//=============================================================================
// スピードゲッター
//=============================================================================
float CEnemyBase::GetSpeed(void)
{
	return m_fSpped;
}

