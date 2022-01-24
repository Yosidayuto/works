//=============================================================================
//
// ゲーム処理 [game.cpp]
// Author:
//
//=============================================================================
//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "manager.h"
#include "game.h"
#include "camera.h"
#include "renderer.h"
#include "map_manager.h"
#include "player control.h"
#include "player.h"
#include "sound.h"
#include "score.h"
#include "Shield.h"
#include "scoreup.h"
#include "timer.h"
#include "timerBg.h"
#include "timecount ui.h"
#include "gameend ui.h"
#ifdef _DEBUG
//デバック用のキー
#include "keyboard.h"
#endif

#define END_TIME (120) //終了からリザルト遷移までの時間

//=============================================================================
// 静的メンバ変数初期化
//=============================================================================
bool CGame::m_bPlayerUse = true;
bool CGame::m_bIsStopUpdate = false;
bool CGame::m_bIsStopUpdateContinue = false;
CCamera* CGame::m_pCamera = nullptr;
CTimer* CGame::m_pTimer = nullptr;
CGame::MODETYPE CGame::m_mode = MODETYPE_NONE;
CGame::GAME_STATE CGame::m_GameState = GAMESTATE_NONE;
D3DXVECTOR3 CGame::m_Score[MAX_PLAYER] =
{
	D3DXVECTOR3(150.0f, 30.0f, 0.0f),
	D3DXVECTOR3(1250.0f, 30.0f, 0.0f),
	D3DXVECTOR3(150.0f, 385.0f, -50.0f),
	D3DXVECTOR3(1250.0f, 385.0f, -50.0f)

};

//イベント発生タイミングの時間を格納（フレーム単位）
const int CGame::m_aGameStateTime[GAMESTATE_MAX] =
{
	-1,
	2700,
	1800,
	1500,
	900,
	600,
	300,
	0
};

//=============================================================================
// コンストラクタ
//=============================================================================
CGame::CGame()
{
	m_pMapManager		= nullptr;
	m_pPlayerControl	= nullptr;
	m_nGameCount		= 0;
	m_nGameCount		= 0;
	m_endcount = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CGame::~CGame()
{

}

//=============================================================================
// 生成処理
//=============================================================================
CGame * CGame::Create(void)
{
	CGame *pGame;
	pGame = new CGame;
	if (pGame != nullptr)
	{
		pGame->Init();
	}
	return pGame;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CGame::Init()
{
	//オブジェクト生成
	CManager::CreateCamera();
	CManager::CreateLight();

	//スコア生成
	for (int nPlayer = 0; nPlayer < MAX_PLAYER; nPlayer++)
	{
		CManager::SetScore(CScore::Create(m_Score[nPlayer], D3DXVECTOR3(30.0f, 60.0f, 0.0f)), nPlayer);
	}
	
	//カメラ設定
	m_pCamera = CManager::GetCamera();
	
	//全てのプレイヤーの管理(プレイヤー4人の生成処理とプレイヤー関係のマネージャー)	
	CManager::SetPlayerControl(CPlayerControl::Create());//情報ほしいのでマネージャーにセットしてほしいです
	
	//マップ作成（ここでミニマップ、管理処理も生成する）
	m_pMapManager = CMapManager::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f));
	
	//タイム生成
	CtimerBg::Create(TIMER_POSBG, TIMERBG_SIZE, D3DCOLOR_RGBA(255, 255, 255, 255));

	if (m_mode == MODETYPE_1)
	{
		m_pTimer = CTimer::Create(TIMER_POS, TIMER_SIZE, MOOD1_MINUTES, MOOD1_SECONDS);
	}
	else if (m_mode == MODETYPE_2)
	{
		m_pTimer = CTimer::Create(TIMER_POS, TIMER_SIZE, MOOD2_MINUTES, MOOD2_SECONDS);
	}
	else
	{

	}

	//サウンド処理
	CSound *pSound = CManager::GetSound();
	pSound->PlaySound(CSound::LABEL_BGM_GAME);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CGame::Uninit(void)
{
	//サウンドストップ
	CSound *pSound = CManager::GetSound();
	pSound->StopSound();
}

//=============================================================================
// 更新処理
//=============================================================================
void CGame::Update(void)
{
	//サウンド
	CSound * pSound = CManager::GetSound();
	//キーボードの取得
	CKeyboard * pInputKeyboard = CManager::GetInputKeyboard();

	//現在の状態
	if (m_GameState != GAMESTATE_7)//最終フェーズまで続ける
	{
		if (m_pTimer->GetTime() <= m_aGameStateTime[m_GameState + 1])
		{
			m_GameState = GAME_STATE((int)m_GameState + 1);	//状態を一段階上げる
			
			if (m_GameState == GAMESTATE_5)			//ステージ状態が5以上の時
			{
				//プレイヤーをリスポーン出来なくする
				CManager::GetPlayerControl()->SetRespawn(false);
			}
			if (m_GameState == GAMESTATE_6)//残り10秒
			{
				CTimecountUi::Create(D3DXVECTOR3(1980.0f, 400.0f, 0.0f), D3DXVECTOR3(-20.0f, 0.0f, 0.0f), D3DXVECTOR3(320.0f, 85.0f, 0.0f));
				pSound->PlaySound(CSound::LABEL_SE_COUNTDOWN);
			}
			if (m_GameState == GAMESTATE_7)//ゲーム終了
			{
				//プレイヤーの取得
				for (int nPlayer = 0; nPlayer<MAX_PLAYER; nPlayer++)
				{
					CPlayer* pPlayer = CManager::GetPlayerControl()->GetPlayer(nPlayer);
					pPlayer->SetStats(CPlayer::PLAYER_STATS_NONE);
				}

				//ゲーム終了お知らせのUI
				CGameEndUi::Create(D3DXVECTOR3(SCREEN_CENTER_X, -50.0f, 0.0f), D3DXVECTOR3(0.0f, 10.0f, 0.0f), D3DXVECTOR3(834.0f, 289.0f, 0.0f));
				//SE
				pSound->PlaySound(CSound::LABEL_SE_PIPI);
			}
		}
	}

	//カメラにプレイヤーの位置を伝える
	for (int nPlayer = 0; nPlayer < MAX_PLAYER; nPlayer++)
	{
		m_pCamera->SetPos(nPlayer, CManager::GetPlayerControl()->GetPlayer(nPlayer)->GetPos());
	}
	//ステージサイズセット
	CManager::GetPlayerControl()->SetMapSize(m_pMapManager->GetMapSize());
	//制限時間を過ぎた際の処理
	GameOut();

#ifdef _DEBUG
	//デバック
	if (pInputKeyboard->GetKeyTrigger(DIK_RETURN))
	{
		CManager::SetMode(CManager::MODE_RESULT);
	}
#endif

}

//=============================================================================
// 描画処理
//=============================================================================
void CGame::Draw(void)
{

}

//=============================================================================
// ゲーム終了時の処理
//=============================================================================
void CGame::GameOut(void)
{
	if (m_GameState == GAMESTATE_7)
	{
		m_endcount++;
		//制限時間が来たら
		if (m_endcount >= END_TIME)
		{
			//マネージャーに最終スコアを渡す
			for (int nCount = 0;nCount < MAX_PLAYER;nCount++)
			{
				CManager::SetResultScore(nCount,CManager::GetScore(nCount)->GetScore());
			}
			
			m_GameState = GAMESTATE_NONE;
			//画面遷移
			CManager::SetMode(CManager::MODE_RESULT);
			return;
		}
	}
	
	//プレイヤーコントロールの取得
	CPlayerControl* pPlayerControl = CManager::GetPlayerControl();
	//やられているプレイヤーの数
	int nDeathPlayer = 0;
	
	//プレイヤーずつに確認
	for (int nPlayer = 0; nPlayer < MAX_PLAYER; nPlayer++)
	{
		//プレイヤーのポインタの取得
		CPlayer *pPlayer = pPlayerControl->GetPlayer(nPlayer);
		if (pPlayer->GetStats() == CPlayer::PLAYER_STATS_DEATH)
		{
			//一人追加
			nDeathPlayer += 1;
		}
	}

	//プレイヤーが一人になった時
	if (nDeathPlayer>=3)
	{
		m_endcount++;
		//制限時間が来たら
		if (m_endcount >= END_TIME)
		{
			//画面遷移
			CManager::SetMode(CManager::MODE_RESULT);
			m_GameState = GAMESTATE_NONE;
			return;
		}
	}
}
