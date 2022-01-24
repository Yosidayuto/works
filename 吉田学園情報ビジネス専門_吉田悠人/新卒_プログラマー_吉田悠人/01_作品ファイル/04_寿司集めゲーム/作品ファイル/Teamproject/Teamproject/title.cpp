//=============================================================================
//
// タイトル処理 [title.cpp]
// Author : 
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "title.h"
#include "sound.h"
#include "joystick.h"
#include "sound.h"
#include "scene2d.h"
#include "keyboard.h"
#include "fade.h"
#include "resource manager.h"
#include "game.h"
#include "result effect.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CTitle::CTitle()
{
	PlayerNum = PLAYER_NONE;
	nPlayer = 1;

	for (int nCount = 0; nCount < MAX_TITLE_TEX; nCount++)
	{
		m_pTitle[nCount] = new CScene2d;
		if (m_pTitle[nCount] != nullptr)
		{
			m_pTitle[nCount]->Init();
		}
	}

	m_pTitle[TEX_TITLE]->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 3, 0.0f));
	m_pTitle[TEX_TITLE]->SetSize(D3DXVECTOR3(SCREEN_WIDTH / 1.5f, SCREEN_HEIGHT / 1.5f, 0.0f));

	m_pTitle[TEX_MODE1]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_pTitle[TEX_MODE1]->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 1.3f, 0.0f));
	m_pTitle[TEX_MODE1]->SetSize(D3DXVECTOR3(500, 100, 0.0f));

	m_pTitle[TEX_MODE2]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
	m_pTitle[TEX_MODE2]->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 1.1f, 0.0f));
	m_pTitle[TEX_MODE2]->SetSize(D3DXVECTOR3(500, 100, 0.0f));

	m_pTitle[TEX_1PLAYER]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	m_pTitle[TEX_1PLAYER]->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 3.0f, SCREEN_HEIGHT / 1.5f, 0.0f));
	m_pTitle[TEX_1PLAYER]->SetSize(D3DXVECTOR3(500, 100, 0.0f));

	m_pTitle[TEX_2PLAYER]->SetColor(D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.0f));
	m_pTitle[TEX_2PLAYER]->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 1.5f, SCREEN_HEIGHT / 1.5f, 0.0f));
	m_pTitle[TEX_2PLAYER]->SetSize(D3DXVECTOR3(500, 100, 0.0f));

	m_pTitle[TEX_3PLAYER]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	m_pTitle[TEX_3PLAYER]->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 3.0f, SCREEN_HEIGHT / 1.2f, 0.0f));
	m_pTitle[TEX_3PLAYER]->SetSize(D3DXVECTOR3(500, 100, 0.0f));

	m_pTitle[TEX_4PLAYER]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	m_pTitle[TEX_4PLAYER]->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 1.5f, SCREEN_HEIGHT / 1.2f, 0.0f));
	m_pTitle[TEX_4PLAYER]->SetSize(D3DXVECTOR3(500, 100, 0.0f));

	CGame::SetGameType(CGame::MODETYPE::MODETYPE_1);
}

//=============================================================================
// デストラクタ
//=============================================================================
CTitle::~CTitle()
{

}

//=============================================================================
// 生成処理
//=============================================================================
CTitle * CTitle::Create(void)
{
	CTitle *pTitle;
	pTitle = new CTitle;

	//リソース確保(リソースマネージャーから呼び出す)
	CResource* pResource = CManager::GetResource();

	for (int nCount = 0; nCount < MAX_TITLE_TEX; nCount++)
	{
		LPDIRECT3DTEXTURE9 TitleTexture = pResource->TextureLoad(pTitle->m_nTexture[nCount]);

		pTitle->m_pTitle[nCount]->BindTexture(TitleTexture);
	}

	if (pTitle != nullptr)
	{
		pTitle->Init();
	}

	return pTitle;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTitle::Init(void)
{
	//オブジェクト生成
	CManager::CreateCamera();
	CManager::CreateLight();
	CResultEffect::Create();
	CSound *pSound = CManager::GetSound();
	pSound->PlaySound(CSound::LABEL_BGM_TITLE);
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CTitle::Uninit(void)
{
}

//=============================================================================
// 更新処理
//=============================================================================
void CTitle::Update(void)
{
	//キーボード入力処理
	KeyControl();
	//コントローラー入力処理
	JoyControl();
}

//=============================================================================
// 描画処理
//=============================================================================
void CTitle::Draw(void)
{
}

//=============================================================================
// キーボード入力処理
//=============================================================================
void CTitle::KeyControl(void)
{
	//キーボードの取得
	CKeyboard * pInputKeyboard = CManager::GetInputKeyboard();

	if (PlayerNum == PLAYER_NONE)
	{
		if (pInputKeyboard->GetKeyTrigger(DIK_UP))
		{
			m_pTitle[TEX_MODE1]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_pTitle[TEX_MODE2]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
			CGame::SetGameType(CGame::MODETYPE::MODETYPE_1);
		}
		else if (pInputKeyboard->GetKeyTrigger(DIK_DOWN))
		{
			m_pTitle[TEX_MODE1]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
			m_pTitle[TEX_MODE2]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			CGame::SetGameType(CGame::MODETYPE::MODETYPE_2);
		}
		if (pInputKeyboard->GetKeyTrigger(DIK_Z))
		{
			m_pTitle[TEX_MODE1]->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
			m_pTitle[TEX_MODE2]->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

			PlayerNum = PLAYER_1;
			m_pTitle[TEX_1PLAYER]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_pTitle[TEX_2PLAYER]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
			m_pTitle[TEX_3PLAYER]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
			m_pTitle[TEX_4PLAYER]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		}
	}
	else
	{
		if (pInputKeyboard->GetKeyTrigger(DIK_UP))
		{
			if (nPlayer == 3 || nPlayer == 4)
			{
				nPlayer += -2;
			}
			else
			{

			}
		}
		else if (pInputKeyboard->GetKeyTrigger(DIK_DOWN))
		{
			if (nPlayer == 1 || nPlayer == 2)
			{
				nPlayer += 2;
			}
			else
			{

			}
		}
		else if (pInputKeyboard->GetKeyTrigger(DIK_LEFT))
		{
			if (nPlayer == 2 || nPlayer == 4)
			{
				nPlayer += -1;
			}
			else
			{

			}
		}
		else if (pInputKeyboard->GetKeyTrigger(DIK_RIGHT))
		{
			if (nPlayer == 1 || nPlayer == 3)
			{
				nPlayer += 1;
			}
			else
			{

			}
		}
		else
		{

		}
		if (nPlayer == 1)
		{
			m_pTitle[TEX_1PLAYER]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_pTitle[TEX_2PLAYER]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
			m_pTitle[TEX_3PLAYER]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
			m_pTitle[TEX_4PLAYER]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		}
		else if (nPlayer == 2)
		{
			m_pTitle[TEX_1PLAYER]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
			m_pTitle[TEX_2PLAYER]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_pTitle[TEX_3PLAYER]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
			m_pTitle[TEX_4PLAYER]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		}
		else if (nPlayer == 3)
		{
			m_pTitle[TEX_1PLAYER]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
			m_pTitle[TEX_2PLAYER]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
			m_pTitle[TEX_3PLAYER]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_pTitle[TEX_4PLAYER]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		}
		else if (nPlayer == 4)
		{
			m_pTitle[TEX_1PLAYER]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
			m_pTitle[TEX_2PLAYER]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
			m_pTitle[TEX_3PLAYER]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
			m_pTitle[TEX_4PLAYER]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else
		{

		}
		if (pInputKeyboard->GetKeyTrigger(DIK_Z))
		{
			CManager::SetPlayerNumber(nPlayer);
			CManager::GetFade()->SetFade(CManager::MODE_TUTORIAL);
		}
	}
}

//=============================================================================
// コントローラー入力処理
//=============================================================================
void CTitle::JoyControl(void)
{
	CJoystick* pJoy = CManager::GetInputJoystick();
	if (PlayerNum == PLAYER_NONE)
	{
		if (pJoy->GetJoyStick(0).lY<-100)
		{
			m_pTitle[TEX_MODE1]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_pTitle[TEX_MODE2]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
			CGame::SetGameType(CGame::MODETYPE::MODETYPE_1);
		}
		else if (pJoy->GetJoyStick(0).lY>100)
		{
			m_pTitle[TEX_MODE1]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
			m_pTitle[TEX_MODE2]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			CGame::SetGameType(CGame::MODETYPE::MODETYPE_2);
		}
		if (pJoy->GetJoystickTrigger(JS_A,0))
		{
			m_pTitle[TEX_MODE1]->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
			m_pTitle[TEX_MODE2]->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

			PlayerNum = PLAYER_1;
			m_pTitle[TEX_1PLAYER]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_pTitle[TEX_2PLAYER]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
			m_pTitle[TEX_3PLAYER]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
			m_pTitle[TEX_4PLAYER]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		}
	}
	else
	{
		if (pJoy->GetJoyStick(0).lY<-100)
		{
			if (nPlayer == 3 || nPlayer == 4)
			{
				nPlayer += -2;
			}
			else
			{

			}
		}
		else if (pJoy->GetJoyStick(0).lY>100)
		{
			if (nPlayer == 1 || nPlayer == 2)
			{
				nPlayer += 2;
			}
			else
			{

			}
		}
		else if (pJoy->GetJoyStick(0).lX<-100)
		{
			if (nPlayer == 2 || nPlayer == 4)
			{
				nPlayer += -1;
			}
			else
			{

			}
		}
		else if (pJoy->GetJoyStick(0).lX>100)
		{
			if (nPlayer == 1 || nPlayer == 3)
			{
				nPlayer += 1;
			}
			else
			{

			}
		}
		else
		{

		}
		if (nPlayer == 1)
		{
			m_pTitle[TEX_1PLAYER]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_pTitle[TEX_2PLAYER]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
			m_pTitle[TEX_3PLAYER]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
			m_pTitle[TEX_4PLAYER]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		}
		else if (nPlayer == 2)
		{
			m_pTitle[TEX_1PLAYER]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
			m_pTitle[TEX_2PLAYER]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_pTitle[TEX_3PLAYER]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
			m_pTitle[TEX_4PLAYER]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		}
		else if (nPlayer == 3)
		{
			m_pTitle[TEX_1PLAYER]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
			m_pTitle[TEX_2PLAYER]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
			m_pTitle[TEX_3PLAYER]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_pTitle[TEX_4PLAYER]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		}
		else if (nPlayer == 4)
		{
			m_pTitle[TEX_1PLAYER]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
			m_pTitle[TEX_2PLAYER]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
			m_pTitle[TEX_3PLAYER]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
			m_pTitle[TEX_4PLAYER]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else
		{

		}
		if (pJoy->GetJoystickTrigger(JS_A, 0))
		{
			CManager::SetPlayerNumber(nPlayer);
			CManager::GetFade()->SetFade(CManager::MODE_TUTORIAL);
		}
	}

}
