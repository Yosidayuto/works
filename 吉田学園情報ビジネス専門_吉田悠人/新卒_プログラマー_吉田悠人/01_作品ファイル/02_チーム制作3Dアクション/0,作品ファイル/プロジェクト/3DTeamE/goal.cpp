//=============================================================================
//
// �S�[������ [trap.cpp]
// Author : �g�c�I�l
//
//=============================================================================


//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "goal.h"
#include "explosion.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "fade.h"
#include "sound.h"

//*****************************************************************************
//�@�ÓI�����o�ϐ��̏�����
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGoal::CGoal()
{
	m_GameMode = {};
	m_pTexture = NULL;
	SetObjType(OBJTYPE_NONE);
}


//=============================================================================
// �����֐�
// CManager::MODE Mode�i���̃X�e�[�W�ݒ�j
//=============================================================================
CGoal * CGoal::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, CManager::MODE Mode)
{
	//�������m��
	CGoal* pGoal = NULL;
	pGoal = new CGoal;

	//���������m�ۂ���Ă��邩
	if (pGoal!=NULL)
	{
		//�ʒu�ݒ�
		pGoal->SetPosition(pos);
		//�����ݒ�
		pGoal->SetRotation(rot);
		//�T�C�Y�ݒ�
		pGoal->SetSize(size);
		//�S�[�������ۂ̎��̃}�b�v
		pGoal->m_GameMode = Mode;

		//�F�ݒ�
		for (int nMesh = 0; nMesh < MESH_Y_BLOCK + 1; nMesh++)
		{
			pGoal->SetColor(D3DXCOLOR(col.r, col.g, col.b, nMesh*0.1f), nMesh);
		}

		//����������
		pGoal->Init();
	}
	return pGoal;
}



//=============================================================================
// �X�V�֐�
//=============================================================================
void CGoal::Update(void)
{
	//���b�V���̃J���[�ύX
	CMeshCylinder::ColorAnimation();
	//�S�[������
	HitGoal();
	//���b�V���̃A�b�v�f�[�g
	CMeshCylinder::Update();
}

//=============================================================================
// �S�[������֐�
//=============================================================================
void CGoal::HitGoal(void)
{
	//�v���C���[�̈ʒu�擾
	D3DXVECTOR3 Playerpos = CManager::GetPlayer()->GetPos();

	//�����蔻��
	if (GetPos().x+(GetSize().x/2)>Playerpos.x
		&&GetPos().x - (GetSize().x / 2)<Playerpos.x
		&&GetPos().z + (GetSize().z / 2)> Playerpos.z
		&&GetPos().z - (GetSize().z / 2)< Playerpos.z)
	{
		//�T�E���h�̎擾
		CSound * pSound = CManager::GetSound();
		pSound->StopSound();

		//���̃X�e�[�W�J��
		CManager::GetFade()->SetFade(m_GameMode);
		Uninit();
	}
}

