//=============================================================================
//
//	ライフボタン[life button.cpp]
//	Author:吉田　悠人
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "life button.h"
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
TEXTURE_DATA CLifeButton::m_TextureData = { NULL,	"data/TEXTURE/Text_Life.png", };
int CLifeButton::m_nScoreCount[PLAYER_LIFE_UP]=
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
CLifeButton::CLifeButton(int nPriorit) :CButton(nPriorit)
{
	m_LifeCount = 0;
}


//=============================================================================
// テクスチャ読み込み
//=============================================================================
HRESULT CLifeButton::Load(void)
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
void CLifeButton::Unload(void)
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
CLifeButton * CLifeButton::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//メモリ確保
	CLifeButton *pLifeButton = NULL;
	pLifeButton = new CLifeButton;

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
HRESULT CLifeButton::Init(void)
{
	//ボタンの初期化処理
	CButton::Init();
	//位置設定
	SetPos(D3DXVECTOR3(GetPos().x + 85, GetPos().y, 0.0f));
	//強化回数
	m_LifeCount = CManager::GetPlayer()->GetLifeData();

	return S_OK;
}

//=============================================================================
// マウスオーバー判定
//=============================================================================
void CLifeButton::MouseOver(void)
{
	//スコア減少量取得
	CScore*		pMinusScore = CSelect::GetMinusScore();
	//テロップポインタ
	CTelop*		pTelop = CSelect::GetTelop();
	
	//消費スコア表示
	if (CManager::GetPlayer()->GetLifeData() <= PLAYER_LIFE_UP)
	{
		pMinusScore->SetScore(m_nScoreCount[m_LifeCount]);
	}

	//テロップ切替
	if (pTelop->GetTelopType() != TELOP_TYPE_LIFEUP)
	{
		pTelop->TypeChange(TELOP_TYPE_LIFEUP);
	}
}

//=============================================================================
// プッシュ判定処理
//=============================================================================
void CLifeButton::Push(void)
{
	//マウスポインタ取得
	CInihMouse* pMouse		= CManager::GetMouse();
	//スコア
	CScore*		Score		= CSelect::GetScore();
	//ライフ強化数値用ナンバー取得
	CUiCount*	pNumber		= CSelect::GetNumber(CSelect::NUMBER_TYPE_LIEF);
	
	//左クリック
	if (pMouse->GetClickTrigger(CLICK_LEFT) == true)
	{
		//ライフアップ処理
		if (LifeUp())
		{
			//ライフカウンターに反映
			pNumber->SetCount(m_LifeCount + 1);
			//スコアの減少
			Score->AddScore(-m_nScoreCount[m_LifeCount]);
			//強化回数設定
			m_LifeCount = CManager::GetPlayer()->GetLifeData();
		}
	}
	//右クリック
	else if (pMouse->GetClickTrigger(CLICK_RIGHT) == true)
	{
		//ライフダウン処理
		if (LifeDown())
		{
			//ライフカウンターに反映
			pNumber->SetCount(m_LifeCount-1);
			//スコアの加算
			Score->AddScore(m_nScoreCount[m_LifeCount-1]);
			//強化回数設定
			m_LifeCount = CManager::GetPlayer()->GetLifeData();

		}
	}



}

//=============================================================================
// ライフ強化処理
//=============================================================================
bool CLifeButton::LifeUp(void)
{
	//サウンド取得
	CSound*		pSound = CManager::GetSound();
	//取得スコアデータ取得
	int			nScore = CSelect::GetScore()->GetScore();
	// ライフ取得
	int			nLife = CManager::GetPlayer()->GetLifeData();
	//ライフアップできたか
	bool		bLifeUp = false;

	// ライフが最大強化されているか
	if (nLife<PLAYER_LIFE_UP
		&& nScore>m_nScoreCount[m_LifeCount])
	{
		//クリック音SE
		pSound->Play(CSound::LABEL_SE_CLICK);
		//ライフアップ
		nLife++;
		//プレイヤーデータに反映
		CManager::GetPlayer()->SetLifeData(nLife);
		//ライフアップ
		bLifeUp = true;
	}
	return bLifeUp;
}

//=============================================================================
// ライフ減少処理
//=============================================================================
bool CLifeButton::LifeDown(void)
{	//サウンド取得
	CSound*		pSound = CManager::GetSound();
	// ライフ取得
	int			nLife = CManager::GetPlayer()->GetLifeData();
	//ライフダウンできたか
	bool		bLifeDown = false;
	// ライフが一度でも強化されているか
	if (nLife>0)
	{
		//クリック音SE
		pSound->Play(CSound::LABEL_SE_CANCEL);
		//ライフダウン
		nLife--;
		//プレイヤーデータに反映
		CManager::GetPlayer()->SetLifeData(nLife);
		//ライフダウン
		bLifeDown = true;
	}
	return bLifeDown;
}
