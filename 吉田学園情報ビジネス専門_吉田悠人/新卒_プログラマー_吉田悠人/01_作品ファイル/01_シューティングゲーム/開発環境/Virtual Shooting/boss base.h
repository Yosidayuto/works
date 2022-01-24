//=============================================================================
//
// ボスベース処理 [boss base.h]
// Author : 吉田悠人
//
//=============================================================================

#ifndef _BOSS_BASE_H_
#define _BOSS_BASE_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include"main.h"
#include"scene2d.h"

//=============================================================================
//前方宣言
//=============================================================================
class CShotsBase;

typedef enum						//エネミータイプ
{
	BOSS_TYPE_1 = 0,
	BOSS_TYPE_2,
	BOSS_TYPE_3,
	BOSS_TYPE_4
}BOSS_TYPE;
typedef enum						//エネミーパターン
{
	BOSS_PATTERN_NONE = 0,		//NULL
	BOSS_PATTERN_SHOTS,			//通常ショット
	BOSS_PATTERN_BUCKSHOT,		//散弾ショット
	BOSS_PATTERN_All_DIR,		//全方位ショット
	BOSS_PATTERN_SPLIT,			//分裂ショット
	BOSS_PATTERN_SPIRAL,		//螺旋ショット
	BOSS_PATTERN_MAX			//マックス
}BOSS_PATTERN;

//=============================================================================
// クラス定義
//=============================================================================
class CBossBase :public CScene2d
{
public:
	CBossBase(int nPriorit = PRIORITY_OBJECT_1);	//コンストラクタ

	static HRESULT	Load(void);		//テクスチャ読み込み
	static void		Unload(void);	//テクスチャの破棄

	HRESULT Init(void);				// 初期化処理
	void	Update(void);			// 更新処理
	void	StatasManage(void);		// 状態管理
	void	Damage(int nDamage);	// ダメージ処理
	void	Hit(void);				// 当たり判定
	void	Bullet(void);			// ボスのショット処理
	bool	CoolTime(void);			// 攻撃時のクールタイム

	virtual void	Effect(void) = 0;		//エフェクト生成
	virtual void	DisEffect(void) = 0;	//倒されたときのエフェクト処理

	void		SetCoolTime(int nCoolTime);	// クールタイムセッター
	int			GetCoolTime(void);			// クールタイムゲッター
	void		SetLife(int nLife);			// ライフセッター
	int			GetLife(void);				// ライフゲッター
	void		SetScore(int nScore);		// スコアセッター
	int			GetScore(void);				// スコアゲッター
	void			SetPattern(BOSS_PATTERN type);	//攻撃パターンセッター
	BOSS_PATTERN	GetPattern(void);				//攻撃パターンゲッター
private:
	typedef enum	// エネミーの状態
	{
		STATS_MODE_NORMAL = 0,	// 通常状態
		STATS_MODE_DAMAGE,		// ダメージ状態
		STATS_MODE_DEATH		// 死
	}STATS_MODE;

	STATS_MODE			m_Stats;			// エネミーの状態
	BOSS_PATTERN		m_Shots;			// ショットタイプ
	int					m_Score;			// スコア
	int					m_nLife;			// エネミーのライフ
	int					m_nCoolTime;		// 攻撃時のクールタイム
	int					m_nLimitCoolTime;	// クールタイムの最大値
	CShotsBase*			m_pShots;			// ショットポインタ
};
#endif