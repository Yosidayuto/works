//=============================================================================
//
// �^�C�g������ [tutorial.cpp]
// Author : 
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "tutorial.h"
#include "sound.h"
#include "joystick.h"
#include "sound.h"
#include "scene2d.h"
#include "keyboard.h"
#include "fade.h"
#include "resource manager.h"
#include "game.h"
#include "joystick.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�������
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTutorial::CTutorial()
{
	for (int nCount = 0; nCount < MAX_TUTORIAL_TEX; nCount++)
	{
		m_pTutorial[nCount] = new CScene2d;
		if (m_pTutorial[nCount] != nullptr)
		{
			m_pTutorial[nCount]->Init();
		}
	}

	m_pTutorial[TEX_TUTORIAL]->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f));
	m_pTutorial[TEX_TUTORIAL]->SetSize(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTutorial::~CTutorial()
{

}

//=============================================================================
// ��������
//=============================================================================
CTutorial * CTutorial::Create(void)
{
	CTutorial *pTutorial;
	pTutorial = new CTutorial;

	//���\�[�X�m��(���\�[�X�}�l�[�W���[����Ăяo��)
	CResource* pResource = CManager::GetResource();

	for (int nCount = 0; nCount < MAX_TUTORIAL_TEX; nCount++)
	{
		LPDIRECT3DTEXTURE9 TitleTexture = pResource->TextureLoad(pTutorial->m_nTexture[nCount]);

		pTutorial->m_pTutorial[nCount]->BindTexture(TitleTexture);
	}

	if (pTutorial != nullptr)
	{
		pTutorial->Init();
	}

	return pTutorial;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTutorial::Init(void)
{
	//�I�u�W�F�N�g����
	CManager::CreateCamera();
	CManager::CreateLight();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CTutorial::Uninit(void)
{

	CSound *pSound = CManager::GetSound();
	pSound->StopSound(CSound::LABEL_BGM_TITLE);
}

//=============================================================================
// �X�V����
//=============================================================================
void CTutorial::Update(void)
{
	//�T�E���h
	CSound * pSound = CManager::GetSound();
	//�L�[�{�[�h�̎擾
	CKeyboard * pInputKeyboard = CManager::GetInputKeyboard();
	CJoystick * pJoy = CManager::GetInputJoystick();

	if (CManager::GetInputKeyboard()->GetKeyTrigger(DIK_Z))
	{
		CManager::GetFade()->SetFade(CManager::MODE_GAME);
	}

	if (pJoy->GetJoystickTrigger(JS_A, 0))
	{
		CManager::GetFade()->SetFade(CManager::MODE_GAME);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CTutorial::Draw(void)
{
}
