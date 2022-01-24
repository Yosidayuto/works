//=============================================================================
//
//	スタートボタン[start button.cpp]
//	Author:吉田　悠人
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "start button.h"
#include "renderer.h"
#include "manager.h"
#include "fade.h"
#include "number.h"
#include "sound.h"
#include "game.h"
#include "player.h"
#include "player data.h"
//=============================================================================
// 静的メンバー変数
//=============================================================================
TEXTURE_DATA CStartButton::m_TextureData = {NULL,	"data/TEXTURE/Text_Start.png",};
//=============================================================================
// コンストラクタ
//=============================================================================
CStartButton::CStartButton(int nPriorit):CButton(nPriorit)
{
	m_pNumber = NULL;
	m_bPush = false;
}

//=============================================================================
// テクスチャ読み込み
//=============================================================================
HRESULT CStartButton::Load(void)
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
void CStartButton::Unload(void)
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
CStartButton * CStartButton::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nStage)
{
	//メモリ確保
	CStartButton *pStartButton = NULL;
	pStartButton = new CStartButton;
	
	//NULLチェック
	if (pStartButton != NULL)
	{
		//位置設定
		pStartButton->SetPos(D3DXVECTOR3(pos.x, pos.y, pos.z));
		//サイズ設定
		pStartButton->SetSize(D3DXVECTOR3(size.x, size.y, size.z));
		//テクスチャ設定
		pStartButton->BindTexture(m_TextureData.m_Texture);
		//ステージ設定
		pStartButton->SetStage(nStage+1);
		//初期化処理
		pStartButton->Init();

	}
	return pStartButton;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CStartButton::Init(void)
{
	//現在のステージ番号
	m_pNumber = CNumber::Create(D3DXVECTOR3(GetPos().x + 65, GetPos().y, 0.0f), D3DXVECTOR3(25.0f, GetSize().y, 0.0f));
	m_pNumber->SetNumber(nStage);
	
	//ボタンの初期化処理
	CButton::Init();
	
	//文字の位置調整
	SetPos(D3DXVECTOR3(GetPos().x + 20, GetPos().y,0.0f));
	SetSize(D3DXVECTOR3(GetSize().x-100, GetSize().y,0.0f));

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CStartButton::Uninit(void)
{
	//NULLチェック
	if (m_pNumber != NULL)
	{
		m_pNumber->Uninit();
	}
	//終了処理
	CButton::Uninit();
}

//=============================================================================
// 描画処理
//=============================================================================
void CStartButton::Draw(void)
{
	//NULLチェック
	if (m_pNumber != NULL)
	{
		m_pNumber->Draw();
	}

	CButton::Draw();
}

//=============================================================================
// ステージ番号ゲッター
//=============================================================================
void CStartButton::SetStage(int stage)
{
	nStage = stage;
}

//=============================================================================
// マウスオーバー判定
//=============================================================================
void CStartButton::MouseOver(void)
{

}

//=============================================================================
// プッシュ判定処理
//=============================================================================
void CStartButton::Push()
{
	//マウスポインタ取得
	CInihMouse *pMouse = CManager::GetMouse();
	//サウンド取得
	CSound*		pSound = CManager::GetSound();	
	//フェイド取得
	CFade*		pFade = CManager::GetFade();	
	//プレイヤーウェポン取得
	WEAPON_DATA nPlayerWeapon = CManager::GetPlayer()->GetWeaponData();

	//左クリック
	if (pMouse->GetClickTrigger(CLICK_LEFT) == true)
	{
		//ボタンを押したか
		if (m_bPush == false)
		{
			//武装がどちらも装備しているか
			if (nPlayerWeapon.Left != WEAPONS_MODE_NONE
				|| nPlayerWeapon.Right != WEAPONS_MODE_NONE)
			{
				//SE音
				pSound->Play(CSound::LABEL_SE_START);
				//フェイドアウト判定
				pFade->SetFade(GAME_MODE_STAGE);
				//ボタン押したか
				m_bPush = true;
			}
		}
	}
}
