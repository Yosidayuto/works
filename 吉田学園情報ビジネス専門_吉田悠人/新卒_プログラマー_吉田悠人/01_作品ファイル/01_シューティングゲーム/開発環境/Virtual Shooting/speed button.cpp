//=============================================================================
//
//	スピードボタン[speed button.cpp]
//	Author:吉田　悠人
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "speed button.h"
#include "renderer.h"
#include "manager.h"
#include "score.h"
#include "select.h"
#include "sound.h"
#include "player data.h"
#include "ui count.h"
#include "telop.h"
//=============================================================================
// 静的メンバー変数
//=============================================================================
TEXTURE_DATA CSpeedButton::m_TextureData = { NULL,	"data/TEXTURE/Text_Speed.png", };
int CSpeedButton::m_nScoreCount[PLAYER_LIFE_UP] =
{
	4000,
	5000,
	6000,
	7000,
	8000,
};
//=============================================================================
// コンストラクタ
//=============================================================================
CSpeedButton::CSpeedButton(int nPriorit) :CButton(nPriorit)
{
	m_SpeedCount = 0;
}

//=============================================================================
// テクスチャ読み込み
//=============================================================================
HRESULT CSpeedButton::Load(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		m_TextureData.m_cFileName,
		&m_TextureData.m_Texture);

	return S_OK;
}

//=============================================================================
// テクスチャの破棄
//=============================================================================
void CSpeedButton::Unload(void)
{
	//テクスチャの破棄
	if (m_TextureData.m_Texture != NULL)
	{
		m_TextureData.m_Texture->Release();
		m_TextureData.m_Texture = NULL;
	}
}

//=============================================================================
// 生成処理
//=============================================================================
CSpeedButton * CSpeedButton::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//メモリ確保
	CSpeedButton *pLifeButton = NULL;
	pLifeButton = new CSpeedButton;

	//NULLチェック
	if (pLifeButton != NULL)
	{
		//位置設定
		pLifeButton->SetPos(D3DXVECTOR3(pos.x, pos.y, pos.z));
		//サイズ設定
		pLifeButton->SetSize(D3DXVECTOR3(size.x, size.y, size.z));
		//テクスチャ設定
		pLifeButton->BindTexture(m_TextureData.m_Texture);
		//初期化処理
		pLifeButton->Init();

	}
	return pLifeButton;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CSpeedButton::Init(void)
{
	//ボタンの初期化処理
	CButton::Init();
	//位置設定
	SetPos(D3DXVECTOR3(GetPos().x + 85, GetPos().y, 0.0f));
	//強化回数
	m_SpeedCount = (int)(CManager::GetPlayer()->GetSpeedData());

	return S_OK;
}


//=============================================================================
// マウスオーバー判定
//=============================================================================
void CSpeedButton::MouseOver(void)
{
	//スコア減少量取得
	CScore*		pMinusScore = CSelect::GetMinusScore();
	//テロップポインタ
	CTelop*		pTelop = CSelect::GetTelop();

	//消費スコア表示
	if (CManager::GetPlayer()->GetSpeedData() <= PLAYER_SPEED_UP)
	{
		//消費スコア反映
		pMinusScore->SetScore(m_nScoreCount[m_SpeedCount]);
	}
	//テロップ切替
	if (pTelop->GetTelopType() != TELOP_TYPE_SPEEDUP)
	{
		pTelop->TypeChange(TELOP_TYPE_SPEEDUP);
	}
}

//=============================================================================
// プッシュ判定処理
//=============================================================================
void CSpeedButton::Push(void)
{
	//マウスポインタ取得
	CInihMouse* pMouse		= CManager::GetMouse();
	//スコア
	CScore*		Score		= CSelect::GetScore();
	//ライフ強化数値用ナンバー取得
	CUiCount*	pNumber		= CSelect::GetNumber(CSelect::NUMBER_TYPE_SPEED);


	//左クリック
	if (pMouse->GetClickTrigger(CLICK_LEFT) == true)
	{
		//スピードアップ処理
		if (SpeedUp())
		{
			//スピードカウンターに反映
			pNumber->SetCount(m_SpeedCount + 1);
			//スコアの減少
			Score->AddScore(-m_nScoreCount[m_SpeedCount]);
			//強化回数設定
			m_SpeedCount = (int)(CManager::GetPlayer()->GetSpeedData());
		}
	}
	//右クリック
	else if (pMouse->GetClickTrigger(CLICK_RIGHT) == true)
	{
		//スピードダウン処理
		if (SpeedDown())
		{
			//スピードカウンターに反映
			pNumber->SetCount(m_SpeedCount - 1);
			//スコアの加算
			Score->AddScore(m_nScoreCount[m_SpeedCount - 1]);
			//強化回数設定
			m_SpeedCount = (int)(CManager::GetPlayer()->GetSpeedData());

		}
	}
}

//=============================================================================
// スピード強化処理
//=============================================================================
bool CSpeedButton::SpeedUp(void)
{
	//サウンド取得
	CSound*		pSound = CManager::GetSound();
	//取得スコアデータ取得
	int			nScore = CSelect::GetScore()->GetScore();
	// スピード取得
	float		fSpeed = CManager::GetPlayer()->GetSpeedData();
	//スピードアップできたか
	bool		bSpeedUp = false;

	// スピードが最大強化されているか
	if (fSpeed<PLAYER_SPEED_UP
		&& nScore>m_nScoreCount[m_SpeedCount])
	{
		//クリック音SE
		pSound->Play(CSound::LABEL_SE_CLICK);
		//スピードアップ
		fSpeed++;
		//プレイヤーデータに反映
		CManager::GetPlayer()->SetSpeedData(fSpeed);
		//ライフアップ
		bSpeedUp = true;
	}
	return bSpeedUp;
}

//=============================================================================
// スピード減少処理
//=============================================================================
bool CSpeedButton::SpeedDown(void)
{	//サウンド取得
	CSound*		pSound = CManager::GetSound();
	//スピード取得
	float		fSpeed = CManager::GetPlayer()->GetSpeedData();
	//ライフダウンできたか
	bool		bSpeedDown = false;
	if (fSpeed>0.0f)
	{
		//クリック音SE
		pSound->Play(CSound::LABEL_SE_CANCEL);
		//ライフダウン
		fSpeed--;
		//プレイヤーデータに反映
		CManager::GetPlayer()->SetSpeedData(fSpeed);
		//ライフダウン
		bSpeedDown = true;
	}
	return bSpeedDown;
}
