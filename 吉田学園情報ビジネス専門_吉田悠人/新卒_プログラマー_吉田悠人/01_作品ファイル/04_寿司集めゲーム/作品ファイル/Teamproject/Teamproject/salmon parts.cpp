//=============================================================================
//
//  ���i�@�T�[�����p�[�c [salmon parts.cpp]
//	Author:�g�c�I�l
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "salmon parts.h"
#include "renderer.h"
#include "resource manager.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CSalmonParts::CSalmonParts()
{

}

//=============================================================================
// ���������֐�
//=============================================================================
CSalmonParts * CSalmonParts::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, D3DXVECTOR3 Size, CScene3d * pParent)
{
	//�������m��
	CSalmonParts* pSalmonPrts = NULL;
	pSalmonPrts = new CSalmonParts;
	//���\�[�X�m��(���\�[�X�}�l�[�W���[����Ăяo��)
	CResource* pResource = CManager::GetResource();
	LPDIRECT3DTEXTURE9 Texture = pResource->TextureLoad(pSalmonPrts->m_nTexture);

	//NULL�`�F�b�N
	if (pSalmonPrts != NULL)
	{
		//�ʒu�ݒ�
		pSalmonPrts->SetPos(Pos);
		//�����ݒ�
		pSalmonPrts->SetRot(Rot);
		//�T�C�Y�ݒ�
		pSalmonPrts->SetSize(Size);
		//�e�p�[�c�|�C���^�擾
		pSalmonPrts->SetParent(pParent);
		//�^�C�v�ݒ�
		pSalmonPrts->SetType(CFoodBase::TYPE_SALMON);
		//�e�N�X�`���ݒ�
		pSalmonPrts->BindTexture(Texture);
		//����������
		pSalmonPrts->Init();
	}

	return pSalmonPrts;
}
