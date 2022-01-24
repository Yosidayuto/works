//=============================================================================
//
//	ボタンマネージャー[button manager.h]
//	Author:吉田　悠人
//
//=============================================================================
//=============================================================================
//インクルードファイル
//=============================================================================
#include "button manager.h"
#include "renderer.h"
#include "manager.h"
#include "select.h"
#include "button.h"
#include "start button.h"
#include "life button.h"
#include "speed button.h"
#include "bullet button.h"
#include "laser button.h"
#include "homing button.h"
#include "telop.h"
#include "score.h"
//=============================================================================
// コンストラクト
//=============================================================================
CButtonManager::CButtonManager()
{
	ZeroMemory(m_pButton, sizeof(m_pButton));
}

//=============================================================================
// デストラクト
//=============================================================================
CButtonManager::~CButtonManager()
{
}

//=============================================================================
// テクスチャロード処理
//=============================================================================
HRESULT CButtonManager::Load(void)
{
	CStartButton::Load();
	CLifeButton::Load();
	CSpeedButton::Load();
	CBulletButton::Load();
	CLaserButton::Load();
	CHomingButton::Load();
	CButton::Load();
	return S_OK;
}

//=============================================================================
// テクスチャ破棄処理
//=============================================================================
void CButtonManager::Unload(void)
{
	CStartButton::Unload();
	CLifeButton::Unload();
	CSpeedButton::Unload();
	CBulletButton::Unload();
	CLaserButton::Unload();
	CHomingButton::Unload();
	CButton::Unload();
}

//=============================================================================
// 生成処理
//=============================================================================
CButtonManager * CButtonManager::Create(int nStage)
{
	//メモリ確保
	CButtonManager* pButtonManager=NULL;
	pButtonManager = new CButtonManager;
	
	//NULLチェック
	if (pButtonManager != NULL)
	{
		// ステージ番号セット
		pButtonManager->SetStageNumber(nStage);
		//初期化処理
		pButtonManager->Init();
	}
	return pButtonManager;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CButtonManager::Init(void)
{
	m_pButton[BUTTON_TYPE_START]	= CStartButton::Create(D3DXVECTOR3(140, 150, 0.0f), D3DXVECTOR3(270.0f, 35.0f, 0.0f), m_nStageNumber);
	m_pButton[BUTTON_TYPE_LIFE]		= CLifeButton::Create(D3DXVECTOR3(140, 250, 0.0f), D3DXVECTOR3(270.0f, 35.0f, 0.0f));
	m_pButton[BUTTON_TYPE_SPEED]	= CSpeedButton::Create(D3DXVECTOR3(140, 300, 0.0f), D3DXVECTOR3(270.0f, 35.0f, 0.0f));
	m_pButton[BUTTON_TYPE_BUTTOL]	= CBulletButton::Create(D3DXVECTOR3(140, 350, 0.0f), D3DXVECTOR3(270.0f, 35.0f, 0.0f));
	m_pButton[BUTTON_TYPE_LASER]	= CLaserButton::Create(D3DXVECTOR3(140, 400, 0.0f), D3DXVECTOR3(270.0f, 35.0f, 0.0f));
	m_pButton[BUTTON_TYPE_HOMING]	= CHomingButton::Create(D3DXVECTOR3(140, 450, 0.0f), D3DXVECTOR3(270.0f, 35.0f, 0.0f));

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CButtonManager::Uninit(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void CButtonManager::Update(void)
{
	//マウスアウトの処理
	MouseOut();
}

//=============================================================================
// 描画処理
//=============================================================================
void CButtonManager::Draw(void)
{
}

//=============================================================================
// ステージナンバーセッター
//=============================================================================
void CButtonManager::SetStageNumber(int nStage)
{
	m_nStageNumber = nStage;
}

//=============================================================================
// マウスアウトの処理
//=============================================================================
void CButtonManager::MouseOut(void)
{
	//テロップポインタ
	CTelop*		pTelop = CSelect::GetTelop();
	//スコア減少量取得
	CScore*		pMinusScore = CSelect::GetMinusScore();

	//どれかボタンにマウスカーソルが重なっているか
	for (int nCountType = 0; nCountType < BUTTON_TYPE_MAX; nCountType++)
	{
		if (m_pButton[nCountType] != NULL)
		{
			if (m_pButton[nCountType]->Hit())
			{
				//処理を終わる
				return;
			}

		}
	}

	//マウスカーソルが重なっていなかったとき
	if (pTelop != NULL)
	{
		if (pTelop->GetTelopType() != TELOP_TYPE_TUTORIAL)
		{
			//テロップ切替
			pTelop->TypeChange(TELOP_TYPE_TUTORIAL);
		}

	}
	//消費スコアを0に変換
	if (pMinusScore != NULL)
	{
		pMinusScore->SetScore(0);
	}

}
