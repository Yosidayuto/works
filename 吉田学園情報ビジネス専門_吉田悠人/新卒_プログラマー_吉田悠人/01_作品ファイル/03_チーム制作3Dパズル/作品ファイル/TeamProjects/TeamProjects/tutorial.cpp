//=============================================================================
//
// チュートリアル [tutorial.cpp]
// Author : 鈴木 聖大
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "tutorial.h"
#include "resource manager.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define TUTORIAL_POS (D3DXVECTOR3((SCREEN_WIDTH/2),(SCREEN_HEIGHT/2),0.0f))
#define TUTORIAL_SIZE (D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f))

//=============================================================================
// コンストラクタ
//=============================================================================
CTutorial::CTutorial(int nPriority) :CUi(nPriority)
{
	m_pObject2d = NULL;
}

//=============================================================================
// セリフの生成
//=============================================================================
CTutorial * CTutorial::Create(void)
{
	// メモリの確保
	CTutorial * pTutorial = NULL;
	pTutorial = new CTutorial;
	//リソース確保
	CResource* pResource = CManager::GetResource();
	LPDIRECT3DTEXTURE9 Texture = pResource->TextureLoad(pTutorial->m_nTexture);

	if (pTutorial != NULL)
	{
		// 座標をset
		pTutorial->SetPos(TUTORIAL_POS);
		// サイズをset
		pTutorial->SetSize(TUTORIAL_SIZE);
		// テクスチャ指定
		pTutorial->BindTexture(Texture);
		// 初期化処理
		pTutorial->Init();
	}

	return pTutorial;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTutorial::Init(void)
{
	//背景生成
	m_pObject2d = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0) / 2, D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0), 0.0f, NULL, PRIORITY_UI_3);
	//背景カラー設定
	m_pObject2d->SetCol(D3DCOLOR_RGBA(0, 0, 0, 128));

	CUi::Init();

	//BGMの再生
	CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_BGM_TUTORIAL);

	return S_OK;
}


//=============================================================================
// 更新処理
//=============================================================================
void CTutorial::Update(void)
{
	CUi::Update();

	//背景用オブジェクト更新
	if (m_pObject2d != NULL)
	{
		m_pObject2d->Update();
	}
}

//=============================================================================
// 描画関数
//=============================================================================
void CTutorial::TutorialUninit(void)
{
	if (m_pObject2d != NULL)
	{
		m_pObject2d->Uninit();
	}
	Uninit();
}
