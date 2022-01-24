//=============================================================================
//
// �v���C���[�̔ԍ�UI [player number.h]
// Author : �g�c�I�l
//
//=============================================================================

//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "player number.h"
#include "resource manager.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPlayerNumber::CPlayerNumber()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPlayerNumber::~CPlayerNumber()
{
}

//=============================================================================
// ��������
//=============================================================================
CPlayerNumber * CPlayerNumber::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nNumber)
{
	//�������m��
	CPlayerNumber *pPlayerNumber;
	pPlayerNumber = new CPlayerNumber;
	//���\�[�X�m��(���\�[�X�}�l�[�W���[����Ăяo��)
	CResource* pResource = CManager::GetResource();
	LPDIRECT3DTEXTURE9 Texture = pResource->TextureLoad(pPlayerNumber->nPlayerNumberTexture[nNumber]);

	//NULL�`�F�b�N
	if (pPlayerNumber != nullptr)
	{
		pPlayerNumber->BindTexture(Texture);
		pPlayerNumber->SetPos(pos);
		pPlayerNumber->SetSize(size);
		pPlayerNumber->Init();
	}
	return pPlayerNumber;
}
