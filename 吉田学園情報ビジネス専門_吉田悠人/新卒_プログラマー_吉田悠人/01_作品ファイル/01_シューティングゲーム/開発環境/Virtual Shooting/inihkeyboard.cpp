//=============================================================================
//
// キーボード処理 [inihkeyboard.cpp]
// Author : 吉田悠人
//
//=============================================================================
//=============================================================================
// インクルードファイル
//=============================================================================
#include"inihkeyboard.h"

//=============================================================================
// コンストラクト
//=============================================================================
CInihKeyboard::CInihKeyboard()
{
	//キー情報の初期化
	memset(m_akeyState,0,sizeof(m_akeyState));
	memset(m_aKesStateTrigger, 0, sizeof(m_aKesStateTrigger));
	memset(m_aKeyStateRelease, 0, sizeof(m_aKeyStateRelease));
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CInihKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	//インプット初期化
	CInput::Init(hInstance, hWnd);

	//入力デバイス（キーボード）の作成
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	//データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	//協調モードを設定（フォアグラウンド＆非排他モード)
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	//キーボードへのアクセス権を会得（入力制御開始）
	m_pDevice->Acquire();
	return S_OK;
}


//=============================================================================
// 更新処理
//=============================================================================
void CInihKeyboard::Update(void)
{
	BYTE akeyState[NUM_KEY_MAX];			//キーボードの入力情報
	int nCntkey;

	//デバイスからデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(akeyState), akeyState)))
	{
		//キー分forで回す
		for (nCntkey = 0; nCntkey < NUM_KEY_MAX; nCntkey++)
		{
			m_aKesStateTrigger[nCntkey] = (m_akeyState[nCntkey] ^ akeyState[nCntkey])&akeyState[nCntkey];
			m_aKeyStateRelease[nCntkey] = (m_akeyState[nCntkey] ^ akeyState[nCntkey])&~akeyState[nCntkey];
			m_akeyState[nCntkey] = akeyState[nCntkey];//キープレス情報保存
		}
	}

	/*キーボードの更新処理*/
	else
	{
		m_pDevice->Acquire();
	}

}

//=============================================================================
//プッシュゲッター
//=============================================================================
bool CInihKeyboard::GetKeyPress(int nKey)
{
	return (m_akeyState[nKey] & 0x80) ? true : false;
}

//=============================================================================
//プッシュトリガーゲッター
//=============================================================================
bool CInihKeyboard::GetKeyPressTrigger(int nKey)
{
	return (m_aKesStateTrigger[nKey] & 0x80) ? true : false;
}

//=============================================================================
//プッシュリリースゲッター
//=============================================================================
bool CInihKeyboard::GetKeyPressRelease(int nKey)
{
	return (m_aKeyStateRelease[nKey] & 0x80) ? true : false;
}
