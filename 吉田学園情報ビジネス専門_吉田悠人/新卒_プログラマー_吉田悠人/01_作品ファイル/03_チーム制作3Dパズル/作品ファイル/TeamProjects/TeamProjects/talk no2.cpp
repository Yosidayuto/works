//=============================================================================
//
//	セリフNo2 [talk no2.cpp]
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
#include "talk no2.h"
#include "tutorial.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define TALK_APPEAR (420)	//出現している時間

//=============================================================================
// コンストラクタ
//=============================================================================
CTalkNo2::CTalkNo2(int nPriorit)
{
	m_bTutorial = false;
	m_pTutorial = nullptr;
}

//=============================================================================
// 生成処理
//=============================================================================
CTalkNo2 * CTalkNo2::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//メモリ確保
	CTalkNo2* pTalkNo2 = nullptr;
	pTalkNo2 = new CTalkNo2;
	//リソース確保
	CResource* pResource = CManager::GetResource();
	LPDIRECT3DTEXTURE9 Texture = pResource->TextureLoad(pTalkNo2->m_nTexture);

	//NULLチェック
	if (pTalkNo2 != nullptr)
	{
		//位置設定
		pTalkNo2->SetPos(pos);
		//サイズ設定
		pTalkNo2->SetSize(size);
		//テクスチャ設定
		pTalkNo2->BindTexture(Texture);
		//初期化処理
		pTalkNo2->Init();
	}
	return pTalkNo2;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTalkNo2::Init(void)
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
// トーク処理
//=============================================================================
void CTalkNo2::Talk(void)
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

	//フラグが立っていない状況
	if (m_bTutorial == false)
	{
		//カウントアップ
		m_nTalkCount++;

		//カウントの数値が一定に達したら || キーを押したら||ボタンを押したら
		if (m_nTalkCount >= TALK_APPEAR || pKeyInput->GetKeyTrigger(DIK_SPACE) || bJoyStick)
		{
			//カウント初期化
			m_nTalkCount = 0;
			
			//チュートリアル生成
			if (m_pTutorial == nullptr)
			{
				m_pTutorial = CTutorial::Create();
			}

			m_bTutorial = true;
		}
	}

	//フラグが立った状況
	else if (m_bTutorial == true)
	{
		//キーを押したら||ボタンを押したら
		if (pKeyInput->GetKeyTrigger(DIK_SPACE)|| bJoyStick)
		{
			//NULLチェック
			if (m_pTutorial != nullptr)
			{
				//終了処理
				m_pTutorial->TutorialUninit();
				m_pTutorial = nullptr;
			}

			//透過状況を設定
			m_Fade = FADE_OUT;
		}
	}
}
