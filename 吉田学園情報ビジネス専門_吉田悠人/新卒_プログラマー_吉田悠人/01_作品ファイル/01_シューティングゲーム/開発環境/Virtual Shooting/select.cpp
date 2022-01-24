//=============================================================================
//
// セレクト処理 [select.cpp]
// Author : 吉田 悠人
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "select.h"		
#include "select bg.h"	
#include "fade.h"
#include "sound.h"
#include "inputmouse.h"
#include "select pointer.h"
#include "player data.h"
#include "button manager.h"
#include "ui count.h"
#include "telop.h"	
#include "weapon manager.h"
#include "score.h"		
//----------------------------------
//静的メンバー変数
//----------------------------------
CScore * CSelect::m_pScore = NULL;
CScore * CSelect::m_pMinusScore = NULL;
CTelop * CSelect::m_pTelop = NULL;
CUiCount *CSelect::Number[MAX_NUMBER]=
{
	NULL,NULL
};

//=============================================================================
// コンストラクタ
//=============================================================================
CSelect::CSelect()
{
	ZeroMemory(Number, sizeof(Number));
	m_pTelop		= NULL;
	m_pMinusScore	= NULL;
	m_nStage		= 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CSelect::~CSelect()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CSelect::Init(void)
{
	CSound*	pSound = CManager::GetSound();	//サウンド取得
	//サウンド再生
	pSound->Play(CSound::LABEL_BGM_SELECT);

	//追加マウスカーソル非表示
	ShowCursor(false);
	//クリエイト処理
	//ボタン生成
	m_pButtonManager = CButtonManager::Create(m_nStage);
	//ウェポンアイコン
	m_pWeaponManager = CWeaponManager::Create(D3DXVECTOR3(1000, 400, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f));
	//テロップ生成
	m_pTelop = CTelop::Create(D3DXVECTOR3(SCREEN_WIDTH - 425, 25, 0.0f), D3DXVECTOR3(850, 50, 0.0f));
	//背景生成
	m_pSelectBg = CSelectBg::Create();
	//スコア
	m_pScore = CScore::Create(D3DXVECTOR3(35.0f, 585.0f, 0.0f), D3DXVECTOR3(25.0f, 35.0f, 0.0f), true);
	m_pScore->AddScore(CManager::GetScore());
	//マイナススコア
	m_pMinusScore = CScore::Create(D3DXVECTOR3(35.0f, 500.0f, 0.0f), D3DXVECTOR3(25.0f, 35.0f, 0.0f), true);
	m_pMinusScore->ColChange(D3DXCOLOR(1.0f,0.0f,0.0f,1.0f));
	//マウスポインタ
	m_pSelectPointer = CSelectPointer::Create();

	//ナンバーセット
	Number[NUMBER_TYPE_LIEF] = CUiCount::Create(D3DXVECTOR3(580.0f, 225.0f, 0.0f), D3DXVECTOR3(25.0f, 50.0f, 0.0f));
	Number[NUMBER_TYPE_LIEF]->SetCount(CManager::GetPlayer()->GetLifeData());
	Number[NUMBER_TYPE_SPEED] = CUiCount::Create(D3DXVECTOR3(580.0f, 465.0f, 0.0f), D3DXVECTOR3(25.0f, 50.0f, 0.0f));
	Number[NUMBER_TYPE_SPEED]->SetCount(((int)(CManager::GetPlayer()->GetSpeedData())));

	return S_OK;

}

//=============================================================================
// 終了処理
//=============================================================================
void CSelect::Uninit(void)
{
	//シーン破棄
	CScene::ReleaseAll();
}

//=============================================================================
// 更新処理
//=============================================================================
void CSelect::Update(void)
{

}

//=============================================================================
// 描画関数
//=============================================================================
void CSelect::Draw(void)
{
}

//=============================================================================
// ステージナンバーセッター
//=============================================================================
void CSelect::SetStage(int nStage)
{
	m_nStage = nStage;
}

//=============================================================================
// ナンバーゲッター
//=============================================================================
CUiCount * CSelect::GetNumber(NUMBER_TYPE NumberType)
{
	return Number[NumberType];
}

//=============================================================================
// スコアゲッターゲッター
//=============================================================================
CScore * CSelect::GetScore(void)
{
	return m_pScore;
}

//=============================================================================
//　マイナススコアゲッター
//=============================================================================
CScore * CSelect::GetMinusScore(void)
{
	return m_pMinusScore;
}

//=============================================================================
// テロップゲッター
//=============================================================================
CTelop * CSelect::GetTelop(void)
{
	return m_pTelop;
}


