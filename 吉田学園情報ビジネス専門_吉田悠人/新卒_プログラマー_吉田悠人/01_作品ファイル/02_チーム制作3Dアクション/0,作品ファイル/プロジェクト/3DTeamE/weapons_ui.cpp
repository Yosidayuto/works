//=============================================================================
//
// ����UI���� [weapons_ui.cpp]
// Author : �g�c�I�l
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "weapons_ui.h"
#include "manager.h"
#include "renderer.h"
#include "billboard.h"
#include "manager.h"

//*****************************************************************************
//�@�}�N����`
//*****************************************************************************
#define SIZE_X (250.0f)
#define SIZE_Y (150.0f)

//*****************************************************************************
//�@�ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CWeapons_ui::m_pTexture[WEAPONS_TEXTURE_MAX] = {};
char *CWeapons_ui::m_cFileName[WEAPONS_TEXTURE_MAX]=
{
	WEAPONS_UI_AR_TEXTURE,
	WEAPONS_UI_HG_TEXTURE
};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CWeapons_ui::CWeapons_ui() : CObject2D(2)
{
	nCountCol = 0;
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CWeapons_ui::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	for (int nTexture=0;nTexture<WEAPONS_TEXTURE_MAX;nTexture++)
	{
		D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
			m_cFileName[nTexture],						// �t�@�C���̖��O
			&m_pTexture[nTexture]);						// �ǂݍ��ރ������[

	}
	return S_OK;
}

//=============================================================================
// �e�N�X�`���j���֐�
//=============================================================================
void CWeapons_ui::Unload(void)
{
	// �e�N�X�`���̔j��
	for (int nTexture = 0; nTexture < WEAPONS_TEXTURE_MAX; nTexture++)
	{
		if (m_pTexture[nTexture] != NULL)
		{
			m_pTexture[nTexture]->Release();
			m_pTexture[nTexture] = NULL;
		}

	}
}

//=============================================================================
// �����֐�
//=============================================================================
CWeapons_ui * CWeapons_ui::Create(void)
{
	//�������̊m��
	CWeapons_ui* pWeaponsUi = NULL;
	pWeaponsUi = new CWeapons_ui;
	
	//NULL�`�F�b�N
	if (pWeaponsUi!=NULL)
	{
		//�ʒu�ݒ�
		pWeaponsUi->SetPos(D3DXVECTOR3(SCREEN_WIDTH - (SIZE_X / 2), SCREEN_HEIGHT - (SIZE_Y + 25), 0));
		//�����ݒ�
		pWeaponsUi->SetRot(0.0f);
		//�T�C�Y�ݒ�
		pWeaponsUi->SetSize(D3DXVECTOR3(SIZE_X, SIZE_Y, 0));
		//�J���[�ݒ�
		pWeaponsUi->SetCol(D3DCOLOR_RGBA(255, 255, 255, 255));
		//�e�N�X�`���ݒ�
		pWeaponsUi->BindTexture(m_pTexture[CManager::GetWeaponsMode()]);
		//����������
		pWeaponsUi->Init();
	}

	return pWeaponsUi;
}

//=============================================================================
// �X�V����
//=============================================================================
void CWeapons_ui::Update(void)
{
	//�X�V����
	CObject2D::Update();
	
	//�J���[�ύX�p���l��0���傫��������
	if (nCountCol >= 0)
	{
		nCountCol--;
	}
	//�J���[�ύX�p���l��0����
	if (nCountCol == 0)
	{
		SetCol(D3DCOLOR_RGBA(255, 255, 255, 255));
	}
}

//=============================================================================
// ����֐�
//=============================================================================
void CWeapons_ui::Gleams(void)
{
	//�J���[�ύX�p���l
	nCountCol = 5;
	//�J���[�ύX
	SetCol(D3DCOLOR_RGBA(255, 241, 86, 255));
}
