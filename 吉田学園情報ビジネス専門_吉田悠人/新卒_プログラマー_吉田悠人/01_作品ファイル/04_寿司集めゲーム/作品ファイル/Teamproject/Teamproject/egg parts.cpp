//=============================================================================
//
// ���i�@���p�[�c [egg parts.cpp]
//	Author:�g�c�I�l
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "egg parts.h"
#include "renderer.h"
#include "resource manager.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEggParts::CEggParts()
{

}

//=============================================================================
// ���������֐�
//=============================================================================
CEggParts * CEggParts::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, D3DXVECTOR3 Size, CScene3d * pParent)
{
	//�������m��
	CEggParts* pEggPrts = NULL;
	pEggPrts = new CEggParts;
	//���\�[�X�m��(���\�[�X�}�l�[�W���[����Ăяo��)
	CResource* pResource = CManager::GetResource();
	LPDIRECT3DTEXTURE9 Texture = pResource->TextureLoad(pEggPrts->m_nTexture);

	//NULL�`�F�b�N
	if (pEggPrts != NULL)
	{
		//�ʒu�ݒ�
		pEggPrts->SetPos(Pos);
		//�����ݒ�
		pEggPrts->SetRot(Rot);
		//�T�C�Y�ݒ�
		pEggPrts->SetSize(Size);
		//�e�p�[�c�|�C���^�擾
		pEggPrts->SetParent(pParent);
		//�^�C�v�ݒ�
		pEggPrts->SetType(CFoodBase::TYPE_EGG);
		//�e�N�X�`���ݒ�
		pEggPrts->BindTexture(Texture);
		//����������
		pEggPrts->Init();
	}

	return pEggPrts;
}
