//====================================================
//
// tutorialの処理[tutorial.cpp]
// Author:伊藤陽梧
//
//====================================================

//=============================
// インクルード
//=============================
#include "titleback_ui.h"
#include "manager.h"
#include "renderer.h"
#include "polygon.h"
#include "keyboard.h"
#include "joypad.h"
#include "resource_texture.h"
#include "fade.h"

//=============================
// マクロ定義
//=============================
#define TEXTURE_SIZE (D3DXVECTOR3(805.0f / 2.0f, 66.0f / 2.0f, 0.0f))	// タイトル戻る用のテクスチャのサイズ
#define TEXTURE_POS (D3DXVECTOR3(SCREEN_WIDTH - (TEXTURE_SIZE.x / 2.0f), SCREEN_HEIGHT - (TEXTURE_SIZE.y / 2.0f), 0.0f))	// タイトル戻る用のテクスチャの座標
#define ALPHACHANGE_FLOAT (0.005f)	// α値を変える値

//=============================
// コンストラクタ
//=============================
CTitlebackui::CTitlebackui()
{
	m_pTitlebackTex = nullptr;
	m_fAlpha = 0.0f;
	m_bAlphaChange = false;
}

//=============================
// デストラクタ
//=============================
CTitlebackui::~CTitlebackui()
{
}

//=============================
// クリエイト
//=============================
CTitlebackui * CTitlebackui::Create()
{
	// メモリの確保
	CTitlebackui *pTitlebackui = new CTitlebackui;

	// 初期化
	pTitlebackui->Init();

	// 一時的にプライオリティーをUIにする
	pTitlebackui->SetPriority(OBJTYPE_UI_2);
	return pTitlebackui;
}

//=============================
// 初期化処理
//=============================
HRESULT CTitlebackui::Init()
{
	m_pTitlebackTex = CPolygon::Create(TEXTURE_POS, TEXTURE_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	m_pTitlebackTex->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_TITLEBACK));
	return S_OK;
}

//=============================
// 終了処理
//=============================
void CTitlebackui::Uninit()
{
}

//=============================
// 更新処理
//=============================
void CTitlebackui::Update()
{
	if (m_pTitlebackTex)
	{
		// α値を変える
		m_pTitlebackTex->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fAlpha));
	}

	// 正負によってα値を変える
	if (!m_bAlphaChange)
	{
		m_fAlpha += ALPHACHANGE_FLOAT;
	}
	else
	{
		m_fAlpha -= ALPHACHANGE_FLOAT;
	}

	if (m_fAlpha >= 1.0f)
	{
		m_bAlphaChange = true;
	}
	else if (m_fAlpha <= 0.0f)
	{
		m_bAlphaChange = false;
	}

	// ジョイパッドの取得
	CInputJoypad* pJoypad = CManager::GetJoypad();

	for (int nCount = 0; nCount < XUSER_MAX_COUNT; nCount++)
	{
		if (pJoypad->GetButtonState(XINPUT_GAMEPAD_BACK, CInputJoypad::BUTTON_TRIGGER, nCount))
		{
			CManager::GetFade()->SetFade(CManager::MODE_TITLE);
		}
	}
}

//=============================
// 描画処理
//=============================
void CTitlebackui::Draw()
{
	if (m_pTitlebackTex)
	{
		m_pTitlebackTex->Draw();
	}
}