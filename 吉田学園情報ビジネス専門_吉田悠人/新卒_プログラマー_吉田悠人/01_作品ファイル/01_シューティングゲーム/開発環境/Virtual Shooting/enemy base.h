//=============================================================================
//
// エネミーベース処理 [enemy base.h]
// Author : 吉田悠人
//
//=============================================================================

#ifndef _ENEMY_BASE_H_
#define _ENEMY_BASE_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include"main.h"
#include"scene2d.h"
//=============================================================================
//マクロ定義
//=============================================================================
#define ENEMY_POINTER (5)	//エネミーの最大移動ポインタ
//=============================================================================
//前方宣言
//=============================================================================
class CShotsBase;
typedef enum						//エネミータイプ
{
	ENEMY_TYPE_1 = 0,
	ENEMY_TYPE_2,
	ENEMY_TYPE_3,
	ENEMY_TYPE_4,
	ENEMY_TYPE_MAX
}ENEMY_TYPE;

typedef enum						//エネミー行動パターン
{
	ENEMY_MOVE_RETURN = 0,			//Uターン
	ENEMY_MOVE_STRAIGHT,			//直進
	ENEMY_MOVE_RIGHT,				//右に曲がる
	ENEMY_MOVE_LEFT,				//左に曲がる
	ENEMY_MOVE_RIGHT_SLIDE,			//右に向かって横移動
	ENEMY_MOVE_LEFT_SLIDE,			//左に向かって横移動
	ENEMY_MOVE_RIGHT_STOP,			//右に向かって横移動(途中で一度止まる)
	ENEMY_MOVE_LEFT_STOP,			//左に向かって横移動(途中で一度止まる)
	ENEMY_MOVE_MAX,
}ENEMY_MOVE_PATTERN;

typedef enum						//エネミーパターン
{
	BULLET_PATTERN_NONE = 0,		//NULL
	BULLET_PATTERN_SHOTS,			//通常ショット
	BULLET_PATTERN_SPIRAL,			//螺旋ショット
	BULLET_PATTERN_MAX				
}ENEMY_ATTACK_PATTERN;

//=============================================================================
// クラス定義
//=============================================================================
class CEnemyBase :public CScene2d
{
public:

	CEnemyBase(int nPriorit = PRIORITY_OBJECT_1);	//コンストラクタ

	static HRESULT	Load(void);		//テクスチャ読み込み
	static void		Unload(void);	//テクスチャの破棄

	void	Update(void);			// 更新処理
	void	StatasManage(void);		// 状態管理
	void	Damage(int nDamage);	// ダメージ処理
	void	Hit(void);				// 当たり判定
	void	Move(void);				// 移動処理
	void	Rotate(void);			// 回転処理
	void	Bullet(void);			// ショット処理

	void		SetMovePattern(ENEMY_MOVE_PATTERN MovePattern);			// 行動パターンセッター
	void		SetAttackPattern(ENEMY_ATTACK_PATTERN AttackPaattern);	// 攻撃パターンセッター
	void		SetInTime(int nInTime);			// 出現時間セッター
	void		SetActionTime(int nActionTime);	// 行動時間セッター
	void		SetAttackTime(int nAttackTime);	// 攻撃時間セッター
	void		SetOutTime(int nOutTime);		// 帰還時間セッター

	void		SetLife(int nLife);				// ライフセッター
	int			GetLife(void);					// ライフゲッター
	void		SetScore(int nScore);			// スコアセッター
	int			GetScore(void);					// スコアゲッター
	void		SetSpeed(float nSpeed);			// スピードセッター
	float		GetSpeed(void);					// スピードゲッター

private:
	typedef enum				// エネミーの状態
	{
		STATS_MODE_NORMAL = 0,	// 通常状態
		STATS_MODE_DAMAGE,		// ダメージ状態
		STATS_MODE_DEATH		// 死
	}STATS_MODE;

	ENEMY_MOVE_PATTERN		m_MovePattern;				// 移動パターン	
	ENEMY_ATTACK_PATTERN	m_Shots;					// ショットタイプ

	int					m_nInTime;						// 画面に入ってくるまで
	int					m_nActionTime;					// 行動を起こすまでのタイム
	int					m_nAttackTime;					// 攻撃までの時間
	int					m_nOutTime;						// 帰還タイム
	int					m_nCount;						// カウント
	int					m_nLife;						// エネミーのライフ
	float				m_fSpped;						// エネミースピード

	STATS_MODE			m_Stats;						// エネミーの状態
	bool				m_bAttack;						// 攻撃したか
	int					m_Score;						// スコア
	CShotsBase*			m_pShotsBase;					// ショットポインタ
	float				m_fRot;							// 回転角度

};
#endif