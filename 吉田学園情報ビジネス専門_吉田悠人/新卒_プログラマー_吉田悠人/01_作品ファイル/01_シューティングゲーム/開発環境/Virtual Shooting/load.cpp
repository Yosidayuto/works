//=============================================================================
//
// ロード画面処理 [load.cpp]
// Author : 吉田悠人
//
//=============================================================================
//=============================================================================
//インクルードファイル
//=============================================================================
#include "load.h"
#include "renderer.h"
#include "sound.h"
#include "manager.h"
#include "load bg.h"
#include "clear.h"
#include "number.h"
#include "telop.h"
#include "mouse pointer.h"
#include "title bg.h"
#include "tutorial bg.h"
#include "select bg.h"
#include "life ui.h"
#include "weapon manager.h"
#include "button manager.h"
#include "result bg.h"
#include "score bar.h"
#include "stage.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CLoad::CLoad()
{
	m_bLoad = false;
	m_pLoadBg = NULL;
	nLoad = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CLoad::~CLoad()
{

}

//=============================================================================
// テクスチャロード処理
//=============================================================================
HRESULT CLoad::Load(void)
{
	CLoadBg::Load();
	return S_OK;
}

//=============================================================================
// テクスチャ破棄処理
//=============================================================================
void CLoad::Unload(void)
{
	CLoadBg::Unload();
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CLoad::Init(void)
{
	//サウンド取得
	CSound*	pSound = CManager::GetSound();
	//サウンド再生
	pSound->Play(CSound::LABEL_BGM_LOAD);
	//背景生成
	m_pLoadBg = CLoadBg::Create();

	//ファイルロード(マルチスレッド)
	m_stLoad = std::thread (&CLoad::FileLoad, this);

	m_stLoad.detach();
	//ここまで
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CLoad::Uninit(void)
{
	//シーン破棄
	CScene::ReleaseAll();
}

//=============================================================================
// 更新処理
//=============================================================================
bool CLoad::GetLoad(void)
{
	return m_bLoad;
}

//=============================================================================
// ファイルロード処理
//=============================================================================
void CLoad::FileLoad(void)
{
	//ロード処理をしていないか
	while (!m_bLoad)
	{
		//ロード開始
		File();
	}
}

//=============================================================================
// ファイル読み込み処理
//=============================================================================
void CLoad::File(void)
{
	switch (nLoad)
	{
	case 0:
		CClear::Load();
		break;
	case 1:
		CNumber::Load();
		break;
	case 2:
		CTelop::Load();
		break;
	case 3:
		CPointer::Load();
		break;
	case 4:
		CTitleBg::Load();
		break;
	case 5:
		CTutorialBg::Load();
		break;
	case 6:
		CSelectBg::Load();
		break;
	case 7:
		CLifeUi::Load();
		break;
	case 8:
		CWeaponManager::Load();
		break;
	case 9:
		CButtonManager::Load();
		break;
	case 10:
		CGame::Load();
		break;
	case 11:
		CResultBg::Load();
		break;
	case 12:
		CScoreBar::Load();
		break;
	case 13:
		CStage::LoadEnemyData();
		//読み終えたか
		m_bLoad = true;
		break;
	}
	nLoad++;
}
