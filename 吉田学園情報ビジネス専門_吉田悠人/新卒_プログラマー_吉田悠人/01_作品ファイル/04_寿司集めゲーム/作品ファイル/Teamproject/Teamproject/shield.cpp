//=============================================================================
//
// �A�C�e��[shield.h]
// Author : �V����s
//
//=============================================================================
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "shield.h"
#include "resource manager.h"
#include "manager.h"
#include "renderer.h"
#include "scoreup.h"
#include "player.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CShield::CShield()
{
}

//=============================================================================
// ���������֐�
//=============================================================================
CShield * CShield::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�������[�m��
	CShield *pShield;
	pShield = new CShield;

	//Resource�̌Ăяo��
	CResource* pResource = CManager::GetResource();
	MODELDATA Model = pResource->ModelLoad(pShield->m_nShieldModel);

	//NULL�`�F�b�N
	if (pShield != NULL)
	{
		pShield->SetPos(pos);			// �ʒu�ݒ�
		pShield->SetSize(size);			// �T�C�Y�ݒ�
		pShield->SetItem(ITEM_SHIELD);
		pShield->SetModelData(Model);	// ���f���ݒ�
		pShield->Init();				//����������
	}
	return pShield;
}

void CShield::ItemEffect(CPlayer* pPlayer)
{
	//�V�[���h�̏���
	pPlayer->ShieldGet();
}


