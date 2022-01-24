//=============================================================================
//
//	終了ボタン[end button.cpp]
//	Author:吉田　悠人
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "end button.h"
#include "renderer.h"
#include "resource manager.h"
#include "manager.h"
#include "fade.h"
#include "inputcontroller.h"
#include "inputkeyboard.h"
#include "sound.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CEndButton::CEndButton()
{
}

//=============================================================================
// 生成処理
//=============================================================================
CEndButton * CEndButton::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//メモリ確保
	CEndButton *pEndButton = NULL;
	pEndButton = new CEndButton;
	//リソース確保
	CResource* pResource = CManager::GetResource();
	LPDIRECT3DTEXTURE9 Texture = pResource->TextureLoad(pEndButton->m_nTexture);

	//NULLチェック
	if (pEndButton != NULL)
	{
		//位置設定
		pEndButton->SetPos(D3DXVECTOR3(pos.x, pos.y, pos.z));
		//サイズ設定
		pEndButton->SetSize(D3DXVECTOR3(size.x, size.y, size.z));
		//テクスチャ設定
		pEndButton->BindTexture(Texture);
		//初期化処理
		pEndButton->Init();
	}
	return pEndButton;
}

//=============================================================================
// プッシュ判定処理
//=============================================================================
void CEndButton::Push()
{
	//フェイド取得
	CFade*			pFade = CManager::GetFadeout();
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
		pFade->SetBlackout(CManager::MODE_TITLE);

		//BGMの再生
		CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_BGM_DECISION);
	}
}
