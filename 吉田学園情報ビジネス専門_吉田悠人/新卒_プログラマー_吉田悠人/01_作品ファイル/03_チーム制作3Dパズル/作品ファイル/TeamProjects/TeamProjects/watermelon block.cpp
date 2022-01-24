//=============================================================================
//
// �X�C�J�u���b�N [watermelon block.cpp]
// Author : �g�c�I�l
//
//=============================================================================

//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "watermelon block.h"
#include "resource manager.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CWatermelonBlock::CWatermelonBlock()
{
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CWatermelonBlock::~CWatermelonBlock()
{
}


//=============================================================================
// �����֐�
//=============================================================================
CWatermelonBlock * CWatermelonBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	//�������m��
	CWatermelonBlock* pWatermelonBlock = NULL;
	pWatermelonBlock = new CWatermelonBlock;
	//���\�[�X�m��
	CResource* pResource = CManager::GetResource();
	CModel::MODELDATA Model = pResource->ModelLoad(pWatermelonBlock->m_nModel);

	//NULL�`�F�b�N
	if (pWatermelonBlock != NULL)
	{
		//�ʒu�ݒ�
		pWatermelonBlock->SetPosition(D3DXVECTOR3(pos.x, pos.y + ITEM_HEIGHT+20, pos.z));
		//�����ݒ�
		pWatermelonBlock->SetRotation(rot);
		//�J���[�ݒ�
		pWatermelonBlock->SetScale(size);
		//���f���ݒ�
		pWatermelonBlock->SetModelData(Model);
		//����������
		pWatermelonBlock->Init();
	}

	return pWatermelonBlock;
}
