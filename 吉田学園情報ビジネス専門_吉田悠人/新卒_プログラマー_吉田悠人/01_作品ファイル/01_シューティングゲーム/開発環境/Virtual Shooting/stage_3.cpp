//=============================================================================
//
// ステージ3処理 [stage_3.cpp]
// Author : 吉田悠人
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "stage_3.h"
#include "manager.h"
#include "sound.h"
#include "boss base.h"
#include "boss type1.h"
#include "boss type2.h"
#include "boss type3.h"
#include "warning.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define PHASE_COUNT (200)	//フェーズが位置段階変わるまでのカウント数

//=============================================================================
// コンストラクト
//=============================================================================
CStage3::CStage3()
{
	m_EnemyCreate = ENEMY_CREATE_NULL;
	m_nBossPhase = 0;
	memset(&m_StageData, NULL, sizeof(m_StageData));
}


//=============================================================================
// 生成処理
//=============================================================================
CStage3 * CStage3::Create(void)
{
	//メモリの確保
	CStage3* pStage3 = NULL;
	pStage3 = new CStage3;

	//NULLチェック
	if (pStage3 != NULL)
	{
		//初期化処理
		pStage3->Init();
	}
	return pStage3;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CStage3::Init(void)
{
	//サウンドクラス取得
	CSound *pSound = CManager::GetSound();
	//サウンド再生
	pSound->Play(CSound::LABEL_BGM_STAGE_3);
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CStage3::Uninit(void)
{
	//サウンド取得
	CSound*	pSound = CManager::GetSound();
	//シーン破棄
	CScene::ReleaseAll();
	//サウンド停止
	pSound->Stop();

}


//=============================================================================
// エネミーのスポーンモード
//=============================================================================
void CStage3::StageMode(void)
{
	//サウンドポインタ取得
	CSound *pSound = CManager::GetSound();
	//ステージ進行
	m_EnemyCreate = (STAGE_ENEMY)(m_EnemyCreate + 1);

	//フェーズ処理
	switch (m_EnemyCreate)
	{
	case ENEMY_CREATE_1:
		//ワーニング生成
		CWarning::Create(D3DXVECTOR3(STAGE_POS, SCREEN_HEIGHT / 2, 0.0f));
		break;
	case ENEMY_CREATE_2:
		//ボス生成
		CBossType1::Create(D3DXVECTOR3(STAGE_POS, 100, 0.0f));
		break;
	case ENEMY_CREATE_3:
		//ワーニング生成
		CWarning::Create(D3DXVECTOR3(STAGE_POS, SCREEN_HEIGHT / 2, 0.0f));
		break;
	case ENEMY_CREATE_4:
		//ボス生成
		CBossType2::Create(D3DXVECTOR3(STAGE_POS, 100, 0.0f));
		break;
	case ENEMY_CREATE_5:
		//ボス演出
		WarningCreate();
		break;
	case ENEMY_CREATE_6:
		//サウンド再生
		pSound->Play(CSound::LABEL_BGM_BOSS_3);
		//ボス生成
		CBossType3::Create(D3DXVECTOR3(STAGE_POS, 100, 0.0f));
		break;
	case ENEMY_CREATE_7:
		//リザルト表示
		Result(STAGE_TYPE_3);
		break;
	}
	SetEnemyCount(PHASE_COUNT);
}
