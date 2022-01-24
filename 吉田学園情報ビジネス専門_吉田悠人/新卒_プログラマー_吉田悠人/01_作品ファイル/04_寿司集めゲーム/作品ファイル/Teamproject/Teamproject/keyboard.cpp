//=============================================================================
//
// �L�[�{�[�h���͏��� [keyboard.cpp]
// Author : �g�c�I�l
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "keyboard.h"

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CKeyboard::CKeyboard()
{
    memset(m_aState, 0, sizeof(m_aState));
    memset(m_aStateTrigger, 0, sizeof(m_aStateTrigger));
    memset(m_aStateRelease, 0, sizeof(m_aStateRelease));
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CKeyboard::~CKeyboard()
{
}

//=============================================================================
//����������
//=============================================================================
HRESULT CKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
    CInput::Init(hInstance, hWnd);

    //���̓f�o�C�X�̍쐬
    if(FAILED(m_pDinput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
    {
        return E_FAIL;
    }
    //�f�[�^�E�t�H�[�}�b�g�ݒ�
    if(FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
    {
        return E_FAIL;
    }
    //�������[�h�ݒ�
    if(FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
    {
        return E_FAIL;
    }
    //�L�[�{�[�h�ւ̃A�N�Z�X���l��
	m_pDevice->Acquire();

    return S_OK;
}

//=============================================================================
//�X�V����
//=============================================================================
void CKeyboard::Update(void)
{
    BYTE akeyState[NUM_KEY_MAX];    //�L�[�̍ő吔
    int nCntkey;

    //�f�o�C�X����f�[�^�擾
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
        //�L�[�{�[�h�̃A�N�Z�X���擾
		m_pDevice->Acquire();
    }
}

//=============================================================================
//�I������
//=============================================================================
void CKeyboard::Uninit(void)
{
    //���̓f�o�C�X�J��
    if(m_pDevice != NULL)
    {
        //�L�[�{�[�h�̃A�N�Z�X���J��
		m_pDevice->Unacquire();
		m_pDevice = NULL;
    }
    CInput::Uninit();
}

//=============================================================================
//�L�[�̏�Ԏ擾
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
