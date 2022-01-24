//=============================================================================
//
//	リスタートボタン[restart button.cpp]
//	Author:吉田　悠人
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "restart button.h"
#include "renderer.h"
#include "resource manager.h"
#include "manager.h"
#include "sound.h"
#include "inputcontroller.h"
#include "inputkeyboard.h"
#include "fade.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CRestartButton::CRestartButton()
{
}

//=============================================================================
// 生成処理
//=============================================================================
CRestartButton * CRestartButton::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//メモリ確保
	CRestartButton *pRestartButton = NULL;
	pRestartButton = new CRestartButton;

	//リソース確保
	CResource* pResource = CManager::GetResource();
	LPDIRECT3DTEXTURE9 Texture = pResource->TextureLoad(pRestartButton->m_nTexture);

	//NULLチェック
	if (pRestartButton != NULL)
	{
		//位置設定
		pRestartButton->SetPos(D3DXVECTOR3(pos.x, pos.y, pos.z));
		//サイズ設定
		pRestartButton->SetSize(D3DXVECTOR3(size.x, size.y, size.z));
		//テクスチャ設定
		pRestartButton->BindTexture(Texture);
		//初期化処理
		pRestartButton->Init();
	}
	return pRestartButton;
}

//=============================================================================
// プッシュ判定処理
//=============================================================================
void CRestartButton::Push()
{
	//フェイド取得
	CFade*	pBlackout = CManager::GetFadeout();
	//キー入力取得
	CInputKeyboard* pInputKey = (CInputKeyboard*)CManager::GetInputKey();
	// コントローラー入力の取得
	CInputJoyStick* pJoyInput = (CInputJoyStick*)CManager::GetInputController();
	bool bpush = false;

	if (pJoyInput != NULL)
	{
		if (pJoyInput->GetJoyStickTrigger(CInputJoyStick::JOY_BUTTON_A))bpush = true;
	}

	//スティック入力
	if (bpush || pInputKey->GetKeyTrigger(DIK_RETURN))
	{
		//ステージロード
		pBlackout->SetWhiteout(CGame::GetMapMode());

		//BGMの再生
		CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_BGM_DECISION);
	}
}

