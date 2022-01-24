//=============================================================================
//
// �g���b�v���� [trap.cpp]
// Author : �g�c�I�l
//
//=============================================================================


//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "trap.h"
#include "explosion.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "sound.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTrap::CTrap()
{
	m_Startpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Endpos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_pTexture = NULL;
	SetObjType(OBJTYPE_NONE);
}

//=============================================================================
// ���������֐�
//=============================================================================
CTrap * CTrap::Create(D3DXVECTOR3 Startpos, D3DXVECTOR3 Endpos)
{
	//�������m��
	CTrap* pTrap = NULL;
	pTrap = new CTrap;

	//�������m�ۂ����ꂽ��
	if (pTrap!=NULL)
	{
		//�g���b�v�̐��̃X�^�[�g�ʒu�擾
		pTrap->m_Startpos = Startpos;
		//�g���b�v�̐��̏I���ʒu�擾
		pTrap->m_Endpos = Endpos;
		//�ʒu�ݒ�i�X�^�[�g�ʒu�ƏI���ʒu�Ōv�Z�j
		pTrap->SetPosition((Startpos + Endpos) / 2);
		//�����ݒ�i�X�^�[�g�ʒu�ƏI���ʒu�Ōv�Z�j
		pTrap->SetRotation(D3DXVECTOR3(90.0f, D3DXToDegree(atan2f((Startpos.x - Endpos.x), (Startpos.z - Endpos.z))), 0.0f));
		//�T�C�Y�ݒ�i�X�^�[�g�ʒu�ƏI���ʒu�Ōv�Z�j
		pTrap->SetSize(D3DXVECTOR3(1.0f, sqrtf(((Startpos.x - Endpos.x)*(Startpos.x - Endpos.x)) + ((Startpos.z - Endpos.z)*(Startpos.z - Endpos.z))), 1.0f));
		//�J���[�ݒ�
		for (int nMesh = 0; nMesh < MESH_Y_BLOCK + 1; nMesh++)
		{
			pTrap->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f - (nMesh*0.1f)), nMesh);
		}
		//����������
		pTrap->Init();
	}
	return pTrap;
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CTrap::Update(void)
{
	//���X�g�擾�p
	CObject* pTop[PRIORITY_MAX] = {};
	CObject* pNext = NULL;
	//�T�E���h�̎擾
	CSound* pSound = CManager::GetSound();   

	//���X�g�g�b�v�擾
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		pTop[nCount] = *(CObject::GetTop() + nCount);
	}

	//����
	float fDistanve;

	//���X�g�̗D�揇�ɓǂݍ���
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		//NULL�`�F�b�N
		if (pTop[nCount] != NULL)
		{
			//�ۑ�
			pNext = pTop[nCount];
			while (pNext != NULL)
			{
				//�I�u�W�F�N�g�^�C�v�`�F�b�N
				if (pNext->GetObjType() == OBJTYPE_MODEL)
				{
					//NULL�`�F�b�N
					if (((CModel *)pNext)->GetParentObject() != NULL)
					{
						//�I�u�W�F�N�g���v���C���[��
						if (((CModel*)pNext)->GetParentObject()->GetObjType() == OBJTYPE_PLAYER)
						{
							//�v���C���[���G�ꂽ��
							if (Search(((CModel*)pNext)->GetModelData(), fDistanve) == TRUE)
							{
								if (GetSize().y>fDistanve)
								{
									//���j
									CExplosion::Create(D3DXVECTOR3(CManager::GetPlayer()->GetPos().x, CManager::GetPlayer()->GetPos().y + 30, CManager::GetPlayer()->GetPos().z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(100, 100, 100));

									//�v���C���[�_���[�W
									CManager::GetPlayer()->AddLife(-45);

									//�I������
									Uninit();
								}
							}
						}
					}
				}
				//���̑Ώۂ�ǂݍ���
				pNext = pNext->GetNext();
			}
		}
	}
	//�X�V����
	CMeshCylinder::Update();
}


//=============================================================================
// ���m�֐�
//=============================================================================
BOOL CTrap::Search(CModel::MODELDATA modeldata, float &fDistanve)
{
	BOOL bSearch = FALSE;			//�������Ă��邩
	D3DXMATRIX mtxWorld;
	D3DXMATRIX InversedWorldMatrix;	//�t��p�}�g���b�N�X
	D3DXVECTOR3 TransformedPos, NormalizedVec, TranceformedVec;

	//�P�ʃx�N�g���ɕϊ�
	D3DXVec3Normalize(&NormalizedVec, &(m_Endpos - m_Startpos));
	//�t�s�񐶐�
	D3DXMatrixInverse(&InversedWorldMatrix, NULL, &modeldata.mtxWorld);
	//�t�s��ŕϊ�
	D3DXVec3TransformCoord(&TransformedPos, &m_Startpos, &InversedWorldMatrix);
	D3DXVec3TransformNormal(&TranceformedVec, &NormalizedVec, &InversedWorldMatrix);
	//�����蔻����m�F
	D3DXIntersect(modeldata.pMesh, &TransformedPos, &TranceformedVec, &bSearch, NULL, NULL, NULL, &fDistanve, NULL, NULL);
	return bSearch;

}


