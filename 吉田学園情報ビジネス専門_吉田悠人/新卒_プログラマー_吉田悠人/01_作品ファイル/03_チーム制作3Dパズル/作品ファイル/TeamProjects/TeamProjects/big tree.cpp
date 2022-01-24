//=============================================================================
//
// �j�t���i�����j [big tree.cpp]
// Author : �g�c�I�l
//
//=============================================================================

//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "big tree.h"
#include "resource manager.h"
#include "manager.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBigTree::CBigTree()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBigTree::~CBigTree()
{
}

//=============================================================================
// �����֐�
//=============================================================================
CBigTree * CBigTree::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	//�������m��
	CBigTree* pBigTree = NULL;
	pBigTree = new CBigTree;
	//���\�[�X�m��
	CResource* pResource = CManager::GetResource();
	CModel::MODELDATA Model = pResource->ModelLoad(pBigTree->m_nModel);

	//NULL�`�F�b�N
	if (pBigTree != NULL)
	{
		//�ʒu�ݒ�
		pBigTree->SetPosition(D3DXVECTOR3(pos.x, pos.y + HINDRANCE_HEIGHT, pos.z));
		//�����ݒ�
		pBigTree->SetRotation(rot);
		//�J���[�ݒ�
		pBigTree->SetScale(size);
		//���f���ݒ�
		pBigTree->SetModelData(Model);
		//����������
		pBigTree->Init();
	}

	return pBigTree;
}

