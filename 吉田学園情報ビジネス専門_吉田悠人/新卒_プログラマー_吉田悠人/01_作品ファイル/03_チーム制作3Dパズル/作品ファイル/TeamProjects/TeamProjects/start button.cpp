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
#include "resource manager.h"
#include "manager.h"
#include "pause.h"
#include "sound.h"
#include "inputcontroller.h"
#include "inputkeyboard.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CStartButton::CStartButton()
{
}

//=============================================================================
// 生成処理
//=============================================================================
CStartButton * CStartButton::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//メモリ確保
	CStartButton *pStartButton = NULL;
	pStartButton = new CStartButton;
	//リソース確保
	CResource* pResource = CManager::GetResource();
	LPDIRECT3DTEXTURE9 Texture = pResource->TextureLoad(pStartButton->m_nTexture);

	//NULLチェック
	if (pStartButton != NULL)
	{
		//位置設定
		pStartButton->SetPos(D3DXVECTOR3(pos.x, pos.y, pos.z));
		//サイズ設定
		pStartButton->SetSize(D3DXVECTOR3(size.x, size.y, size.z));
		//テクスチャ設定
		pStartButton->BindTexture(Texture);
		//初期化処理
		pStartButton->Init();
	}
	return pStartButton;
}

//=============================================================================
// プッシュ判定処理
//=============================================================================
void CStartButton::Push()
{
	//キー入力取得
	CInputKeyboard* pInputKey = (CInputKeyboard*)CManager::GetInputKey();
	//ポーズ取得
	CPause* pPause = CManager::GetPause();
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
		//ポーズ終了
		pPause->Delete();
		//BGMの再生
		CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_BGM_DECISION);
	}
}

