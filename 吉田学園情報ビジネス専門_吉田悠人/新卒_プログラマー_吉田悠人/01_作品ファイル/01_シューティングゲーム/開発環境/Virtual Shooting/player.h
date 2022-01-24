//=============================================================================
//
// プレイヤー処理 [player.h]
// Author : 吉田悠人
//
//=============================================================================

#ifndef _PLAYER_H_
#define _PLAYER_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include"main.h"
#include"scene2d.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define MAX_WEAPON		 (2)	// プレイヤーの最大武装数
#define PLAYER_SIZE		 (100)	// プレイヤーのサイズ

#define PLAYER_LIFE		 (3)	// 初期ライフ
#define PLAYER_MAX_LIFE  (8)	// 最大ライフ
#define PLAYER_LIFE_UP	 (PLAYER_MAX_LIFE-PLAYER_LIFE)			// 最大ライフ強化回数

#define PLAYER_SPEED	 (4.0f)	// 初期スピード
#define PLAYER_MAX_SPEED (9.0f)	// 最大スピード
#define PLAYER_SPEED_UP	 ((int)(PLAYER_MAX_SPEED-PLAYER_SPEED))	// スピード強化回数
//=============================================================================
//前方宣言
//=============================================================================
class CLife;

typedef enum	//プレイヤーの武装
{
	WEAPONS_MODE_NONE = 0,	//NULL
	WEAPONS_MODE_BUTTOL,	//バレット
	WEAPONS_MODE_LASER,		//レーザー
	WEAPONS_MODE_HOMING,	//ホーミング
	WEAPONS_MODE_MAX
}WEAPON_TYPE;

typedef enum	//プレイヤーの状態
{
	STATS_MODE_NONE = 0,	//NULL
	STATS_MODE_NORMAL,		//通常状態
	STATS_MODE_DAMAGE,		//ダメージ状態
	STATS_MODE_DEATH		//死
}STATS_MODE;

typedef struct	//プレイヤーの武装
{
	WEAPON_TYPE Left;
	WEAPON_TYPE Right;
}WEAPON_DATA;

//=============================================================================
// クラス定義
//=============================================================================
class CPlayer :public CScene2d
{
public:
	CPlayer(int nPriorit = PRIORITY_OBJECT_0);	//コンストラクタ

	static CPlayer*	Create(D3DXVECTOR3 Pos);	//生成処理
	static void		Unload(void);				// テクスチャの破棄
	static HRESULT	Load(void);					// テクスチャ読み込み
									   
	HRESULT	Init(void);				// 初期化処理
	void	Update(void);			// 更新処理
	void	Draw(void);				// 描画処理
	void	Damage(int nDamage);	// ダメージ処理
	
	void	SetLife(int nLife);				// ライフセッター
	void	SetSpeed(float fSpeed);			// スピードセッター
	void	SetWeapon(WEAPON_DATA wepon);	// ウェポンセッター

	int			GetLife(void);		// ライフゲッター
	float		GetSpeed(void);		// スピードゲッター
	WEAPON_DATA GetWeapon(void);	// ウェポンゲッター	

private:

	void	StatasManage(void);		// 状態管理処理
	void	Move(void);				// 移動処理
	void	Weapon(void);			// 攻撃時の武装処理

	static TEXTURE_DATA	m_TextureData;	// テクスチャデータ
	STATS_MODE			Stats;			// プレイヤーの状態
	int					m_nLife;		// ライフ
	CLife*				pLife;			// ライフポインタ
	float				m_fSpeed;		// スピード
	WEAPON_DATA			m_Weapon;		// 装備中武装
	int					m_nAttackCount[MAX_WEAPON];	// 攻撃までのカウント
};
#endif