//=============================================================================
//
// �X�R�A������(�}�C)��UI [classifier.cpp]
// Author : �g�c�I�l
//
//=============================================================================

//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "classifier.h"
#include "resource manager.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CClassifier::CClassifier()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CClassifier::~CClassifier()
{
}

//=============================================================================
// ��������
//=============================================================================
CClassifier * CClassifier::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�������m��
	CClassifier *pClassifier;
	pClassifier = new CClassifier;
	//���\�[�X�m��(���\�[�X�}�l�[�W���[����Ăяo��)
	CResource* pResource = CManager::GetResource();
	LPDIRECT3DTEXTURE9 Texture = pResource->TextureLoad(pClassifier->nClassifierTexture);

	//NULL�`�F�b�N
	if (pClassifier != nullptr)
	{
		pClassifier->BindTexture(Texture);
		pClassifier->SetPos(pos);
		pClassifier->SetSize(size);
		pClassifier->Init();
	}
	return pClassifier;
}
