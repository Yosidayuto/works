//=============================================================================
//
//	プレイヤー[player.cpp]
//	Author:吉田悠人
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "player.h"
#include "renderer.h"
#include "resource manager.h"
#include "keyboard.h"
#include "mouse.h"
#include "joystick.h"
#include "player parts.h"
#include "ebi parts.h"
#include "egg parts.h"
#include "ikura parts.h"
#include "salmon parts.h"
#include "tuna parts.h"
#include "food base.h"
#include "ebi.h"
#include "egg.h"
#include "ikura.h"
#include "salmon.h"
#include "tuna.h"
#include "ShieldEffect.h"
#include "sound.h"
#include "effect powerup.h"
#include "game.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define PLAYER_SPEED		(1.0f)	// プレイヤーのスピード(後で変更)
#define PLAYER_BOOST_SPEED	(2.0f)	// プレイヤーのブーストスピード(後で変更)
#define PLAYER_ROT_SPEED	(10.0f)	// プレイヤーの振り向き速度(後で変更)
#define PLAYER_REPEL		(15.0f)	// プレイヤーがはじかれる距離
#define PLAYER_REPEL_FRAME	(10.0f)	// プレイヤーのはじかれた際のフレーム
#define PLAYER_INVINCIBLE	(30*3)	// プレイヤーの無敵時間
#define PLAYER_DASH_DEMERIT	(30*2)	// プレイヤーのダッシュ時のデメリットカウント
#define ITEM_EFFECT_COUNT	(150)	// アイテムの効果時間


//=============================================================================
// コンストラクタ
//=============================================================================
CPlayer::CPlayer(int nPriority)
{
	SetObjType(OBJTYPE_PLAYER);								// オブジェクトタイプ設定
	m_nLife				 = 0;								// ライフの初期化
	m_nRepelFrameCount	 = 0;								// はじかれた際のフレーム値の初期化
	m_nFlashing			 = 0;								// 死亡時のカウントフレーム値　の初期化
	m_nInvinciFrameCount = 0;								// 無敵状態のフレームカウントの初期化
	m_MaxInvinciCount	 = 0;								// 無敵状態の最大数の初期化
	m_fDashDemeritCoutn	 = PLAYER_DASH_DEMERIT;				// 加速時のデメリットカウントの初期化
	m_fDashCoutn	= 0;									// 加速値の初期化
	m_nParts		= 0;									// パーツ数の初期化
	m_nItemCount	= ITEM_EFFECT_COUNT;					// スコアアップ状態の時間
	m_PlayerStats	= PLAYER_STATS_NORMAL;					// プレイヤーステータスの初期化
	m_bInvincible	= false;								// 無敵状態の初期化
	m_bDashSwitch	= false;								// ダッシュ切替の初期化
	m_bShield		= false;								// アイテムシールドスイッチの初期化
	m_bScoreUp		= false;					// アイテムスコアアップの初期化
	m_RotMove		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 向きの移動量の初期化
	m_RepelMove		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// はじかれた際の移動量の初期化

	for (int nParts = 0; nParts < MAX_PARTS; nParts++)
	{
		m_pParts[nParts] = nullptr;
	}
}
//=============================================================================
// デストラクタ
//=============================================================================
CPlayer::~CPlayer()
{

}

//=============================================================================
// 生成処理関数
//=============================================================================
CPlayer * CPlayer::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, D3DXVECTOR3 Size, int nModel)
{
	//メモリ確保
	CPlayer* pPlayer = NULL;
	pPlayer = new CPlayer;
	//リソース確保
	CResource* pResource = CManager::GetResource();
	MODELDATA Model = pResource->ModelLoad(nModel);

	//NULLチェック
	if (pPlayer != NULL)
	{
		//位置設定
		pPlayer->SetPos(Pos);
		//向き設定
		pPlayer->SetRot(Rot);
		//カラー設定
		pPlayer->SetSize(Size);
		//モデルデータ設定
		pPlayer->SetModelData(Model);
		//初期化処理
		pPlayer->Init();
	}

	return pPlayer;
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CPlayer::Update(void)
{
	//状態によって処理の変更
	switch (m_PlayerStats)
	{

	case PLAYER_STATS_NORMAL:	//通常状態の場合
		//移動処理
		Move();
		//角度処理
		Rot();
		//ダッシュ時のデメリット処理
		DashDemerit();
		break;

	case PLAYER_STATS_REPEL:	//はじかれている場合
		RepelMove();
		break;

	case PLAYER_STATS_RESPAWN:	// リスポーン状態
		RespawnStats();
		break;

	case PLAYER_STATS_DEATH:	//死亡している場合
		Death();
		break;
	}
	// 無敵時間処理関数
	Invincible();
	
	//スコアアップのアイテムを拾ったら
	if (m_bScoreUp == true)
	{
		// スコアアップの制限時間処理
		ScoreUpCount();
	}
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CPlayer::Draw(void)
{
	//レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	//デバイスにレンダラーのデバイスを代入
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//アルファテストを有効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//アルファテスト基準値の設定
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	//アルファテストの比較方法の設定
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//描画処理
	CModel::Draw();

	//アルファテストを無効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=============================================================================
// 移動処理関数
//=============================================================================
void CPlayer::Move(void)
{
	//位置取得
	D3DXVECTOR3 pos = GetPos();
	//向き取得
	D3DXVECTOR3 rot = GetRot();
	//移動量
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//移動処理
	move = D3DXVECTOR3((float)(cos(rot.y + D3DXToRadian(90.0f))), 0.0f, (float)(sin(rot.y - D3DXToRadian(90.0f))));

	if (!m_bDashSwitch)
	{
		if (m_fDashCoutn <= PLAYER_SPEED)
		{
			m_fDashCoutn = m_fDashCoutn + 0.1f;
		}
		else if (m_fDashCoutn > PLAYER_SPEED)
		{
			m_fDashCoutn = m_fDashCoutn - 0.1f;

		}
	}
	else
	{
		if (m_fDashCoutn <= PLAYER_BOOST_SPEED)
		{
			m_fDashCoutn = m_fDashCoutn + 0.1f;
		}
		else if (m_fDashCoutn > PLAYER_BOOST_SPEED)
		{
			m_fDashCoutn = m_fDashCoutn - 0.1f;
		}
	}
	//スピードを計算
	move *= m_fDashCoutn;
	// 移動処理
	pos += move;

	// 位置保存
	SetPos(pos);

}

//=============================================================================
// 向き処理関数
//=============================================================================
void CPlayer::Rot(void)
{
	//角度の移動量
	float fRotMove = 0.0f;
	//位置取得
	D3DXVECTOR3 pos = GetPos();
	//向き取得
	D3DXVECTOR3 rot = GetRot();
	//向きたい角度
	fRotMove = atan2f((pos.x - (m_RotMove.x + pos.x)), (pos.z - (m_RotMove.z + pos.z)));
	//差分の角度
	float fDiff = ((D3DXToRadian(180.0f) - (fRotMove*-1.0f)) - (D3DXToRadian(180.0f) - (rot.y*-1.0f)))*-1.0f;
	//回転方向の確認(時計周りtrue:反時計回りfalse)
	bool bRotation = fRotMove>rot.y ? !(fRotMove - rot.y > D3DXToRadian(180.0f)) : rot.y - fRotMove  > D3DXToRadian(180.0f);
	//向きの修正
	fDiff = (fDiff + (bRotation ? D3DXToRadian(-360.0f) : D3DXToRadian(360.0f)));
	fDiff = (float)(fmod(fDiff, D3DXToRadian(360.0f)));
	//向き処理
	rot.y = rot.y - (fDiff*(0.04f));
	//角度が一定に達したら修正
	if (D3DXToDegree(rot.y) >= 360.0f
		|| D3DXToDegree(rot.y) <= -360.0f)
	{
		rot.y = 0.0f;
	}
	// 向き保存
	SetRot(rot);
}

//=============================================================================
// はじかれた際の移動処理関数
//=============================================================================
void CPlayer::RepelMove(void)
{
	//位置取得
	D3DXVECTOR3 pos = GetPos();

	//移動処理
	pos = pos + (m_RepelMove - pos) / (PLAYER_REPEL_FRAME - m_nRepelFrameCount);
	//位置セット
	SetPos(pos);
	//フレーム加算
	m_nRepelFrameCount++;

	if (m_nRepelFrameCount >= PLAYER_REPEL_FRAME)
	{
		//カウント初期化
		m_nRepelFrameCount = 0;
		//ステータスを変更
		SetStats(PLAYER_STATS_NORMAL);
	}
}

//=============================================================================
// はじかれる処理関数
//=============================================================================
void CPlayer::Repel(CScene3d* Player)
{
	//プレイヤーの状態が通常の場合＆無敵状態出ないとき
	if (m_PlayerStats == PLAYER_STATS_NORMAL
		&&m_bInvincible == false)
	{
		//現在位置
		D3DXVECTOR3 pos = GetPos();
		//相手の位置
		D3DXVECTOR3 PlayerPos = Player->GetPos();
		//当たった方向
		D3DXVECTOR3 HItPint = D3DXVECTOR3(0.0f, atan2f((PlayerPos.x - pos.x), (PlayerPos.z - pos.z)), 0.0f);;
		//法線ベクトルの計算
		D3DXVECTOR3 Normal = PlayerPos - pos;
		//移動処理
		D3DXVECTOR3 move = D3DXVECTOR3((float)(cos(HItPint.y + D3DXToRadian(90.0f))), 0.0f, (float)(sin(HItPint.y - D3DXToRadian(90.0f))));

		//移動量
		D3DXVec3Normalize(&Normal, &Normal);
		//移動量の計算
		D3DXVec3Normalize(&m_RepelMove, &(move - 2.0f * D3DXVec3Dot(&move, &Normal) * Normal));
		m_RepelMove = (-m_RepelMove*PLAYER_REPEL) + pos;
		//加速値の初期化
		m_fDashCoutn = 0.0f;
		//一定時間無敵にする
		SwitchedInvincible(PLAYER_INVINCIBLE);

		//シールドアイテムを持っているか
		//持っていない場合
		if (m_bShield == false)
		{
			//はじかれ状態に変化
			SetStats(PLAYER_STATS_REPEL);
		}
		//持っていた場合
		else
		{
			//アイテムを消費して防ぐ
			m_bShield = false;
		}
	}
}

//=============================================================================
// パーツ追加（食べ物を食べた後の追加パーツ）処理関数
//=============================================================================
void CPlayer::AddParts(CFoodBase::FOOD_TYPE FoodType)
{
	if (m_PlayerStats != PLAYER_STATS_DEATH|| m_PlayerStats != PLAYER_STATS_RESPAWN)
	{
		//パーツがない時
		if (m_nParts == 0)
		{
			//位置取得
			D3DXVECTOR3 pos = GetPos();
			//向き取得
			D3DXVECTOR3 rot = GetRot();
			//生成処理
			switch (FoodType)
			{
			case CFoodBase::TYPE_EBI:
				m_pParts[m_nParts] = CEbiParts::Create(pos, rot, D3DXVECTOR3(10.0f, 10.0f, 10.0f), this);
				break;
			case CFoodBase::TYPE_EGG:
				m_pParts[m_nParts] = CEggParts::Create(pos, rot, D3DXVECTOR3(10.0f, 10.0f, 10.0f), this);
				break;
			case CFoodBase::TYPE_IKURA:
				m_pParts[m_nParts] = CIkuraParts::Create(pos, rot, D3DXVECTOR3(10.0f, 10.0f, 10.0f), this);
				break;
			case CFoodBase::TYPE_SALMON:
				m_pParts[m_nParts] = CSalmonParts::Create(pos, rot, D3DXVECTOR3(10.0f, 10.0f, 10.0f), this);
				break;
			case CFoodBase::TYPE_TUNA:
				m_pParts[m_nParts] = CTunaParts::Create(pos, rot, D3DXVECTOR3(10.0f, 10.0f, 10.0f), this);
				break;
			}
		}
		//パーツが１つでもある時
		else if (m_nParts>0 && m_nParts<MAX_PARTS)
		{
			//位置取得
			D3DXVECTOR3 PartsPos = m_pParts[m_nParts - 1]->GetPos();
			//向き取得
			D3DXVECTOR3 PartsRot = m_pParts[m_nParts - 1]->GetRot();
			//生成処理
			switch (FoodType)
			{
			case CFoodBase::TYPE_EBI:
				m_pParts[m_nParts] = CEbiParts::Create(m_pParts[m_nParts - 1]->GetPos(), PartsRot, D3DXVECTOR3(10.0f, 10.0f, 10.0f), m_pParts[m_nParts - 1]);
				break;
			case CFoodBase::TYPE_EGG:
				m_pParts[m_nParts] = CEggParts::Create(m_pParts[m_nParts - 1]->GetPos(), PartsRot, D3DXVECTOR3(10.0f, 10.0f, 10.0f), m_pParts[m_nParts - 1]);
				break;
			case CFoodBase::TYPE_IKURA:
				m_pParts[m_nParts] = CIkuraParts::Create(m_pParts[m_nParts - 1]->GetPos(), PartsRot, D3DXVECTOR3(10.0f, 10.0f, 10.0f), m_pParts[m_nParts - 1]);
				break;
			case CFoodBase::TYPE_SALMON:
				m_pParts[m_nParts] = CSalmonParts::Create(m_pParts[m_nParts - 1]->GetPos(), PartsRot, D3DXVECTOR3(10.0f, 10.0f, 10.0f), m_pParts[m_nParts - 1]);
				break;
			case CFoodBase::TYPE_TUNA:
				m_pParts[m_nParts] = CTunaParts::Create(m_pParts[m_nParts - 1]->GetPos(), PartsRot, D3DXVECTOR3(10.0f, 10.0f, 10.0f), m_pParts[m_nParts - 1]);
				break;
			}
		}

		//パーツ数を増やす
		m_nParts++;

	}
}

//=============================================================================
// コントローラー操作処理関数
//=============================================================================
void CPlayer::RotControl(D3DXVECTOR3 Control)
{
	//スティックに触れているかの確認（Controlのｘとｙがどちらも0.0fの場合触れていない）
	bool TouchStick = Control.x == 0.0f&&Control.y == 0.0f ? true : false;
	
	//スティックに触れている場合の処理
	if(TouchStick!= true)
	{
		//単位ベクトル取得
		D3DXVec3Normalize(&m_RotMove, &D3DXVECTOR3(Control.x, 0.0f, Control.y));
	}
}

//=============================================================================
// ダッシュ状態に移行
//=============================================================================
void CPlayer::Dash(bool bDash)
{
	m_bDashSwitch = bDash;
}

//=============================================================================
// プレイヤーがダメージを受けるモノにぶつかった際の処理関数
//=============================================================================
void CPlayer::DamageHit(void)
{
	if (m_PlayerStats == PLAYER_STATS_NORMAL)
	{
		//シールドアイテムを持っていなかった場合
		if (m_bShield == false)
		{
			if (m_bInvincible == false)
			{
				//状態をリスポーン状態に変更
				SetStats(PLAYER_STATS_RESPAWN);

				//死亡音
				CSound *pSound = CManager::GetSound();
				pSound->PlaySound(CSound::LABEL_SE_DEATH);

				//持っている寿司をばら撒く
				for (int nParts = 0; nParts < m_nParts; nParts++)
				{
					if (m_pParts[nParts] != nullptr)
					{
						//パーツの位置取得
						D3DXVECTOR3 PartsPos = m_pParts[nParts]->GetPos();
						switch (m_pParts[nParts]->GetType())
						{
						case CFoodBase::TYPE_EBI:
							CEbi::Create(PartsPos, D3DXVECTOR3(10.0f, 10.0f, 10.0f));
							break;
						case CFoodBase::TYPE_EGG:
							CEgg::Create(PartsPos, D3DXVECTOR3(10.0f, 10.0f, 10.0f));
							break;
						case CFoodBase::TYPE_IKURA:
							CIkura::Create(PartsPos, D3DXVECTOR3(10.0f, 10.0f, 10.0f));
							break;
						case CFoodBase::TYPE_SALMON:
							CSalmon::Create(PartsPos, D3DXVECTOR3(10.0f, 10.0f, 10.0f));
							break;
						case CFoodBase::TYPE_TUNA:
							CTuna::Create(PartsPos, D3DXVECTOR3(10.0f, 10.0f, 10.0f));
							break;
						}
						m_pParts[nParts]->Uninit();
						m_pParts[nParts] = nullptr;
					}
				}
				m_nParts = 0;
			}
		}
		//持っていた場合
		else
		{
			//アイテムを消費
			m_bShield = false;
			//一定時間無敵にする
			m_bInvincible = true;
			//ヒット音
			CSound *pSound = CManager::GetSound();
			pSound->PlaySound(CSound::LABEL_SE_HITPLAYER);
		}
	}
}

//=============================================================================
// マップ端でのダメージヒット処理
//=============================================================================
void CPlayer::BarrierHit(void)
{
	if (m_PlayerStats == PLAYER_STATS_NORMAL)
	{
		//状態をリスポーン状態に変更
		SetStats(PLAYER_STATS_RESPAWN);

		//死亡音
		CSound *pSound = CManager::GetSound();
		pSound->PlaySound(CSound::LABEL_SE_DEATH);

		//持っている寿司をばら撒く
		for (int nParts = 0; nParts < m_nParts; nParts++)
		{
			if (m_pParts[nParts] != nullptr)
			{
				//パーツの位置取得
				D3DXVECTOR3 PartsPos = m_pParts[nParts]->GetPos();
				switch (m_pParts[nParts]->GetType())
				{
				case CFoodBase::TYPE_EBI:
					CEbi::Create(PartsPos, D3DXVECTOR3(10.0f, 10.0f, 10.0f));
					break;
				case CFoodBase::TYPE_EGG:
					CEgg::Create(PartsPos, D3DXVECTOR3(10.0f, 10.0f, 10.0f));
					break;
				case CFoodBase::TYPE_IKURA:
					CIkura::Create(PartsPos, D3DXVECTOR3(10.0f, 10.0f, 10.0f));
					break;
				case CFoodBase::TYPE_SALMON:
					CSalmon::Create(PartsPos, D3DXVECTOR3(10.0f, 10.0f, 10.0f));
					break;
				case CFoodBase::TYPE_TUNA:
					CTuna::Create(PartsPos, D3DXVECTOR3(10.0f, 10.0f, 10.0f));
					break;
				}

				m_pParts[nParts]->Uninit();
				m_pParts[nParts] = nullptr;
			}
		}
		m_nParts = 0;
	}
}

//=============================================================================
// リスポーン処理
//=============================================================================
void CPlayer::Respawn(D3DXVECTOR3 RespawnPos)
{
	if (m_PlayerStats == PLAYER_STATS_RESPAWN)
	{
		//リスポーン位置
		SetPos(RespawnPos);
		//ステータス設定
		SetStats(PLAYER_STATS_NORMAL);
		//リスポーン時に一定時間無敵にする
		SwitchedInvincible(PLAYER_INVINCIBLE);
		//アイテムの効果を切る
		m_bShield = false;
		m_bScoreUp = false;
		//アルファ値を初期化
		SetAlphaValue(1.0f);
	}
}

//=============================================================================
// シールド取得処理
//=============================================================================
void CPlayer::ShieldGet(void)
{
	//アイテムを持っているか
	if (m_bShield == false)
	{
		//ヒット音
		CSound *pSound = CManager::GetSound();
		pSound->PlaySound(CSound::LABEL_SE_GETITEM);

		//取得状態のためtrueに変更
		m_bShield = true;
		//見た目に変化？
		D3DXVECTOR3 pos = GetPos();
		CShieldEffect::Create(D3DXVECTOR3(pos.x, pos.y + 13.0f ,pos.z), D3DXVECTOR3(30.0f, 30.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 125),this);
	}
}

//=============================================================================
// スコアアップ取得処理
//=============================================================================
void CPlayer::ScoreUpGet(void)
{
	//アイテムを持っているか
	if (m_bScoreUp == false)
	{
		//ヒット音
		CSound *pSound = CManager::GetSound();
		pSound->PlaySound(CSound::LABEL_SE_GETITEM);

		//取得状態のためtrueに変更
		m_bScoreUp = true;
		//見た目に変化？
		D3DXVECTOR3 pos = GetPos();
		CEffectPowerUP::Create(pos, D3DXVECTOR3(30.0f, 30.0f, 0.0f), this);
	}
}

//=============================================================================
//スコアアップ状態の時間
//=============================================================================
void CPlayer::ScoreUpCount(void)
{
	//カウントを減らす
	m_nItemCount--;

	if (m_nItemCount <= 0)
	{
		//状態を元に戻す
		m_bScoreUp = false;
		//数値を元に戻す
		m_nItemCount = ITEM_EFFECT_COUNT;
	}

}

//=============================================================================
// 死亡処理関数
//=============================================================================
void CPlayer::Death(void)
{
	SetAlphaValue(0.0f);
}

//=============================================================================
// 無敵時間処理関数
//=============================================================================
void CPlayer::Invincible(void)
{
	//無敵スイッチがtrueの場合
	if (m_bInvincible == true)
	{
		//点滅処理
		Flashing();
		//カウントダウン
		m_nInvinciFrameCount++;
		//カウントが一定に達したら
		if (m_nInvinciFrameCount >= PLAYER_INVINCIBLE)
		{
			//カウントの初期化
			m_nInvinciFrameCount = 0;
			//無敵スイッチをfalseにする
			m_bInvincible = false;
			//点滅ストップ
			FlashingStop();
			return;
		}
	}
}

//=============================================================================
// 無敵スイッチオン処理関数
//=============================================================================
void CPlayer::SwitchedInvincible(int nInvincible)
{
	// 無敵かどうか
	if (!m_bInvincible)
	{
		//カウントの最大数を書き込む
		m_MaxInvinciCount = nInvincible;
		//無敵スイッチオン
		m_bInvincible = true;
	}
}

//=============================================================================
// リスポーン状態時処理
//=============================================================================
void CPlayer::RespawnStats(void)
{
	SetAlphaValue(0.0f);
}

//=============================================================================
// ダッシュ時のデメリット処理関数
//=============================================================================
void CPlayer::DashDemerit(void)
{
	//ダッシュ状態チェック
	if (m_bDashSwitch)
	{
		//カウントダウン
		m_fDashDemeritCoutn--;

		//餌を落とす
		if (m_fDashDemeritCoutn == 0)
		{
			if (m_pParts[m_nParts - 1] != nullptr)
			{
				//パーツの位置取得
				D3DXVECTOR3 PartsPos = m_pParts[m_nParts - 1]->GetPos();
				switch (m_pParts[m_nParts - 1]->GetType())
				{
				case CFoodBase::TYPE_EBI:
					CEbi::Create(PartsPos, D3DXVECTOR3(10.0f, 10.0f, 10.0f));
					break;
				case CFoodBase::TYPE_EGG:
					CEgg::Create(PartsPos, D3DXVECTOR3(10.0f, 10.0f, 10.0f));
					break;
				case CFoodBase::TYPE_IKURA:
					CIkura::Create(PartsPos, D3DXVECTOR3(10.0f, 10.0f, 10.0f));
					break;
				case CFoodBase::TYPE_SALMON:
					CSalmon::Create(PartsPos, D3DXVECTOR3(10.0f, 10.0f, 10.0f));
					break;
				case CFoodBase::TYPE_TUNA:
					CTuna::Create(PartsPos, D3DXVECTOR3(10.0f, 10.0f, 10.0f));
					break;
				}

				m_pParts[m_nParts - 1]->Uninit();
				m_pParts[m_nParts - 1] = nullptr;
				m_nParts -= 1;
				m_fDashDemeritCoutn = PLAYER_DASH_DEMERIT;

			}
		}
	}
}

//=============================================================================
// 点滅処理関数
//=============================================================================
void CPlayer::Flashing(void)
{
	//カウント
	m_nFlashing++;
	if (m_nFlashing % 3)
	{
		SetAlphaValue(1.0f);
	}
	else
	{
		SetAlphaValue(0.0f);
	}
}

//=============================================================================
// 点滅ストップ処理関数
//=============================================================================
void CPlayer::FlashingStop(void)
{
	//点滅のカウント初期化
	m_nFlashing = 0;
	//アルファ値を初期化
	SetAlphaValue(1.0f);
}

