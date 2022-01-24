//=============================================================================
//
// プレイヤー [player.h]
// Author : 吉田悠人
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//=============================================================================
// ヘッダーファイル
//=============================================================================
#include "scene3d.h"
#include "model.h"
#include "food base.h"
//=============================================================================
// 前方宣言
//=============================================================================
class CPlayerParts;
//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_PARTS (500)	//最大パーツ数

//=============================================================================
//クラス定義
//=============================================================================
class CPlayer : public CModel
{
public:
	CPlayer(int nPriority = 3);
	~CPlayer();
	typedef enum	//プレイヤーの状態
	{
		PLAYER_STATS_NONE = 0,	// NULL
		PLAYER_STATS_NORMAL,	// 通常状態
		PLAYER_STATS_REPEL,		// はじかれ状態
		PLAYER_STATS_RESPAWN,	// リスポーン状態
		PLAYER_STATS_DEATH		// 死亡状態
	}PLAYER_STATS;

	static CPlayer* Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, D3DXVECTOR3 Size,int nModel);	//生成処理

	void			Update(void);
	void			Draw(void);
	void			Repel(CScene3d* Player);					// はじかれる処理
	void			AddParts(CFoodBase::FOOD_TYPE FoodType);	// パーツ追加（食べ物を食べた後の追加パーツ）処理関数
	virtual void	RotControl(D3DXVECTOR3 Control);			// コントローラーでの操作
	void			Dash(bool bDash);							// ダッシュ状態に移行
	void			DamageHit(void);							// プレイヤーがダメージを受けるモノにぶつかった際の処理
	void			BarrierHit(void);							// マップ端でのダメージヒット処理
	void			Respawn(D3DXVECTOR3 RespawnPos);			// リスポーン処理
	void			ShieldGet(void);							// シールド取得処理
	void			ScoreUpGet(void);							// スコアアップ処理
	void			ScoreUpCount(void);							// スコアアップ
	void			SwitchedInvincible(int nInvincible);		// 無敵状態に移行

	CPlayerParts*	GetParts(int nParts) { return m_pParts[nParts]; }				// パーツゲッター
	int				GetPartsCount(void) { return m_nParts; }						// パーツ数ゲッター
	void			SetStats(const PLAYER_STATS Stats) { m_PlayerStats = Stats; }	// プレイヤー状態セッター
	PLAYER_STATS	GetStats(void) { return m_PlayerStats; }						// プレイヤー状態ゲッター
	bool			GetScoreUp(void) { return m_bScoreUp; }							// スコアアップ状態のゲッター
	bool			GetShield(void) { return m_bShield; }							// シールド状態のゲッター

private:
	void			Move(void);								// 移動処理
	void			Rot(void);								// 向き処理
	void			Invincible(void);						// 無敵処理
	void			DashDemerit(void);		// ダッシュ時のデメリット処理
	void			RepelMove(void);		// はじかれ移動処理
	void			RespawnStats(void);		// リスポーン状態時処理
	void			Death(void);			// 死亡処理
	void			Flashing(void);			// 点滅処理
	void			FlashingStop(void);		// 点滅ストップ処理

	PLAYER_STATS	m_PlayerStats;			// プレイヤーステータス
	int				m_nLife;				// ライフ
	D3DXVECTOR3		m_RotMove;				// 向きの移動量
	int				m_nRepelFrameCount;		// はじかれた際の移動時のフレームカウント
	D3DXVECTOR3		m_RepelMove;			// はじかれ移動量
	int				m_nFlashing;			// 点滅する際のフレームカウント
	bool			m_bInvincible;			// 無敵状態のスイッチ
	int				m_nInvinciFrameCount;	// 無敵状態のフレームカウント
	int				m_MaxInvinciCount;		// 無敵状態の最大カウント数
	bool			m_bShield;				// アイテムのシールドスイッチ（持っているか）
	bool			m_bScoreUp;				// アイテムのスコアアップの　(状態になっているか)
	float			m_fDashCoutn;			// 加速値
	float			m_fDashDemeritCoutn;	// 加速時のデメリットカウント
	bool			m_bDashSwitch;			// 加速切替スイッチ
	int				m_nParts;				// パーツ数
	CPlayerParts*	m_pParts[MAX_PARTS];	// パーツポインタ
	int				m_nItemCount;			// 効果カウント用変数
};
#endif // !_PLAYER_H_


