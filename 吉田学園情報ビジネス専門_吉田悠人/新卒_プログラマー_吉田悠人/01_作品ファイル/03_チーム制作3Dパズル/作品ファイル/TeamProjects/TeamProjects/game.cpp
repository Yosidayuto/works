//=============================================================================
//
// ゲーム [game.cpp]
// Author : 吉田悠人
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "game.h"
#include "manager.h"
#include "object.h"
#include "camera.h"
#include "fade.h"
#include "inputkeyboard.h"
#include "stage1.h"
#include "stage2.h"
#include "stage3.h"
#include "sound.h"
#include "inputkeyboard.h"
#include "pause.h"

//=============================================================================
//静的メンバ変数宣言
//=============================================================================
CGame::MAP_TYPE CGame::m_MapMode = MAP_TYPE_1;
CStageBase* CGame::m_pStage_1	 = NULL;
CStageBase* CGame::m_pStage_2	 = NULL;
CStageBase* CGame::m_pStage_3 	 = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CGame::CGame()
{
	m_pCamera		= NULL;
	m_pTalk			= NULL;
	m_pStageNumber	= NULL;
}
//=============================================================================
// デストラクタ
//=============================================================================
CGame::~CGame()
{
}

//=============================================================================
// 初期化処理
//=============================================================================

HRESULT CGame::Init(void)
{
	m_pCamera = new CCamera;
	//カメラ初期化処理
	m_pCamera->Init(D3DXVECTOR3(-200.0f, 0.0f, 200.0f));
	//カメラ位置セット
	m_pCamera->SetCamera();

	//オブジェクト生成
	m_pStage_1 = new CStage1;
	m_pStage_2 = new CStage2;
	m_pStage_3 = new CStage3;

	m_MapMode = MAP_TYPE_1;
	SetMapMode(m_MapMode);
	return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void CGame::Update(void)
{
	if (m_pCamera != NULL)
	{
		m_pCamera->Update();
	}
	switch (m_MapMode)
	{
	case MAP_TYPE_1:
		if (m_pStage_1 != NULL)
		{
			m_pStage_1->Update();
		}
		break;
	case MAP_TYPE_2:
		if (m_pStage_2 != NULL)
		{
			m_pStage_2->Update();
		}

		break;
	case MAP_TYPE_3:
		if (m_pStage_3 != NULL)
		{
			m_pStage_3->Update();
		}

		break;
	}
}

//=============================================================================
// 描画関数
//=============================================================================
void CGame::Draw(void)
{
	if (m_pCamera != NULL)
	{
		m_pCamera->SetCamera();
	}

	//モード処理
	switch (m_MapMode)
	{
	case MAP_TYPE_1:
		if (m_pStage_1 != NULL)
		{
			m_pStage_1->Draw();
		}
		break;
	case MAP_TYPE_2:
		if (m_pStage_2 != NULL)
		{
			m_pStage_2->Draw();
		}

		break;
	case MAP_TYPE_3:
		if (m_pStage_3 != NULL)
		{
			m_pStage_3->Draw();
		}

		break;
	}

}

//=============================================================================
// 終了処理
//=============================================================================
void CGame::Uninit(void)
{
	CManager::GetSound()->StopSound();

	CObject::ReleaseAll();
}

//=============================================================================
// マップモードセッター処理
//=============================================================================
void CGame::SetMapMode(MAP_TYPE MapMode)
{
	//ポーズ取得
	CPause* pPause = CManager::GetPause();
	
	//NULLチェック
	if (pPause != NULL)
	{
		//ポーズ終了
		pPause->Delete();
	}

	//終了処理
	switch (m_MapMode)
	{
	case MAP_TYPE_1:	//ステージ1
		if (m_pStage_1 != NULL)
		{
			m_pStage_1->Uninit();
		}
		break;
	case MAP_TYPE_2:	//ステージ2
		if (m_pStage_2 != NULL)
		{
			m_pStage_2->Uninit();
		}
		break;
	case MAP_TYPE_3:	//ステージ3
		if (m_pStage_3 != NULL)
		{
			m_pStage_3->Uninit();
		}
		break;
	}

	//モード切替
	m_MapMode = MapMode;

	//初期化処理
	switch (m_MapMode)
	{
	case MAP_TYPE_1:	//ステージ1
		if (m_pStage_1 != NULL)
		{
			m_pStage_1->Init();

		}
		break;
	case MAP_TYPE_2:	//ステージ2
		if (m_pStage_2 != NULL)
		{
			m_pStage_2->Init();

		}
		break;
	case MAP_TYPE_3:	//ステージ3
		if (m_pStage_3 != NULL)
		{
			m_pStage_3->Init();

		}
		break;

	}

}

//=============================================================================
// マップモードゲッター処理
//=============================================================================
CGame::MAP_TYPE CGame::GetMapMode(void)
{
	return m_MapMode;
}
