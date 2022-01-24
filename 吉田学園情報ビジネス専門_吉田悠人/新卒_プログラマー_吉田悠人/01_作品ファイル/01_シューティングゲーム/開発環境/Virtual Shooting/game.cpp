//=============================================================================
//
// ゲーム処理 [game.cpp]
// Author : 吉田悠人
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "game.h"		
#include "score.h"		
#include "life.h"		
#include "player.h"		
#include "bullet base.h"		
#include "explosion.h"
#include "effect.h"		
#include "fade.h"		
#include "manager.h"	
#include "warning.h"	
#include "result.h"		
#include "sound.h"		
#include "game pointer.h"
#include "boss base.h"
#include "boss effect base.h"
#include "sound.h"
#include "game bg manager.h"
#include "life tank.h"
#include "stage_1.h"
#include "stage_2.h"
#include "stage_3.h"
//=============================================================================
// 静的メンバー変数
//=============================================================================
CScore *CGame::m_Score			= NULL;
CPlayer *CGame::m_pPlayer		= NULL;
STAGE_TYPE CGame::m_StageType	= STAGE_TYPE_1;
//=============================================================================
// コンストラクト
//=============================================================================
CGame::CGame()
{
	m_pPlayer= NULL;
	m_pStage = NULL;
}

//=============================================================================
// デストラクト
//=============================================================================
CGame::~CGame()
{
}

//=============================================================================
// テクスチャロード処理
//=============================================================================
HRESULT CGame::Load(void)
{
	//テクスチャの読み込み
	CPlayer::Load();		
	CExplosion::Load();		
	CEffect::Load();		
	CWarning::Load();		
	CGameBgManager::Load();
	CEnemyBase::Load();
	CBulletBase::Load();
	CBossBase::Load();
	CBossEffectBase::Load();
	CLifeTank::Load();

	return S_OK;
}

//=============================================================================
// テクスチャ破棄処理
//=============================================================================
void CGame::Unload(void)
{
	//テクスチャの破棄
	CPlayer::Unload();		
	CExplosion::Unload();	
	CEffect::Unload();		
	CWarning::Unload();		
	CGameBgManager::Unload();
	CEnemyBase::Unload();
	CBulletBase::Unload();
	CBossBase::Unload();
	CBossEffectBase::Unload();
	CLifeTank::Unload();

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CGame::Init(void)
{
	//サウンドクラス取得
	CSound *pSound = CManager::GetSound();
	//=============================================================================
	//クリエイト処理
	//=============================================================================
	//背景
	m_pGameBgManager = CGameBgManager::Create();
	//プレイヤー生成
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(780, 600, 0.0f));
	//スコア表記
	m_Score	= CScore::Create(D3DXVECTOR3(35,670,0),D3DXVECTOR3(20,45,0.0f),true);
	m_Score->SetScore(CManager::GetScore());
	//マウスポインタ生成
	m_pGamePointer = CGamePointer::Create();

	//ステージ生成
	switch (m_StageType)
	{
	case STAGE_TYPE_1:
		m_pStage = CStage1::Create();
		break;
	case STAGE_TYPE_2:
		m_pStage = CStage2::Create();
		break;
	case STAGE_TYPE_3:
		m_pStage = CStage3::Create();
		break;
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CGame::Uninit(void)
{
	//ステージの初期化
	if (m_StageType > STAGE_TYPE_3)
	{
		m_StageType = STAGE_TYPE_1;
	}

	//シーン破棄
	CScene::ReleaseAll();
}

//=============================================================================
// 更新処理
//=============================================================================
void CGame::Update(void)
{
	if (m_pStage != NULL)
	{
		m_pStage->Update();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CGame::Draw(void)
{
}

//=============================================================================
// スコア取得
//=============================================================================
CScore * CGame::GetScore(void)
{
	return m_Score;
}

//=============================================================================
// ステージゲッター
//=============================================================================
STAGE_TYPE CGame::GetStageType(void)
{
	return m_StageType;
}

//=============================================================================
// ステージセット
//=============================================================================
void CGame::SetStageType(STAGE_TYPE stage)
{
	m_StageType = stage;
}

//=============================================================================
// プレイヤーゲッター
//=============================================================================
CPlayer * CGame::GetPlayer(void)
{
	return m_pPlayer;
}