//=============================================================================
//
// �H�ו��x�[�X [food base.cpp]
// Author : �g�c�I�l
//
//=============================================================================

//=============================================================================
// �w�b�_�[�t�@�C��
//=============================================================================
#include "food base.h"
#include "player.h"
#include "sound.h"
#include "manager.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define FOOD_HIT (5.0f)	//�v���C���[�̓����蔻��

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CFoodBase::CFoodBase(int nPriority) : CBillboard(nPriority)
{
	SetObjType(OBJTYPE_SUSHI);								// �I�u�W�F�N�g�^�C�v�ݒ�
	m_nPoint = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CFoodBase::~CFoodBase()
{

}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CFoodBase::Update(void)
{
	//�v���C���[�Ƃ̓����蔻��
	Collision();
}

//=============================================================================
// �����蔻��֐�
//=============================================================================
void CFoodBase::Collision(void)
{
	//�V�[���擾�p
	CScene* pTop[PRIORITY_MAX] = {};
	//���`�F�b�N����V�[���̃|�C���^
	CScene* pNext = NULL;
	//�ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	//top�̃A�h���X���擾
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		pTop[nCount] = *(CScene::GetTop() + nCount);
	}

	//�I�u�W�F�N�g�T��
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		if (pTop[nCount] != NULL)
		{
			pNext = pTop[nCount];
			//���̕`��D��x�̃I�u�W�F�N�g���Ȃ��Ȃ�܂Ń��[�v
			while (pNext != NULL)
			{
				if (pNext->GetObjType() == CScene::OBJTYPE_PLAYER)
				{
					//�v���C���[�̈ʒu�擾
					D3DXVECTOR3 PlayerPos = ((CPlayer*)pNext)->GetPos();
					
					//�v���C���[���߂��ɂ��邩
					if (PlayerPos.x + FOOD_HIT>pos.x
						&&PlayerPos.x - FOOD_HIT<pos.x
						&&PlayerPos.z + FOOD_HIT>pos.z
						&&PlayerPos.z - FOOD_HIT<pos.z)
					{
			
						//�擾��
						CSound *pSound = CManager::GetSound();
						pSound->PlaySound(CSound::LABEL_SE_GETSUSHI);

						//�p�[�c��ǉ�
						((CPlayer*)pNext)->AddParts(m_FoodType);

						//�X�R�A�A�b�v��ԂȂ������x�ǉ�
						if (((CPlayer*)pNext)->GetScoreUp() == true)
						{
							((CPlayer*)pNext)->AddParts(m_FoodType);
						}
						//�I�������ŏ���
						Uninit();
						return;
					}
				}
				//���̃I�u�W�F�N�g�̃|�C���^���X�V
				pNext = pNext->GetNext();
			}
		}
	}

}

//=============================================================================
// �|�C���g�Z�b�^�[�֐�
//=============================================================================
void CFoodBase::SetPoint(int nPoint)
{
	m_nPoint = nPoint;
}
