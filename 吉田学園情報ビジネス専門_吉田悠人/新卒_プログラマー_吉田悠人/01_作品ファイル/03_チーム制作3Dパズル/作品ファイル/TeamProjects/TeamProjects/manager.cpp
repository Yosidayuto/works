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
#include "light.h"
#include "input.h"
#include "inputkeyboard.h"
#include "inputcontroller.h"
#include "sound.h"
#include "fade.h"
#include "camera.h"
#include "title.h"
#include "game.h"
#include "inputmouse.h"
#include "pause.h"
#include "child.h"

#include "resource manager.h"
#include "player.h"
//=============================================================================
//静的メンバ変数宣言
//=============================================================================
CRenderer*		CManager::m_pRenderer			= NULL;
CFade*			CManager::m_pFade				= NULL;
CManager::MODE	CManager::m_mode				= MODE_TITLE;
CSound*			CManager::m_pSound				= NULL;
CInput*			CManager::m_pInputKey			= NULL;
CInput*			CManager::m_pInputMou			= NULL;
CInput*			CManager::m_pInputController	= NULL;
CCamera*		CManager::m_pCamera				= NULL;
CTitle*			CManager::m_pTitle				= NULL;
CGame*			CManager::m_pGame				= NULL;
CPause*			CManager::m_pPause				= NULL;
CResource*		CManager::m_Resource			= NULL;
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
HRESULT CManager::Init(HWND hWnd, bool bWindow, HINSTANCE hInstance)
{
	//レンダラを生成
    HRESULT hResult = NULL;
    m_pRenderer     = new CRenderer;

	//レンダラを初期化
	if (m_pRenderer != NULL)
	{
		hResult = m_pRenderer->Init(hWnd, bWindow);
	}

	//ライトの生成
    CLight* pLight	= NULL;						
    pLight			= new CLight;	
	//ライトの初期化
	if (pLight != NULL)
	{
		pLight->Init();
	}

	//キーボード生成
    m_pInputKey = new CInputKeyboard;		
	if (m_pInputKey != NULL)
	{
		m_pInputKey->Init(hInstance, hWnd);
	}

	//マウス生成
	m_pInputMou = new CInputMouse;
	if (m_pInputMou != NULL)
	{
		m_pInputMou->Init(hInstance, hWnd);
	}

	//コントローラー生成
	m_pInputController = new CInputJoyStick;
	if (m_pInputController != NULL)
	{
		if (m_pInputController->Init(hInstance, hWnd) == E_FAIL)
		{
			m_pInputController = NULL;
		}
	}

    //サウンドの生成
	m_pSound = new CSound;
	if (m_pSound != NULL)
	{
		//サウンドの初期化
		m_pSound->Init(hWnd);
	}

	//フェード生成
	m_pFade = CFade::Create();
	
	//ポーズ生成
	m_pPause = new CPause;

	//ファイル読み込み
	m_Resource = new CResource;
	//リソース読み込み
	m_Resource->Init();

    //LoadFile();				
	
	//メモリ確保
	m_pTitle	= new CTitle;	//タイトル
	m_pGame		= new CGame;	//ゲーム
	
	m_pFade->SetBlackout(m_mode);
	return hResult;
}

//=============================================================================
//終了関数
//=============================================================================
void CManager::Uninit(void)
{
    //シーンの終了
    CObject::ReleaseAll();

    //フェード終了
    if(m_pFade != NULL)
    {
		m_pFade->Uninit();
        delete m_pFade;
		m_pFade = NULL;
    }
	//ポーズ終了
	if (m_pPause!=NULL)
	{
		m_pPause->Uninit();
		delete m_pPause;
		m_pPause = NULL;

	}
    //キーボード入力の終了
	if (m_pInputKey != NULL)
	{
		m_pInputKey->Uninit();
		delete m_pInputKey;
		m_pInputKey = NULL;
	}
	
	//マウス入力の終了
	if (m_pInputMou != NULL)
	{
		m_pInputMou->Uninit();
		delete m_pInputMou;
		m_pInputMou = NULL;
	}

	//コントローラー入力の終了
	if (m_pInputController != NULL)
	{
		m_pInputController->Uninit();
		delete m_pInputController;
		m_pInputController = NULL;
	}
	//カメラの終了
	if (m_pCamera != NULL)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = NULL;
	}

    //レンダラの終了
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	//リソースの終了処理
	if (m_Resource != NULL)
	{
		m_Resource->Uninit();
		delete m_Resource;
		m_Resource = NULL;
	}
    
	//サウンドの破棄
    if(m_pSound != NULL)
    {
		//サウンドの停止
		m_pSound->StopSound();

        m_pSound->Uninit();
        delete m_pSound;
        m_pSound = NULL;
    }

}

//=============================================================================
//更新関数
//=============================================================================
void CManager::Update(void)
{
    //キーボード入力の更新
    if(m_pInputKey != NULL)
    {
        m_pInputKey->Update();
    }

	//マウス入力の更新
    if(m_pInputMou != NULL)
    {
        m_pInputMou->Update();
    }

	//コントロール入力の更新
	if (m_pInputController != NULL)
	{
		m_pInputController->Update();
	}

	//レンダラの更新
	if (m_pRenderer != NULL&&!m_pPause->GetPause())
	{
		m_pRenderer->Update();
	}

    //フェード更新
    if(m_pFade != NULL)
    {
		m_pFade->Update();
    }

	//ポーズ状態か
	if (m_pPause->GetPause())		//ポーズなら
	{
		//ポーズ更新
		m_pPause->Update();
	}
	else						//ポーズでないなら
	{
		//場面ごとの更新
		switch (m_mode)
		{
		case MODE_TITLE:	//タイトル
			if (m_pTitle != NULL)
			{
				m_pTitle->Update();
			}
			break;
		case MODE_GAME:		//ゲーム
			if (m_pGame != NULL)
			{
				m_pGame->Update();
				//ポーズ生成
				PauseStart();
			}
			break;
		}

	}
}

//=============================================================================
//描画関数
//=============================================================================
void CManager::Draw(void)
{
	//モード処理
    switch(m_mode)
    {
        case MODE_TITLE:	//タイトル
			if (m_pTitle != NULL)
			{
				m_pTitle->Draw();
			}
			break;
		case MODE_GAME:		//ゲーム
			if (m_pGame != NULL)
			{
				m_pGame->Draw();
			}
			break;
    }

    //レンダラの描画
    if(m_pRenderer != NULL)
    {
        m_pRenderer->Draw();
    }
}

//=============================================================================
//ゲッター関数
//=============================================================================
CRenderer* CManager::GetRenderer(void)
{
    return m_pRenderer;
}

CResource * CManager::GetResource(void)
{
	return m_Resource;
}

CInput* CManager::GetInputKey(void)
{
    return m_pInputKey;
}

CInput* CManager::GetInputMou(void)
{
    return m_pInputMou;
}

CInput * CManager::GetInputController(void)
{
	return m_pInputController;
}

CCamera* CManager::GetCamera(void)
{
    return m_pCamera;
}

CSound * CManager::GetSound(void)
{
	return m_pSound;
}

void CManager::BindCamera(CCamera* pCamera)
{
	m_pCamera = pCamera;
	CChild::Load();
}

//=============================================================================
//モード切替
//=============================================================================
void CManager::SetMode(MODE mode)
{
	//ポーズ終了
	m_pPause->Delete();
    //終了処理
    switch(m_mode)
    {
        case MODE_TITLE:	//タイトル	
			if (m_pTitle != NULL)
			{
				m_pTitle->Uninit();
			}
            break;
		case MODE_GAME:		//ゲーム
			if (m_pGame != NULL)
			{
				m_pGame->Uninit();
			}
			break;
    }

	//モード切替
	m_mode = mode;

    switch(m_mode)
    {
        case MODE_TITLE:	//タイトル
			if (m_pTitle != NULL)
			{
				m_pTitle->Init();
			}
            break;
		case MODE_GAME:		//ゲーム
			if (m_pGame != NULL)
			{
				m_pGame->Init();
			}
			break;
    }
}

//=============================================================================
// ポーズモードスタート
//=============================================================================
void CManager::PauseStart(void)
{
	//コントローラー入力取得
	CInputJoyStick* pJoyInput = (CInputJoyStick*)CManager::GetInputController();
	//入力確認スイッチ
	bool bJoyStick = false;
	
	//コントローラー入力確認
	if (pJoyInput != NULL)
	{
		if (pJoyInput->GetJoyStickTrigger(CInputJoyStick::JOY_BUTTON_SELECT))
		{
			bJoyStick = true;
		}
	}

	//ポーズ画面生成
	if (!m_pPause->GetPause() &&((CInputKeyboard*)m_pInputKey)->GetKeyTrigger(DIK_P)|| bJoyStick)
	{
		m_pPause->Init();
	}
}


//=============================================================================
// モード取得
//=============================================================================
CManager::MODE CManager::GetMode(void)
{
    return m_mode;
}
