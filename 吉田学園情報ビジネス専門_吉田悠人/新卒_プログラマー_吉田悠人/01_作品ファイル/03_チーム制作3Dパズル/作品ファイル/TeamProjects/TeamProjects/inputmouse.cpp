//=============================================================================
//
//	マウス入力処理[inputmouse.cpp]
//	Author:吉田 悠人
//
//=============================================================================
//=============================================================================
//インクルードファイル
//=============================================================================
#include "inputmouse.h"

//=============================================================================
//コンストラクタ
//=============================================================================
CInputMouse::CInputMouse()
{
	//座標の初期化
#ifdef  MOUSE_POS_TYPE
	m_aMousePos.lX = (LONG)0.0f;
	m_aMousePos.lY = (LONG)0.0f;

#else 
	posMouse.x = 0.0f;
	posMouse.y = 0.0f;
#endif
	memset(m_aClickState.rgbButtons, 0, sizeof(m_aClickState.rgbButtons));
	memset(m_aClickTrigger.rgbButtons, 0, sizeof(m_aClickTrigger.rgbButtons));
	memset(m_aClickRelease.rgbButtons, 0, sizeof(m_aClickRelease.rgbButtons));


}

//=============================================================================
//デストラクタ
//=============================================================================
CInputMouse::~CInputMouse()
{
}

//=============================================================================
//初期化処理
//=============================================================================
HRESULT CInputMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);
	//座標の初期化
#ifdef  MOUSE_POS_TYPE
	m_aMousePos.lX = (LONG)0.0f;
	m_aMousePos.lY = (LONG)0.0f;
#else 
	hPointerpos = hWnd;
	posMouse.x = 0.0f;
	posMouse.y = 0.0f;
#endif

	//入力デバイス（マウス）の作成
	if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pDeviceInput, NULL)))
	{
		return E_FAIL;
	}
	/*データフォーマットを設定*/
	if (FAILED(m_pDeviceInput->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;
	}
	/*協調モードを設定（フォアグラウンド＆非排他モード*/
	if (FAILED(m_pDeviceInput->SetCooperativeLevel(hWnd, (DISCL_NONEXCLUSIVE | DISCL_FOREGROUND))))
	{
		return E_FAIL;
	}
	// 軸モードを設定（相対値モードに設定）
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;
	//diprop.dwData       = DIPROPAXISMODE_ABS; // 絶対値モードの場合

	if (FAILED(m_pDeviceInput->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
	{
		return E_FAIL;
	}
	/*マウスへのアクセス権を会得（入力制御開始）*/
	m_pDeviceInput->Acquire();




	return S_OK;
}

//=============================================================================
//更新処理
//=============================================================================
void CInputMouse::Update(void)
{


#ifdef  MOUSE_POS_TYPE
	DIMOUSESTATE ClickState;
	if (SUCCEEDED(m_pDeviceInput->GetDeviceState(sizeof(DIMOUSESTATE), &ClickState)))
	{
		for (int nCntClick = 0; nCntClick < NUM_CLICK_MAX; nCntClick++)
		{
			//クリック処理
			m_aClickState.rgbButtons[nCntClick] = ClickState.rgbButtons[nCntClick];
			//クリックトリガー処理
			m_aClickTrigger.rgbButtons[nCntClick] = (m_aClickState.rgbButtons[nCntClick] ^ ClickState.rgbButtons[nCntClick])&ClickState.rgbButtons[nCntClick];
			//クリックリリース処理
			m_aClickRelease.rgbButtons[nCntClick] = (m_aClickState.rgbButtons[nCntClick] ^ ClickState.rgbButtons[nCntClick])&~ClickState.rgbButtons[nCntClick];
		}
		//マウスの移動量取得（IXとIYの移動量）
		m_aMousePos = ClickState;
	}

	else
	{
		m_pDeviceInput->Acquire();
	}
#else 
	DIMOUSESTATE ClickState;

	if (SUCCEEDED(m_pDeviceInput->GetDeviceState(sizeof(DIMOUSESTATE), &ClickState)))
	{
		for (int nCntClick = 0; nCntClick < NUM_CLICK_MAX; nCntClick++)
		{
			//クリックトリガー処理
			m_aClickTrigger.rgbButtons[nCntClick] = (m_aClickState.rgbButtons[nCntClick] ^ ClickState.rgbButtons[nCntClick])&ClickState.rgbButtons[nCntClick];
			//クリックリリース処理
			m_aClickRelease.rgbButtons[nCntClick] = (m_aClickState.rgbButtons[nCntClick] ^ ClickState.rgbButtons[nCntClick])&~ClickState.rgbButtons[nCntClick];
			//クリック処理
			m_aClickState.rgbButtons[nCntClick] = ClickState.rgbButtons[nCntClick];

		}
	}

	else
	{
		m_pDeviceInput->Acquire();
	}
	////スクリーン座標取得
	GetCursorPos(&posMouse);
	ScreenToClient(hPointerpos, &posMouse);

#endif

}

//=============================================================================
// 位置処理
//=============================================================================
#ifdef  MOUSE_POS_TYPE
DIMOUSESTATE CInputMouse::GetMousePos(void)
{
	return m_aMousePos;
}
#else 
POINT CInputMouse::GetMousePos(void)
{
	return posMouse;
}
#endif

//=============================================================================
// クリック処理
//=============================================================================
bool CInputMouse::GetClick(int nClick)
{
	return (m_aClickState.rgbButtons[nClick] & 0x80) ? true : false;
}

bool CInputMouse::GetClickTrigger(int nClick)
{
	return (m_aClickTrigger.rgbButtons[nClick] & 0x80) ? true : false;
}

bool CInputMouse::GetClickRelease(int nClick)
{
	return (m_aClickRelease.rgbButtons[nClick] & 0x80) ? true : false;
}
