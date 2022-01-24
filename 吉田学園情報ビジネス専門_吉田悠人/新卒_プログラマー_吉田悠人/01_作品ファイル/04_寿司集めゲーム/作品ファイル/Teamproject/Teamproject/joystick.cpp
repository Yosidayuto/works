//=============================================================================
//
// �W���C�X�e�B�b�N���� [joystick.cpp]
// Author : �ѐ�ї���
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "input.h"
#include "joystick.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECTINPUTDEVICE8 CJoystick::m_pJDevice[MAX_PLAYER] = 
{NULL,NULL/*,NULL,NULL*/};
LPDIRECTINPUTEFFECT CJoystick::m_IpDIEffect[MAX_PLAYER] =
{ NULL,NULL/*,NULL,NULL*/ };
DIDEVCAPS CJoystick::m_diDevCaps;
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CJoystick::CJoystick()
{
	memset(m_aJoyState, 0, sizeof(m_aJoyState));
	memset(m_aJoyStateTrigger, 0, sizeof(m_aJoyStateTrigger));
	memset(m_aJoyStateRelease, 0, sizeof(m_aJoyStateRelease));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CJoystick::~CJoystick()
{
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CJoystick::Init(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT  hr;

	hr = CInput::Init(hInstance, hWnd);

	hr = m_pDinput->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback, NULL, DIEDFL_FORCEFEEDBACK | DIEDFL_ATTACHEDONLY);
	
	if (FAILED(hr)) 
	{
		MessageBox(hWnd, "Can't create Device.", "Error", MB_OK);
		return FALSE;
	}

	for (int nJoystick = 0; nJoystick < MAX_PLAYER; nJoystick++)
	{
		if (m_pJDevice[nJoystick] != NULL)
		{

			hr = m_pJDevice[nJoystick]->SetDataFormat(&c_dfDIJoystick);
			if (FAILED(hr)) {
				MessageBox(hWnd, "Can't set data format.", "Error", MB_OK);
				return FALSE;
			}

			hr = m_pJDevice[nJoystick]->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND);
			if (FAILED(hr)) {
				MessageBox(hWnd, "Can't set cooperative level.", "Error", MB_OK);
				return FALSE;
			}

			m_diDevCaps.dwSize = sizeof(DIDEVCAPS);
			hr = m_pJDevice[nJoystick]->GetCapabilities(&m_diDevCaps);
			if (FAILED(hr)) {
				MessageBox(hWnd, "Can't create device capabilities.", "Error", MB_OK);
				return FALSE;
			}

			hr = m_pJDevice[nJoystick]->EnumObjects(EnumAxesCallback, (VOID*)&m_dwNumForceFeedbackAxis, DIDFT_AXIS);
			if (FAILED(hr)) {
				MessageBox(hWnd, "Can't set property.", "Error", MB_OK);
				return FALSE;
			}

			if (m_dwNumForceFeedbackAxis > 2)
			{
				m_dwNumForceFeedbackAxis = 2;
			}

			if (!CreateEffect(hWnd, nJoystick)) {
				MessageBox(hWnd, "Can't create effect.", "Error", MB_OK);
				return FALSE;
			}

			hr = m_pJDevice[nJoystick]->Poll();
			if (FAILED(hr)) {
				hr = m_pJDevice[nJoystick]->Acquire();
				while (hr == DIERR_INPUTLOST) {
					hr = m_pJDevice[nJoystick]->Acquire();
				}
			}
		}

	}
	return TRUE;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CJoystick::Uninit(void)
{
	CInput::Uninit();

	for (int nJoystick = 0; nJoystick < MAX_PLAYER; nJoystick++)
	{
		if (m_pJDevice[nJoystick] != NULL)
		{
			//�f�o�C�X����̒�~
			m_pJDevice[nJoystick]->Unacquire();
			m_pJDevice[nJoystick]->Release();
			m_pJDevice[nJoystick] = NULL;
		}
		if (m_IpDIEffect[nJoystick] != NULL)
		{
			m_IpDIEffect[nJoystick]->Release();
		}
	}

}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CJoystick::Update(void)
{
	int nCntKey;
	DIJOYSTATE js;
	for (int nJoystick = 0; nJoystick < MAX_PLAYER; nJoystick++)
	{

		if (m_pJDevice[nJoystick] != NULL)
		{
			m_pJDevice[nJoystick]->Poll();
			m_pJDevice[nJoystick]->GetDeviceState(sizeof(DIJOYSTATE), &js);
			//�f�o�C�X����f�[�^���擾
			if (SUCCEEDED(m_pJDevice[nJoystick]->GetDeviceState(sizeof(DIJOYSTATE), &js)))
			{
				for (nCntKey = 0; nCntKey < NUM_JS_MAX; nCntKey++)
				{
					//�L�[�v���X����ۑ�
					m_aJoyState[nCntKey][nJoystick] = m_aJoyState[nCntKey][nJoystick];

					//�L�[�g���K�[
					m_aJoyStateTrigger[nCntKey][nJoystick] = (m_aJoyState[nCntKey][nJoystick] ^ js.rgbButtons[nCntKey]) &  js.rgbButtons[nCntKey];

					//�L�[�����[�X
					m_aJoyStateRelease[nCntKey][nJoystick] = (m_aJoyState[nCntKey][nJoystick] ^ js.rgbButtons[nCntKey]) & ~js.rgbButtons[nCntKey];

					//�L�[�v���X����ۑ�
					m_aJoyState[nCntKey][nJoystick] = js.rgbButtons[nCntKey];
				}
			}
			else
			{
				m_pJDevice[nJoystick]->Acquire();
			}
		}

	}
}

//=============================================================================
// PRESS
//=============================================================================
bool CJoystick::GetJoystickPress(int nKey, int nJoystick)
{
	return m_aJoyState[nKey][nJoystick] & 0x80 ? true : false;
}

//=============================================================================
// TRIGGER
//=============================================================================
bool CJoystick::GetJoystickTrigger(int nKey, int nJoystick)
{
	return m_aJoyStateTrigger[nKey][nJoystick] & 0x80 ? true : false;
}

//=============================================================================
// RELEASE
//=============================================================================
bool CJoystick::GetJoystickRelease(int nKey, int nJoystick)
{
	return m_aJoyStateRelease[nKey][nJoystick] & 0x80 ? true : false;
}

//=============================================================================
//�W���C�X�e�B�b�N�N���X�̃X�e�B�b�N���̎擾
//=============================================================================
DIJOYSTATE CJoystick::GetJoyStick(int nJoystick)
{
	DIJOYSTATE js;
	SecureZeroMemory(&js, sizeof(js));

	if (m_pJDevice[nJoystick] != NULL)
	{
		m_pJDevice[nJoystick]->Poll();
		m_pJDevice[nJoystick]->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}

	return js;
}

//=============================================================================
//    Force Feedback Callback.
//=============================================================================
BOOL CJoystick::EnumFFDevicesCallback(const DIDEVICEINSTANCE * pdidInstance, VOID * pContext)
{
	HRESULT hr;
	for (int nJoystick = 0; nJoystick < MAX_PLAYER; nJoystick++)
	{
		if (m_pJDevice[nJoystick]==NULL)
		{
			hr = m_pDinput->CreateDevice(pdidInstance->guidInstance, &m_pJDevice[nJoystick], NULL);
			if (FAILED(hr)) return DIENUM_CONTINUE;
		}
	}
	return DIENUM_STOP;
}

//=============================================================================
//EnumJoysticksCallback
//=============================================================================
BOOL CALLBACK CJoystick::EnumJoysticksCallback(const DIDEVICEINSTANCE * pdidInstance, VOID * pContext)
{
	HRESULT hr;
	for (int nJoystick = 0; nJoystick < MAX_PLAYER; nJoystick++)
	{
		if (m_pJDevice[nJoystick] == NULL)
		{
			hr = m_pDinput->CreateDevice(pdidInstance->guidInstance, &m_pJDevice[nJoystick], NULL);
			if (FAILED(hr)) return DIENUM_CONTINUE;
			// �W���C�X�e�B�b�N�̔\�͂𒲂ׂ�
			m_diDevCaps.dwSize = sizeof(DIDEVCAPS);
			hr = m_pJDevice[nJoystick]->GetCapabilities(&m_diDevCaps);
			if (FAILED(hr))
			{   // �W���C�X�e�B�b�N�\�͂̎擾�Ɏ��s
				if (m_pJDevice[nJoystick])
				{ 
					m_pJDevice[nJoystick]->Release();
					m_pJDevice[nJoystick] = NULL;
				};
			}
			return DIENUM_CONTINUE;
		}
	}
	return DIENUM_STOP;
}


//=============================================================================
// EnumAxesCallback
//=============================================================================
BOOL CALLBACK CJoystick::EnumAxesCallback(const DIDEVICEOBJECTINSTANCE * pdidoi, VOID * pContext)
{
	HRESULT     hr;
	DIPROPRANGE diprg;

	diprg.diph.dwSize = sizeof(DIPROPRANGE);
	diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	diprg.diph.dwHow = DIPH_BYID;
	diprg.diph.dwObj = pdidoi->dwType;
	diprg.lMin = 0 - 1000;
	diprg.lMax = 0 + 1000;
	for (int nJoystick = 0; nJoystick < MAX_PLAYER; nJoystick++)
	{
		if (m_pJDevice[nJoystick]!=NULL)
		{
			hr = m_pJDevice[nJoystick]->SetProperty(DIPROP_RANGE, &diprg.diph);
		}
	}

	if (FAILED(hr)) return DIENUM_STOP;

	DWORD *pdwNumForceFeedbackAxis = (DWORD*)pContext;
	if ((pdidoi->dwFlags & DIDOI_FFACTUATOR) != 0) (*pdwNumForceFeedbackAxis)++;

	return DIENUM_CONTINUE;
}

//=============================================================================
// Create Effect.
//=============================================================================
BOOL CJoystick::CreateEffect(HWND hWnd, int nJoystick)
{
	DWORD           rgdwAxes[2] = { DIJOFS_X , DIJOFS_Y };
	LONG            rglDirection[2] = { 1 , 1 };
	DICONSTANTFORCE cf;
	DIEFFECT        eff;
	HRESULT         hr;

	ZeroMemory(&eff, sizeof(eff));
	eff.dwSize = sizeof(DIEFFECT);
	eff.dwFlags = DIEFF_CARTESIAN | DIEFF_OBJECTOFFSETS;
	eff.dwDuration = INFINITE;
	eff.dwSamplePeriod = 0;
	eff.dwGain = DI_FFNOMINALMAX;
	eff.dwTriggerButton = DIEB_NOTRIGGER;
	eff.dwTriggerRepeatInterval = 0;
	eff.cAxes = m_dwNumForceFeedbackAxis;
	eff.rgdwAxes = rgdwAxes;
	eff.rglDirection = rglDirection;
	eff.lpEnvelope = 0;
	eff.cbTypeSpecificParams = sizeof(DICONSTANTFORCE);
	eff.lpvTypeSpecificParams = &cf;
	eff.dwStartDelay = 0;

	hr = m_pJDevice[nJoystick]->CreateEffect(GUID_ConstantForce, &eff,
		&m_IpDIEffect[nJoystick], NULL);

	if (FAILED(hr)) {
		MessageBox(hWnd, "Can't create effect.", "Error", MB_OK);
		return FALSE;
	}

	return TRUE;
}

