//=============================================================================
//
//	�}�E�X���͏���[mouse.cpp]
//	Author:�g�c �I�l
//
//=============================================================================
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "mouse.h"

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CMouse::CMouse()
{
	//�ړ��ʂ̏�����
	m_aMouseMove.lX = (LONG)0.0f;
	m_aMouseMove.lY = (LONG)0.0f;
	//�ʒu�̏�����
	m_aMousePos.x = (LONG)0.0f;
	m_aMousePos.y = (LONG)0.0f;

	memset(m_aClickState.rgbButtons, 0, sizeof(m_aClickState.rgbButtons));
	memset(m_aClickTrigger.rgbButtons, 0, sizeof(m_aClickTrigger.rgbButtons));
	memset(m_aClickRelease.rgbButtons, 0, sizeof(m_aClickRelease.rgbButtons));


}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CMouse::~CMouse()
{
}

//=============================================================================
//����������
//=============================================================================
HRESULT CMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);
	//�ړ��ʂ̏�����
	m_aMouseMove.lX = (LONG)0.0f;
	m_aMouseMove.lY = (LONG)0.0f;
	//�E�B���h�E�̃f�[�^�̎擾
	m_hPointerpos = hWnd;
	//���W�̏�����
	m_aMousePos.x = (LONG)0.0f;
	m_aMousePos.y = (LONG)0.0f;

	//���̓f�o�C�X�i�}�E�X�j�̍쐬
	if (FAILED(m_pDinput->CreateDevice(GUID_SysMouse, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	/*�f�[�^�t�H�[�}�b�g��ݒ�*/
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;
	}
	/*�������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h*/
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_NONEXCLUSIVE | DISCL_FOREGROUND))))
	{
		return E_FAIL;
	}
	// �����[�h��ݒ�i���Βl���[�h�ɐݒ�j
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;
	//diprop.dwData       = DIPROPAXISMODE_ABS; // ��Βl���[�h�̏ꍇ

	if (FAILED(m_pDevice->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
	{
		return E_FAIL;
	}

	/*�}�E�X�ւ̃A�N�Z�X������i���͐���J�n�j*/
	m_pDevice->Acquire();

	return S_OK;
}

//=============================================================================
//�X�V����
//=============================================================================
void CMouse::Update(void)
{
	DIMOUSESTATE ClickState;

	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(DIMOUSESTATE), &ClickState)))
	{
		for (int nCntClick = 0; nCntClick < NUM_CLICK_MAX; nCntClick++)
		{
			//�N���b�N����
			m_aClickState.rgbButtons[nCntClick] = ClickState.rgbButtons[nCntClick];
			//�N���b�N�g���K�[����
			m_aClickTrigger.rgbButtons[nCntClick] = (m_aClickState.rgbButtons[nCntClick] ^ ClickState.rgbButtons[nCntClick])&ClickState.rgbButtons[nCntClick];
			//�N���b�N�����[�X����
			m_aClickRelease.rgbButtons[nCntClick] = (m_aClickState.rgbButtons[nCntClick] ^ ClickState.rgbButtons[nCntClick])&~ClickState.rgbButtons[nCntClick];
		}
		//�}�E�X�̈ړ��ʎ擾�iIX��IY�̈ړ��ʁj
		m_aMouseMove = ClickState;
	}

	else
	{
		m_pDevice->Acquire();
	}

	////�X�N���[�����W�擾
	GetCursorPos(&m_aMousePos);
	ScreenToClient(m_hPointerpos, &m_aMousePos);

}

//=============================================================================
// �ړ��ʏ���
//=============================================================================
DIMOUSESTATE CMouse::GetMouseMove(void)
{
	return m_aMouseMove;
}

//=============================================================================
// �ʒu����
//=============================================================================
POINT CMouse::GetMousePos(void)
{
	return m_aMousePos;
}

//=============================================================================
// �N���b�N����
//=============================================================================
bool CMouse::GetClick(int nClick)
{
	return (m_aClickState.rgbButtons[nClick] & 0x80) ? true : false;
}

bool CMouse::GetClickTrigger(int nClick)
{
	return (m_aClickTrigger.rgbButtons[nClick] & 0x80) ? true : false;
}

bool CMouse::GetClickRelease(int nClick)
{
	return (m_aClickRelease.rgbButtons[nClick] & 0x80) ? true : false;
}
