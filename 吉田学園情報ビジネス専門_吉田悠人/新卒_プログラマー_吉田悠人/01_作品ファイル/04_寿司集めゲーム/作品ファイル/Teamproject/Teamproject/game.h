//=============================================================================
//
// ゲームシーン処理 [game.h]
// Author : 林川紗梨夏
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "scene.h"
#include "camera.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CInput;
class CScene2D;
class CCamera;
class CScore;
class CPlayerControl;
class CTimer;
class CMapManager;
//=============================================================================
//マネージャークラス
//=============================================================================
class CGame : public CScene
{
public:
	typedef enum
	{
		MODETYPE_NONE = 0,
		MODETYPE_1,
		MODETYPE_2,
	} MODETYPE;

	typedef enum //現在の状態
	{
		GAMESTATE_NONE = 0,
		GAMESTATE_1,
		GAMESTATE_2,
		GAMESTATE_3,
		GAMESTATE_4,
		GAMESTATE_5,
		GAMESTATE_6,
		GAMESTATE_7,
		GAMESTATE_MAX
	}GAME_STATE;

	CGame();
	~CGame();
	static CGame *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void GameOut(void);		// ゲーム終了時の処理

	CScene2D * GetScene(void) { return m_pScene; };
	CGame * GetManager(void) { return this; };

	static bool GetIsStopUpdate(void) { return m_bIsStopUpdate; };
	static void SetIsStopUpdate(bool bIsStopUpdate) { m_bIsStopUpdate = bIsStopUpdate; };
	static bool GetIsStopUpdateContinue(void) { return m_bIsStopUpdateContinue; };
	static void SetIsStopUpdateContinue(bool bIsStopUpdateContinue) { m_bIsStopUpdateContinue = bIsStopUpdateContinue; };
	static CTimer * GetTimer(void) { return m_pTimer; };
	static GAME_STATE GetGameState(void) { return m_GameState; };
	static void SetGameType(MODETYPE mode) { m_mode = mode; };
	static MODETYPE GetGameType(void) { return m_mode; };
private:

	CScene2D*		m_pScene;				// シーンポインタ
	int				m_nGameCount;			// ゲームカウント
	CPlayerControl* m_pPlayerControl;		// プレイヤーコントロールポインタ
	CMapManager *	m_pMapManager;			// マップマネージャーポインタ
	
	static CCamera*	m_pCamera;				// カメラポインタ
	static CTimer*	m_pTimer;				// タイムポインタ
	static D3DXVECTOR3 m_Score[MAX_PLAYER];	// スコアの位置
	static MODETYPE		m_mode;				// ゲームモード

	static bool		m_bPlayerUse;			// プレイヤーが使われているか
	static bool		m_bIsStopUpdate;		// アップデート停止しているか
	static bool		m_bIsStopUpdateContinue;// コンティニュー発生しているか
	static const int	m_aGameStateTime[GAMESTATE_MAX];	// イベント発生タイミング格納
	static GAME_STATE	m_GameState;		//現在の状態
	int					m_endcount;			//終了カウンタ
};
#endif