//=============================================================================
//
// �~�J���u���b�N [oranges block.cpp]
// Author : �g�c�I�l
//
//=============================================================================

//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "oranges block.h"
#include "resource manager.h"
#include "manager.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
COrangesBlock::COrangesBlock()
{
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
COrangesBlock::~COrangesBlock()
{
}


//=============================================================================
// �����֐�
//=============================================================================
COrangesBlock * COrangesBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	//�������m��
	COrangesBlock* pOrangesBlock = NULL;
	pOrangesBlock = new COrangesBlock;
	//���\�[�X�m��
	CResource* pResource = CManager::GetResource();
	CModel::MODELDATA Model = pResource->ModelLoad(pOrangesBlock->m_nModel);

	//NULL�`�F�b�N
	if (pOrangesBlock != NULL)
	{
		//�ʒu�ݒ�
		pOrangesBlock->SetPosition(D3DXVECTOR3(pos.x, pos.y + ITEM_HEIGHT, pos.z));
		//�����ݒ�
		pOrangesBlock->SetRotation(rot);
		//�J���[�ݒ�
		pOrangesBlock->SetScale(size);
		//���f���ݒ�
		pOrangesBlock->SetModelData(Model);
		//����������
		pOrangesBlock->Init();
	}

	return pOrangesBlock;
}

