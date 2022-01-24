//=============================================================================
//
// ���i�@�T�[���� [salmon.cpp]
// Author : �g�c�I�l
//
//=============================================================================

//=============================================================================
// �w�b�_�[�t�@�C��
//=============================================================================
#include "salmon.h"
#include "resource manager.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define SALMON_SCORE (10)

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CSalmon::CSalmon(int nPriority) : CFoodBase(nPriority)
{

}

//=============================================================================
// ���������֐�
//=============================================================================
CSalmon * CSalmon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�������̊m��
	CSalmon *pSalmon;
	pSalmon = new CSalmon;

	//���\�[�X�m��(���\�[�X�}�l�[�W���[����Ăяo��)
	CResource* pResource = CManager::GetResource();
	LPDIRECT3DTEXTURE9 Texture = pResource->TextureLoad(pSalmon->m_nTexture);

	//NULL�`�F�b�N
	if (pSalmon != NULL)
	{
		pSalmon->SetPos(pos);				// �ʒu�ݒ�
		pSalmon->SetSize(size);				// �T�C�Y�ݒ�
		pSalmon->SetPoint(SALMON_SCORE);	// �X�R�A�ݒ�
		pSalmon->BindTexture(Texture);		// �e�N�X�`���ݒ�
		pSalmon->SetFoodType(TYPE_SALMON);	// �^�C�v�ݒ�
		pSalmon->Init();					// ����������
	}

	return pSalmon;
}
