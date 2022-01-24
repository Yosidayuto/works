//=============================================================================
//
// 管理処理 [manager.cpp]
// Author : 林川紗梨夏
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "keyboard.h"
#include "mouse.h"
#include "sound.h"
#include "joystick.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "camera.h"
#include "light.h"
#include "resource manager.h"
#include "fade.h"
#include "Tutorial.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
CRenderer * CManager::m_pRenderer = nullptr;
CKeyboard * CManager::m_pKeyboard = nullptr;
CJoystick * CManager::m_pJoystick = nullptr;
CMouse * CManager::m_pMouse	= nullptr;
CSound * CManager::m_pSound = nullptr;
CGame * CManager::m_pGame = nullptr;
CResult * CManager::m_pResult = nullptr;
CTitle * CManager::m_pTitle = nullptr;
CTutorial * CManager::m_pTutorial = nullptr;
CSelect * CManager::m_pSelect = nullptr;
CCamera *CManager::m_pCamera = nullptr;
CLight *CManager::m_pLight = nullptr;
CManager::MODE CManager::m_mode = MODE_NONE;
CPlayer * CManager::m_pPlayer = nullptr;
CMapManager * CManager::m_pMapManager = nullptr;
HWND CManager::m_hWnd = nullptr;
CResource * CManager::m_pResource = nullptr;
CScore * CManager::m_apScore[MAX_PLAYER] = {};
CPlayerControl * CManager::m_pPlayerControl = nullptr;
int CManager::m_nPlayerNumber = NULL;
CFade* CManager::m_pFade = nullptr;
int CManager::m_nResultScore[MAX_PLAYER] = {};
//=============================================================================
// コンストラクタ
//=============================================================================
CManager::CManager()
{
	m_hWnd = nullptr;
}

//=============================================================================
// デストラクタ
//=============================================================================
CManager::~CManager()
{
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInsitance, HWND hWnd, bool bWindow)
{
	//レンダラーの生成
	if (m_pRenderer == nullptr)
	{
		m_pRenderer = new CRenderer;
	}
	//レンダラーの初期化
	m_pRenderer->Init(hWnd, bWindow);

	//入力の生成
	if (m_pKeyboard == nullptr)
	{
		m_pKeyboard = new CKeyboard;
	}
	//キーボードの初期化
	m_pKeyboard->Init(hInsitance, hWnd);

	//入力の生成
	if (m_pMouse == nullptr)
	{
		m_pMouse = new CMouse;
	}
	//マウスの初期化
	m_pMouse->Init(hInsitance, hWnd);

	//ジョイスティックの生成
	if (m_pJoystick == nullptr)
	{
		m_pJoystick = new CJoystick;
	}
	//ジョイスティックの初期化
	m_pJoystick->Init(hInsitance, hWnd);

	//サウンドの生成
	if (m_pSound == nullptr)
	{
		m_pSound = new CSound;
	}
	//サウンドの初期化
	m_pSound->Init(hWnd);

	//フェードの生成
	if (m_pFade == nullptr)
	{
		m_pFade = new CFade;
	}
	//フェードの初期化
	m_pFade->Init();

	//カーソル見えなくする
	//ShowCursor(FALSE);

	//全てのリソース読み込み
	if (m_pResource == nullptr)
	{
		m_pResource = new CResource;
	}
	m_pResource->Init();

	SetMode(MODE_GAME);

	m_hWnd = hWnd;
	return S_OK;
}

//=============================================================================	
// 終了処理関数
//=============================================================================
void CManager::Uninit(void)
{
	CScene::ReleaseAll();

	//サウンドの停止
	m_pSound->StopSound();

	//サウンドの破棄
	if (m_pSound != nullptr)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = NULL;
	}

	//ジョイスティックの破棄
	if (m_pJoystick != nullptr)
	{
		m_pJoystick->Uninit();
		delete m_pJoystick;
		m_pJoystick = nullptr;
	}

	//マウスの破棄
	if (m_pMouse != nullptr)
	{
		m_pMouse->Uninit();
		delete m_pMouse;
		m_pMouse = nullptr;
	}

	//キーボードの破棄
	if (m_pKeyboard != nullptr)
	{
		m_pKeyboard->Uninit();
		delete m_pKeyboard;
		m_pKeyboard = nullptr;
	}

	//カメラの終了
	if (m_pCamera != nullptr)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}

	//レンダラーの破棄
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	////フェードの破棄
	if (m_pFade != nullptr)
	{
		m_pFade->Uninit();
		delete m_pFade;
		m_pFade = nullptr;
	}

	//全てのリソース破棄
	if (m_pResource != nullptr)
	{
		m_pResource->Uninit();
		delete m_pResource;
		m_pResource = nullptr;
	}
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CManager::Update(void)
{
	//キーボードの更新
	if (m_pKeyboard != nullptr)
	{
		m_pKeyboard->Update();
	}

	//マウスの更新
	if (m_pMouse != nullptr)
	{
		m_pMouse->Update();
	}

	//ジョイスティックの更新
	if (m_pJoystick != nullptr)
	{
		m_pJoystick->Update();
	}

	//カメラの更新処理
	if (m_pCamera != nullptr)
	{
		m_pCamera->Update();
	}

	//フェードの更新処理
	if (m_pFade != NULL)
	{
		m_pFade->Update();
	}

	//描画の更新
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Update();
	}

}

//=============================================================================
// 描画処理関数
//=============================================================================
void CManager::Draw(void)
{
	if (m_pCamera != nullptr)
	{
		// 現在のシーン状況で画面分割をする
		// ゲームシーン以外の場合分割しない
		if (m_mode != MODE_GAME)
		{
			m_pCamera->SetUpViewport();
			m_pCamera->SetCamera();
			m_pRenderer->Draw();
		}
		// ゲームシーンの場合分割する
		else
		{
			for (int nCamera = 0; nCamera<MAX_PLAYER; nCamera++)
			{
				m_pCamera->SetUpViewport(nCamera);
				m_pCamera->SetCamera(nCamera);
				m_pRenderer->Draw();
			}

		}
	}
}

//=============================================================================
// モード設定関数
//=============================================================================
void CManager::SetMode(MODE mode)
{
	m_pPlayer = nullptr;
	//m_pMapManager = nullptr;
	CScene::ReleaseAll();

	//モードの割り当て
	m_mode = mode;

	//モードの切り替え
	switch (mode)
	{
	case MODE_TITLE:
		m_pTitle = CTitle::Create();
		break;
	case MODE_TUTORIAL:
		m_pTutorial = CTutorial::Create();
		break;
	case MODE_GAME:
		m_pGame = CGame::Create();
		break;
	case MODE_RESULT:
		m_pResult = CResult::Create();
		break;
	}
}

//=============================================================================
//  カメラ生成
//=============================================================================
void CManager::CreateCamera(void)
{
	// m_pCameraがNULLの場合
	if (m_pCamera == nullptr)
	{
		// メモリ確保
		m_pCamera = new CCamera;

		// m_pCameraがNULLでない場合
		if (m_pCamera != nullptr)
		{
			// 初期化
			m_pCamera->Init();
		}
	}
}

//=============================================================================
//  ライト生成
//=============================================================================
void CManager::CreateLight(void)
{
	// m_pLightがNULLの場合
	if (m_pLight == nullptr)
	{
		// メモリ確保
		m_pLight = new CLight;

		// m_pLightがNULLでない場合
		if (m_pLight != nullptr)
		{
			// 初期化
			m_pLight->Init();
		}
	}
}
//=============================================================================
//  カメラ割り当て
//=============================================================================
void CManager::BindCamera(CCamera * pCamera)
{
	m_pCamera = pCamera;
}
//=============================================================================
//  ウィンドウがアクティブかチェック
//=============================================================================
bool CManager::GetIsActiveWindow(void)
{
	bool bActive = false;
	if (GetForegroundWindow() == m_hWnd)
	{
		bActive = true;
	}
	else
	{
		bActive = false;
	}
	return bActive;
}
//=============================================================================
//  スコアポインタセット
//=============================================================================
void CManager::SetScore(CScore * pScore, int nPlayer)
{
	m_apScore[nPlayer] = pScore;
}

//=============================================================================
//  プレイヤー管理ポインタセット
//=============================================================================
void CManager::SetPlayerControl(CPlayerControl * pPlayerControl)
{
	m_pPlayerControl = pPlayerControl;
}

//=============================================================================
// プレイヤー人数セッター
//=============================================================================
void CManager::SetPlayerNumber(const int nNumber)
{
	m_nPlayerNumber = nNumber;
}

//=============================================================================
// プレイヤー最終スコアセッター
//=============================================================================
void CManager::SetResultScore(int nPlayer ,int nScore)
{
	m_nResultScore[nPlayer] = nScore;
}
