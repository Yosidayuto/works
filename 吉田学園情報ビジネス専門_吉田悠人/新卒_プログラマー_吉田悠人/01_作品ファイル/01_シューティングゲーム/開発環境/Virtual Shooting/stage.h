//=============================================================================
//
// ステージ処理 [stage.h]
// Author : 吉田悠人
//
//=============================================================================
#ifndef _STAGE_H_
#define _STAGE_H_

//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "main.h"
#include "game.h"
#include "enemy base.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_ENEMY (200)	//最大エネミー数
#define MAX_STAGE (3)	//最大ステージ数
//=============================================================================
//前方宣言
//=============================================================================
class CBossBase;
class CEnemyBase;
class CScore;

typedef enum	//エネミーの出現モード
{
	ENEMY_CREATE_NULL = -1,	//初期状態
	ENEMY_CREATE_1,		//フェーズ１
	ENEMY_CREATE_2,		//フェーズ２
	ENEMY_CREATE_3,		//フェーズ３
	ENEMY_CREATE_4,		//フェーズ４
	ENEMY_CREATE_5,		//フェーズ5
	ENEMY_CREATE_6,		//フェーズ6
	ENEMY_CREATE_7,		//フェーズ7
	ENEMY_CREATE_8,		//フェーズ8
	ENEMY_CREATE_9,		//フェーズ9
	ENEMY_CREATE_MAX,
}STAGE_ENEMY;

typedef struct	//エネミーデータ
{
	ENEMY_TYPE				EnemyType;			// タイプ
	ENEMY_MOVE_PATTERN		EnemyMovePattern;	// 行動パターン
	ENEMY_ATTACK_PATTERN	EnemyAttack;		// 攻撃パターン
	int						nSpwan;				// 出現までの時間
	int						nActionTime;		// アクションタイム
	int						nAttackTime;		// 攻撃までのタイム
	int						nReturnTime;		// 戻るまでのタイム
	D3DXVECTOR3				pos;				// 最初の出現位置
	float					fSpeed;				// スピード
	int						nLife;				// 体力
}ENEMY_DATA;

typedef struct	//フェーズ情報
{
	ENEMY_DATA	EnemySpawn[MAX_ENEMY];			// エネミーデータ
	int			nEnemyCount;					// 最大エネミー数
	int			nPhaseCount;					// 次のフェーズまでの時間
} PHASE_DATA;

typedef struct //ステージ情報
{
	PHASE_DATA	Phase[ENEMY_CREATE_MAX];		// フェーズ情報
	int			nCountPhase;					// 最大フェーズ
}STAGE_DATA;


//=============================================================================
// クラス定義
//=============================================================================
class CStage
{
public:

	CStage();	//コンストラクタ
	virtual ~CStage();	//デストラクタ

	virtual HRESULT			Init(void);		// 初期化処理
	virtual void			Uninit(void);	// 終了処理
	virtual void			Update(void);	// 更新処理
	void			WarningCreate(void);				// ボス出現演出生成
	void			Result(STAGE_TYPE stage);			// リザルト
	void			SetEnemyCount(int nConut);			// エネミーカウントセット
	void			SetScore(CScore* pScore);			// スコアポインタセッター
	void			EnemeyCreate(void);					// エネミークリエイト
	static void		LoadEnemyData(void);				// エクセルからエネミーデータ取得
	virtual void	StageMode(void) = 0;				// エネミーのスポーンモード
	STAGE_DATA		GetStageEnemy(STAGE_TYPE stage);	// ステージエネミーデータゲッター
	bool			BossSearch(void);					// ボスがいるか
private:
	int					m_nCountEnemy;				// エネミー出現までのカウント
	static STAGE_DATA	m_Stage[STAGE_TYPE_MAX];	// ステージのエネミー出現データ
	static char*		pFileName[STAGE_TYPE_MAX];	// ファイルネーム
	CScore*				m_pScore;					// スコアポインタ
	ENEMY_DATA			m_Enemy[MAX_ENEMY];			// エネミーデータ保存

};
#endif