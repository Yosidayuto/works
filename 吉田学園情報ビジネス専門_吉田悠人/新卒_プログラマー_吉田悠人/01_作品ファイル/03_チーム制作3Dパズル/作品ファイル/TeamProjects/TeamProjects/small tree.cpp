//=============================================================================
//
// �j�t��(������) [small tree.cpp]
// Author : �g�c�I�l
//
//=============================================================================

//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "small tree.h"
#include "resource manager.h"
#include "manager.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CSmallTree::CSmallTree()
{
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CSmallTree::~CSmallTree()
{
}

//=============================================================================
// �����֐�
//=============================================================================
CSmallTree * CSmallTree::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	//�������m��
	CSmallTree* pSmallTree = NULL;
	pSmallTree = new CSmallTree;
	//���\�[�X�m��
	CResource* pResource = CManager::GetResource();
	CModel::MODELDATA Model = pResource->ModelLoad(pSmallTree->m_nModel);

	//NULL�`�F�b�N
	if (pSmallTree != NULL)
	{
		//�ʒu�ݒ�
		pSmallTree->SetPosition(D3DXVECTOR3(pos.x, pos.y + HINDRANCE_HEIGHT, pos.z));
		//�����ݒ�
		pSmallTree->SetRotation(rot);
		//�J���[�ݒ�
		pSmallTree->SetScale(size);
		//���f���ݒ�
		pSmallTree->SetModelData(Model);
		//����������
		pSmallTree->Init();
	}

	return pSmallTree;
}
