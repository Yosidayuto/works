//=============================================================================
//
//	セリフNo12 [talk no12.cpp]
//	Author:吉田 悠人
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "resource manager.h"
#include "inputkeyboard.h"
#include "inputcontroller.h"
#include "renderer.h"
#include "talk no12.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define TALK_APPEAR (220)	//出現している時間

//=============================================================================
// コンストラクタ
//=============================================================================
CTalkNo12::CTalkNo12(int nPriorit)
{

}

//=============================================================================
// 生成処理
//=============================================================================
CTalkNo12 * CTalkNo12::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//メモリ確保
	CTalkNo12* pTalkNo12 = nullptr;
	pTalkNo12 = new CTalkNo12;
	//リソース確保
	CResource* pResource = CManager::GetResource();
	LPDIRECT3DTEXTURE9 Texture = pResource->TextureLoad(pTalkNo12->m_nTexture);

	if (pTalkNo12 != nullptr)
	{
		//位置設定
		pTalkNo12->SetPos(pos);
		//サイズ設定
		pTalkNo12->SetSize(size);
		//テクスチャ設定
		pTalkNo12->BindTexture(Texture);
		//初期化処理
		pTalkNo12->Init();
	}
	return pTalkNo12;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTalkNo12::Init(void)
{
	//出現している時間セット
	SetAppear(TALK_APPEAR);
	//フェード状況設定
	SetFade(FADE_IN);

	//初期化処理
	CTalkbase::Init();
	return S_OK;
}

//=============================================================================
// トークを次に進める関数
//=============================================================================
void CTalkNo12::Talk(void)
{
	//キーボード入力取得
	CInputKeyboard* pKeyInput = (CInputKeyboard*)CManager::GetInputKey();
	//コントローラー入力取得
	CInputJoyStick* pJoyInput = (CInputJoyStick*)CManager::GetInputController();
	//入力確認スイッチ
	bool bJoyStick = false;
	//コントローラー入力確認
	if (pJoyInput != NULL)
	{
		if (pJoyInput->GetJoyStickTrigger(CInputJoyStick::JOY_BUTTON_A)) bJoyStick = true;

	}

	//カウントアップ
	m_nTalkCount++;

	//カウントが一定に達したら || キーを押したら||ボタンを押したら
	if (m_nTalkCount >= TALK_APPEAR || pKeyInput->GetKeyTrigger(DIK_SPACE) || bJoyStick)
	{
		//フェード状況設定
		m_Fade = FADE_OUT;

		//カウント初期化
		m_nTalkCount = 0;
	}

}
