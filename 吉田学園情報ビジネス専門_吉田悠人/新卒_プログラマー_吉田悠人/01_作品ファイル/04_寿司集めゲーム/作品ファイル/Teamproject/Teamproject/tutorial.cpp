//=============================================================================
//
// タイトル処理 [tutorial.cpp]
// Author : 
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "tutorial.h"
#include "sound.h"
#include "joystick.h"
#include "sound.h"
#include "scene2d.h"
#include "keyboard.h"
#include "fade.h"
#include "resource manager.h"
#include "game.h"
#include "joystick.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CTutorial::CTutorial()
{
	for (int nCount = 0; nCount < MAX_TUTORIAL_TEX; nCount++)
	{
		m_pTutorial[nCount] = new CScene2d;
		if (m_pTutorial[nCount] != nullptr)
		{
			m_pTutorial[nCount]->Init();
		}
	}

	m_pTutorial[TEX_TUTORIAL]->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f));
	m_pTutorial[TEX_TUTORIAL]->SetSize(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
}

//=============================================================================
// デストラクタ
//=============================================================================
CTutorial::~CTutorial()
{

}

//=============================================================================
// 生成処理
//=============================================================================
CTutorial * CTutorial::Create(void)
{
	CTutorial *pTutorial;
	pTutorial = new CTutorial;

	//リソース確保(リソースマネージャーから呼び出す)
	CResource* pResource = CManager::GetResource();

	for (int nCount = 0; nCount < MAX_TUTORIAL_TEX; nCount++)
	{
		LPDIRECT3DTEXTURE9 TitleTexture = pResource->TextureLoad(pTutorial->m_nTexture[nCount]);

		pTutorial->m_pTutorial[nCount]->BindTexture(TitleTexture);
	}

	if (pTutorial != nullptr)
	{
		pTutorial->Init();
	}

	return pTutorial;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTutorial::Init(void)
{
	//オブジェクト生成
	CManager::CreateCamera();
	CManager::CreateLight();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CTutorial::Uninit(void)
{

	CSound *pSound = CManager::GetSound();
	pSound->StopSound(CSound::LABEL_BGM_TITLE);
}

//=============================================================================
// 更新処理
//=============================================================================
void CTutorial::Update(void)
{
	//サウンド
	CSound * pSound = CManager::GetSound();
	//キーボードの取得
	CKeyboard * pInputKeyboard = CManager::GetInputKeyboard();
	CJoystick * pJoy = CManager::GetInputJoystick();

	if (CManager::GetInputKeyboard()->GetKeyTrigger(DIK_Z))
	{
		CManager::GetFade()->SetFade(CManager::MODE_GAME);
	}

	if (pJoy->GetJoystickTrigger(JS_A, 0))
	{
		CManager::GetFade()->SetFade(CManager::MODE_GAME);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CTutorial::Draw(void)
{
}
