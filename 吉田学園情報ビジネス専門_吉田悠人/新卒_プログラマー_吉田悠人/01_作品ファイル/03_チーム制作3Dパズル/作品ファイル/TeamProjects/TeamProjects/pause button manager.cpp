
//=============================================================================
//
//	タイトルボタンマネージャー[button title.h]
//	Author:吉田　悠人
//
//=============================================================================
//=============================================================================
//インクルードファイル
//=============================================================================
#include "pause button manager.h"
#include "renderer.h"
#include "manager.h"
#include "inputcontroller.h"
#include "inputkeyboard.h"
#include "button.h"
#include "start button.h"
#include "end button.h"
#include "restart button.h"
#include "sound.h"

//=============================================================================
// コンストラクト
//=============================================================================
CPauseButtonManager::CPauseButtonManager()
{
	ZeroMemory(m_pButton, sizeof(m_pButton));
	m_bStick = false;
	m_nButtonSelect = 0;
}

//=============================================================================
// デストラクト
//=============================================================================
CPauseButtonManager::~CPauseButtonManager()
{
}


//=============================================================================
// 生成処理
//=============================================================================
CPauseButtonManager * CPauseButtonManager::Create(void)
{
	CPauseButtonManager* pPauseButtonManager = NULL;
	pPauseButtonManager = new CPauseButtonManager;
	
	//NULLチェック
	if (pPauseButtonManager != NULL)
	{
		//初期化処理
		pPauseButtonManager->Init();
	}
	return pPauseButtonManager;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CPauseButtonManager::Init(void)
{
	//それぞれのボタン生成
	m_pButton[BUTTON_TYPE_START]	= CStartButton::Create(D3DXVECTOR3((float)(SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2) - 150, 0.0f), D3DXVECTOR3(300.0f, 50.0f, 0.0f));
	m_pButton[BUTTON_TYPE_RESTART]	= CRestartButton::Create(D3DXVECTOR3 ((float)(SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), 0.0f), D3DXVECTOR3(300.0f, 50.0f, 0.0f));
	m_pButton[BUTTON_TYPE_END]		= CEndButton::Create(D3DXVECTOR3((float)(SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2) + 150, 0.0f), D3DXVECTOR3(300.0f, 50.0f, 0.0f));;
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CPauseButtonManager::Uninit(void)
{
	for (int nButton = 0; nButton<BUTTON_TYPE_MAX; nButton++)
	{
		if (m_pButton[nButton] != NULL)
		{
			m_pButton[nButton]->Uninit();
			m_pButton[nButton] = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CPauseButtonManager::Update(void)
{
	//アップデート処理
	for (int nButton = 0; nButton < BUTTON_TYPE_MAX; nButton++)
	{
		if (m_pButton[nButton] != NULL)
		{
			m_pButton[nButton]->Update();
		}
	}

	//選択したボタンの処理
	Over();

	//ボタン選択処理
	Select();
}

//=============================================================================
// 描画処理
//=============================================================================
void CPauseButtonManager::Draw(void)
{

}

//=============================================================================
// 選択処理
//=============================================================================
void CPauseButtonManager::Select(void)
{
	//キーボード入力取得
	CInputKeyboard* pInputKey = (CInputKeyboard*)CManager::GetInputKey();

	// コントローラー十字キーの値の取得
	CInputJoyStick* pJoyInput = (CInputJoyStick*)CManager::GetInputController();
	WORD joyCross = CROSS_KEY_NEUTRAL;
	if (pJoyInput != NULL) joyCross = (WORD)pJoyInput->GetJoyStick().rgdwPOV[0];


	//入力がされているか
	if (!m_bStick)
	{
		//スタートボタン選択
		if (joyCross == CROSS_KEY_UP || pInputKey->GetKeyTrigger(DIK_W))
		{
			m_nButtonSelect -= 1;
			m_bStick = true;

			//BGMの再生
			CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_BGM_CHOICE);
		}
		//終了ボタン選択
		if (joyCross == CROSS_KEY_DOWN || pInputKey->GetKeyTrigger(DIK_S))
		{
			m_nButtonSelect += 1;
			m_bStick = true;

			//BGMの再生
			CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_BGM_CHOICE);
		}
	}
	else if(m_bStick)
	{
		if (joyCross == CROSS_KEY_NEUTRAL)
		{
			m_bStick = false;
		}
	}


	//選択肢のループ
	if (m_nButtonSelect>=BUTTON_TYPE_MAX)
	{
		//戻す
		m_nButtonSelect = 0;
	}
	if (m_nButtonSelect<BUTTON_TYPE_START)
	{
		//戻す
		m_nButtonSelect = BUTTON_TYPE_MAX - 1;
	}
}
//=============================================================================
// 選択したボタンの処理
//=============================================================================
void CPauseButtonManager::Over(void)
{
	for (int nButton = 0; nButton < BUTTON_TYPE_MAX; nButton++)
	{
		if (m_pButton[nButton] != NULL)
		{
			//現在の選択しているボタンかどうか
			if (nButton == m_nButtonSelect)
			{
				//選択しているボタン
				m_pButton[nButton]->Over();
			}
			else
			{
				//選択していないボタン
				m_pButton[nButton]->Out();
			}

		}
	}
}
