//=============================================================================
//
// キーボード入力処理 [keyboard.cpp]
// Author : 吉田悠人
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "keyboard.h"

//=============================================================================
//コンストラクタ
//=============================================================================
CKeyboard::CKeyboard()
{
    memset(m_aState, 0, sizeof(m_aState));
    memset(m_aStateTrigger, 0, sizeof(m_aStateTrigger));
    memset(m_aStateRelease, 0, sizeof(m_aStateRelease));
}

//=============================================================================
//デストラクタ
//=============================================================================
CKeyboard::~CKeyboard()
{
}

//=============================================================================
//初期化処理
//=============================================================================
HRESULT CKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
    CInput::Init(hInstance, hWnd);

    //入力デバイスの作成
    if(FAILED(m_pDinput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
    {
        return E_FAIL;
    }
    //データ・フォーマット設定
    if(FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
    {
        return E_FAIL;
    }
    //強調モード設定
    if(FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
    {
        return E_FAIL;
    }
    //キーボードへのアクセス権獲得
	m_pDevice->Acquire();

    return S_OK;
}

//=============================================================================
//更新処理
//=============================================================================
void CKeyboard::Update(void)
{
    BYTE akeyState[NUM_KEY_MAX];    //キーの最大数
    int nCntkey;

    //デバイスからデータ取得
    if(SUCCEEDED(m_pDevice->GetDeviceState(sizeof(akeyState), akeyState)))
    {
        for(nCntkey = 0; nCntkey < NUM_KEY_MAX; nCntkey++)
        {
            m_aStateTrigger[nCntkey] = (m_aState[nCntkey] ^ akeyState[nCntkey]) & akeyState[nCntkey];
            m_aStateRelease[nCntkey] = (m_aState[nCntkey] ^ akeyState[nCntkey]) & ~akeyState[nCntkey];
            m_aState[nCntkey]        = akeyState[nCntkey];
        }
    }
    else
    {
        //キーボードのアクセス権取得
		m_pDevice->Acquire();
    }
}

//=============================================================================
//終了処理
//=============================================================================
void CKeyboard::Uninit(void)
{
    //入力デバイス開放
    if(m_pDevice != NULL)
    {
        //キーボードのアクセス権開放
		m_pDevice->Unacquire();
		m_pDevice = NULL;
    }
    CInput::Uninit();
}

//=============================================================================
//キーの状態取得
//=============================================================================
bool CKeyboard::GetKeyPress(int nkey)
{
    return (m_aState[nkey] & 0x80) ? true : false;
}
bool CKeyboard::GetKeyTrigger(int nkey)
{
    return (m_aStateTrigger[nkey] & 0x80) ? true : false;
}
bool CKeyboard::GetKeyRelease(int nkey)
{
    return (m_aStateRelease[nkey] & 0x80) ? true : false;
}
