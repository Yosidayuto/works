//=============================================================================
//
// 武装UI処理 [weapons_ui.cpp]
// Author : 吉田悠人
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "weapons_ui.h"
#include "manager.h"
#include "renderer.h"
#include "billboard.h"
#include "manager.h"

//*****************************************************************************
//　マクロ定義
//*****************************************************************************
#define SIZE_X (250.0f)
#define SIZE_Y (150.0f)

//*****************************************************************************
//　静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CWeapons_ui::m_pTexture[WEAPONS_TEXTURE_MAX] = {};
char *CWeapons_ui::m_cFileName[WEAPONS_TEXTURE_MAX]=
{
	WEAPONS_UI_AR_TEXTURE,
	WEAPONS_UI_HG_TEXTURE
};

//=============================================================================
// コンストラクタ
//=============================================================================
CWeapons_ui::CWeapons_ui() : CObject2D(2)
{
	nCountCol = 0;
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CWeapons_ui::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの生成
	for (int nTexture=0;nTexture<WEAPONS_TEXTURE_MAX;nTexture++)
	{
		D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
			m_cFileName[nTexture],						// ファイルの名前
			&m_pTexture[nTexture]);						// 読み込むメモリー

	}
	return S_OK;
}

//=============================================================================
// テクスチャ破棄関数
//=============================================================================
void CWeapons_ui::Unload(void)
{
	// テクスチャの破棄
	for (int nTexture = 0; nTexture < WEAPONS_TEXTURE_MAX; nTexture++)
	{
		if (m_pTexture[nTexture] != NULL)
		{
			m_pTexture[nTexture]->Release();
			m_pTexture[nTexture] = NULL;
		}

	}
}

//=============================================================================
// 生成関数
//=============================================================================
CWeapons_ui * CWeapons_ui::Create(void)
{
	//メモリの確保
	CWeapons_ui* pWeaponsUi = NULL;
	pWeaponsUi = new CWeapons_ui;
	
	//NULLチェック
	if (pWeaponsUi!=NULL)
	{
		//位置設定
		pWeaponsUi->SetPos(D3DXVECTOR3(SCREEN_WIDTH - (SIZE_X / 2), SCREEN_HEIGHT - (SIZE_Y + 25), 0));
		//向き設定
		pWeaponsUi->SetRot(0.0f);
		//サイズ設定
		pWeaponsUi->SetSize(D3DXVECTOR3(SIZE_X, SIZE_Y, 0));
		//カラー設定
		pWeaponsUi->SetCol(D3DCOLOR_RGBA(255, 255, 255, 255));
		//テクスチャ設定
		pWeaponsUi->BindTexture(m_pTexture[CManager::GetWeaponsMode()]);
		//初期化処理
		pWeaponsUi->Init();
	}

	return pWeaponsUi;
}

//=============================================================================
// 更新処理
//=============================================================================
void CWeapons_ui::Update(void)
{
	//更新処理
	CObject2D::Update();
	
	//カラー変更用数値が0より大きかったら
	if (nCountCol >= 0)
	{
		nCountCol--;
	}
	//カラー変更用数値が0だと
	if (nCountCol == 0)
	{
		SetCol(D3DCOLOR_RGBA(255, 255, 255, 255));
	}
}

//=============================================================================
// 光る関数
//=============================================================================
void CWeapons_ui::Gleams(void)
{
	//カラー変更用数値
	nCountCol = 5;
	//カラー変更
	SetCol(D3DCOLOR_RGBA(255, 241, 86, 255));
}
