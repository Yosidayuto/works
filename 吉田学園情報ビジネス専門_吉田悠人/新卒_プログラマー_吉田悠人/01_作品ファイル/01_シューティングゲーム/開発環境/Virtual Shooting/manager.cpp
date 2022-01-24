//=============================================================================
//
// マネージャー処理 [manager.cpp]
// Author : 吉田悠人
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "manager.h"		
#include "renderer.h"		
#include "scene2d.h"		
#include "scene.h"			
#include "input.h"			
#include "inihkeyboard.h"	
#include "inputmouse.h"		
#include "sound.h"			
#include "score.h"			
#include "number.h"			
#include "load.h"
#include "fade.h"			
#include "game.h"			
#include "select.h"			
#include "clear.h"			
#include "telop.h"		
#include "mouse pointer.h"	
#include "title bg.h"
#include "title.h"
#include "tutorial bg.h"
#include "tutorial.h"
#include "select bg.h"
#include "life ui.h"
#include "weapon manager.h"
#include "button manager.h"
#include "player data.h"
#include "result bg.h"
#include "stage.h"
#include "stage_1.h"
#include "stage_2.h"
#include "stage_3.h"
#include "score bar.h"
#include <thread>

//=============================================================================
//静的メンバ変数宣言
//=============================================================================
CRenderer *CManager::m_pRenderer	 = NULL;
CInihKeyboard *CManager::m_pInput	 = NULL;
CInihMouse *CManager::m_pInihMouse	 = NULL;
CSound *CManager::m_pSound			 = NULL;
GAME_MODE CManager::m_Mode			 = GAME_MODE_LOAD;
CScene *CManager::m_pScene			 = NULL;
CFade *CManager::m_pFade			 = NULL;
int CManager::m_nScore				 = 10000;
CPlayerData *CManager::m_pPlayerData = NULL;
CGame* CManager::m_pGame			 = NULL;
CTitle* CManager::m_pTitle			 = NULL;
CSelect* CManager::m_pSelect		 = NULL;
CTutorial* CManager::m_pTutorial	 = NULL;
CLoad* CManager::m_pLoad			 = NULL;
//=============================================================================
//コンストラクタ
//=============================================================================
CManager::CManager()
{
}

//=============================================================================
//デストラクタ
//=============================================================================
CManager::~CManager()
{
}

//=============================================================================
//初期化関数
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	//インプット(キーボード)生成
	m_pInput = new CInihKeyboard;
	m_pInput->Init(hInstance, hWnd);
	
	//インプット(マウス)生成
	m_pInihMouse = new CInihMouse;
	m_pInihMouse->Init(hInstance, hWnd);
	
	//レンダリング生成
	m_pRenderer = new CRenderer;
	m_pRenderer->Init(hWnd, bWindow);

	//フェイドアウト生成
	m_pFade = new CFade;
	m_pFade->Init();

	//サウンド生成
	m_pSound = new CSound;
	m_pSound->Init(hWnd);
	//タイトル処理
	m_pTitle	= new CTitle;
	//チュートリアル処理
	m_pTutorial	= new CTutorial;
	//セレクト処理
	m_pSelect	= new CSelect;
	//ゲーム処理
	m_pGame = new CGame;
	//ロード処理
	m_pLoad = new CLoad;

	CLoad::Load();
	////ファイルロード
	//LoadFile();

	//オブジェクトクラス生成
	m_pFade->SetFade(m_Mode);

	return S_OK;
}

//=============================================================================
//終了関数
//=============================================================================
void CManager::Uninit(void)
{
	//シーンの終了
	CScene::ReleaseAll();

	//キーボード破棄
	if (m_pInput != NULL)
	{
		m_pInput->Uninit();
		delete m_pInput;
		m_pInput = NULL;
	}
	//マウス破棄
	if (m_pInihMouse != NULL)
	{
		m_pInihMouse->Uninit();
		delete m_pInihMouse;
		m_pInihMouse = NULL;
	}
	//サウンド破棄
	if (m_pSound != NULL)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = NULL;
	}
	//フェードアウト破棄
	if (m_pFade != NULL)
	{
		m_pFade->Uninit();
		delete m_pFade;
		m_pFade = NULL;
	}
	//タイトル破棄
	if (m_pTitle != NULL)
	{
		m_pTitle->Uninit();
		delete m_pTitle;
		m_pTitle = NULL;
	}
	//チュートリアル破棄
	if (m_pTutorial != NULL)
	{
		m_pTutorial->Uninit();
		delete m_pTutorial;
		m_pTutorial = NULL;
	}
	//セレクト破棄
	if (m_pSelect != NULL)
	{
		m_pSelect->Uninit();
		delete m_pSelect;
		m_pSelect = NULL;
	}
	//ゲーム破棄
	if (m_pGame != NULL)
	{
		m_pGame->Uninit();
		delete m_pGame;
		m_pGame = NULL;
	}

	//レンダリングクラスの破棄
	if (m_pRenderer != NULL)	//メモリが確保されているか
	{
		//レンダリング 終了処理
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	//ファイルアンロード処理
	UnLoadFile();
}

//=============================================================================
//更新関数
//=============================================================================
void CManager::Update()
{
	// キーボード更新 (最初に行う)
	if (m_pInput != NULL)
	{
		m_pInput->Update();
	}
	// マウス更新
	if (m_pInihMouse != NULL)
	{
		m_pInihMouse->Update();		
	}
	// レンダリング更新処理
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();		
	}
	// フェードアウト更新処理
	if (m_pFade != NULL)
	{
		m_pFade->Update();			
	}

	//場面ごとのアップデート
	switch (m_Mode)
	{
	case GAME_MODE_LOAD:
		if (m_pLoad != NULL)
		{
			if (m_pLoad->GetLoad())
			{
				//オブジェクトクラス生成
				m_pFade->SetFade(GAME_MODE_TITLE);
			}
		}
		break;

	case GAME_MODE_TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->Update();
		}
		break;
	case GAME_MODE_TUTORIAL:
		if (m_pTitle != NULL)
		{
			m_pTutorial->Update();
		}
		break;
	case GAME_MODE_SELECT:
		if (m_pSelect != NULL)
		{
			m_pSelect->Update();
		}
		break;
	case GAME_MODE_STAGE:
		if (m_pGame != NULL)
		{
			m_pGame->Update();
		}
		break;
	}

}

//=============================================================================
//描画処理
//=============================================================================
void CManager::Draw(void)
{
	//レンダラの描画
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();
	}
}


//=============================================================================
//ゲームモードセット処理
//=============================================================================
void CManager::SetMode(GAME_MODE mode)
{

	//終了処理
	switch (m_Mode)
	{
	case GAME_MODE_LOAD:
		if (m_pLoad != NULL)
		{
			m_pLoad->Uninit();
		}
		break;
	case GAME_MODE_TITLE:
		if (m_pTitle != NULL)
		{
			//タイトルシーン破棄
			m_pTitle->Uninit();
			//プレイヤー処理
			m_pPlayerData = CPlayerData::Create();
		}

		break;
	case GAME_MODE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			//チュートリアルシーンの破棄
			m_pTutorial->Uninit();
		}
		break;
	case GAME_MODE_SELECT:
		if (m_pSelect != NULL)
		{
			//セレクトシーン破棄
			m_pSelect->Uninit();
		}

		break;
	case GAME_MODE_STAGE:
		if (m_pGame != NULL)
		{
			m_pGame->Uninit();
		}
		break;
	case GAME_MODE_CLEAR:
		m_nScore = 10000;
		break;
	}

	//サウンド停止
	m_pSound->Stop();
	//モード変更処理
	m_Mode = mode;

	//初期化処理
	switch (m_Mode)
	{
	case GAME_MODE_LOAD:
		if (m_pLoad != NULL)
		{
			m_pLoad->Init();
		}
		break;

	case GAME_MODE_TITLE:
		if (m_pTitle != NULL)
		{
			//タイトル初期化処理
			m_pTitle->Init();
		}
		break;
	case GAME_MODE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			//チュートリアル初期化処理
			m_pTutorial->Init();
		}
		break;
	case GAME_MODE_SELECT:
		if (m_pSelect != NULL)
		{
			//セレクト初期化処理
			m_pSelect->SetStage(m_pGame->GetStageType());
			m_pSelect->Init();

		}
		break;
	case GAME_MODE_STAGE:
		if (m_pGame != NULL)
		{
			//ゲーム生成処理
			m_pGame->Init();
		}
		break;
	case GAME_MODE_CLEAR:
		//ゲームクリア
		CClear::Create();
		//プレイヤーのデータ破棄
		m_pPlayerData->Uninit();
		//サウンド再生
		m_pSound->Play(CSound::LABEL_SE_RESULT);
		break;
	}
}

CRenderer * CManager::GetRenderer(void)
{
	return m_pRenderer;
}

CInihKeyboard * CManager::GetKeyboard(void)
{
	return m_pInput;
}

CInihMouse * CManager::GetMouse(void)
{
	return m_pInihMouse;
}

CSound * CManager::GetSound(void)
{
	return m_pSound;
}

CFade * CManager::GetFade(void)
{
	return m_pFade;
}

int  CManager::GetScore(void)
{
	return m_nScore;
}

//=============================================================================
// プレイヤー取得
//=============================================================================
CPlayerData* CManager::GetPlayer(void)
{
	return m_pPlayerData;
}

//=============================================================================
// ファイルロード関数
//=============================================================================
void CManager::LoadFile(void)
{
	//テクスチャの読み込み
	CClear::Load();
	CNumber::Load();		
	CTelop::Load();		
	CPointer::Load();
	CTitleBg::Load();
	CTutorialBg::Load();
	CSelectBg::Load();
	CLifeUi::Load();
	CWeaponManager::Load();
	CButtonManager::Load();
	CGame::Load();
	CResultBg::Load();
	CScoreBar::Load();
	//テキスト読み込み
	CStage::LoadEnemyData();

}

//=============================================================================
// ファイルアンロード関数
//=============================================================================
void CManager::UnLoadFile(void)
{
	//テクスチャの破棄
	CClear::Unload();			
	CNumber::Unload();			
	CTelop::Unload();		
	CPointer::Unload();			
	CTitleBg::Unload();
	CTutorialBg::Unload();
	CSelectBg::Unload();
	CLifeUi::Unload();
	CWeaponManager::Unload();
	CButtonManager::Unload();
	CGame::Unload();
	CResultBg::Unload();
	CScoreBar::Unload();
	CLoad::Unload();

}

//=============================================================================
// プレイヤーデータセッター関数
//=============================================================================
void CManager::SetPlayer(CPlayerData* Player)
{
	m_pPlayerData = Player;
}




