//=============================================================================
//
// タイトル [title.cpp]
// Author : 吉田悠人
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "title.h"
#include "manager.h"
#include "object.h"
#include "camera.h"
#include "inputkeyboard.h"
#include "inputcontroller.h"
#include "fade.h"
#include "stage1.h"
#include "sound.h"
#include "title logo.h"
#include "sea.h"
#include "press button ui.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define TITLE_LOGO_POS_X	(SCREEN_WIDTH / 2)	// ロゴのX位置
#define TITLE_LOGO_POS_Y	(280.0f)			// ロゴのY位置		
#define TITLE_LOGO_SIZE_X	(1400.0f)			// ロゴのXサイズ
#define TITLE_LOGO_SIZE_Y	(680.0f)			// ロゴのYサイズ
//=============================================================================
// コンストラクタ
//=============================================================================
CTitle::CTitle()
{
	m_pStage	 = NULL;
	m_pCamera	 = NULL;
	m_pTitleLoge = NULL;
	m_bFlag		 = false;
}
//=============================================================================
// デストラクタ
//=============================================================================
CTitle::~CTitle()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTitle::Init(void)
{
	// 海の生成
	CSea::Create(D3DXVECTOR3(0.0f, -70.0f, 0.0f), 0.002f, CSea::TYPE_NORMAL);
	CSea::Create(D3DXVECTOR3(0.0f, -60.0f, 0.0f), 0.005f, CSea::TYPE_NORMAL);
	CSea::Create(D3DXVECTOR3(0.0f, -50.0f, 0.0f), 0.008f, CSea::TYPE_NORMAL);

	//カメラのメモリ確保
	m_pCamera = new CCamera;

	//カメラの初期化処理
	if (m_pCamera != NULL)
	{
		m_pCamera->Init(D3DXVECTOR3(-275, 0.0f, 300.0f));
	}

	//タイトルロゴ生成
	m_pTitleLoge = CTitleLoge::Create(D3DXVECTOR3(TITLE_LOGO_POS_X, TITLE_LOGO_POS_Y,0.0f), D3DXVECTOR3(TITLE_LOGO_SIZE_X, TITLE_LOGO_SIZE_Y, 0.0f));

	//フェードをしていない
	m_bFlag = false;

	//ボタンUI
	CPressUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 600.0f, 0.0f), D3DXVECTOR3(500.0f, 100.0f, 0.0f));


	//ステージのメモリ確保
	m_pStage = new CStage1;
	//ステージの初期化処理
	if (m_pStage != NULL)
	{
		m_pStage->TitleMapCreate();
	}

	//BGMの再生
	CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_BGM_TITLE);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CTitle::Uninit(void)
{
	//カメラ終了
	if (m_pCamera != NULL)
	{
		delete m_pCamera;
		m_pCamera = NULL;
	}

	//BGMの終了
	CManager::GetSound()->StopSound(CSound::SOUND_LABEL_BGM_TITLE);

	CObject::ReleaseAll();
}


//=============================================================================
// 描画関数
//=============================================================================
void CTitle::Draw(void)
{
	if (m_pCamera != NULL)
	{
		m_pCamera->SetCamera();
	}
}


//=============================================================================
// 更新処理
//=============================================================================
void CTitle::Update(void)
{
	//カメラの更新
	if (m_pCamera != NULL)
	{
		m_pCamera->TitleMove();
		m_pCamera->Update();
	}

	//キーボード入力の取得
	CInputKeyboard* pInput = (CInputKeyboard*)CManager::GetInputKey();
	//フェードのポインタ取得
	CFade* pBlackout = CManager::GetFadeout();
	//コントローラー入力取得
	CInputJoyStick* pJoyInput = (CInputJoyStick*)CManager::GetInputController();
	//入力確認スイッチ
	bool bJoyStick = false;
	//コントローラー入力確認
	if (pJoyInput != NULL)
	{
		if (pJoyInput->GetJoyStickTrigger(CInputJoyStick::JOY_BUTTON_START)) bJoyStick = true;

	}

	//フェードをしているか&フェード状況
	if (m_bFlag == false && pBlackout->GetFade() <= CFade::FADE_NONE)
	{
		//ボタンを押されたか
		if (pInput->GetKeyTrigger(DIK_RETURN)|| bJoyStick)
		{
			//フェードをしている
			m_bFlag = true;

			//シーン移動処理
			pBlackout->SetBlackout(CManager::MODE_GAME);

			//BGMの再生
			CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_BGM_DECISION);
		}
	}
}