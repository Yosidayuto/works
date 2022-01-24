//=============================================================================
//
//  ���i�@�G�r�p�[�c [ebi parts.cpp]
//	Author:�g�c�I�l
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "ebi parts.h"
#include "renderer.h"
#include "resource manager.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEbiParts::CEbiParts()
{

}

//=============================================================================
// ���������֐�
//=============================================================================
CEbiParts * CEbiParts::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, D3DXVECTOR3 Size, CScene3d * pParent)
{
	//�������m��
	CEbiParts* pEbiPrts = NULL;
	pEbiPrts = new CEbiParts;
	//���\�[�X�m��(���\�[�X�}�l�[�W���[����Ăяo��)
	CResource* pResource = CManager::GetResource();
	LPDIRECT3DTEXTURE9 Texture = pResource->TextureLoad(pEbiPrts->m_nTexture);

	//NULL�`�F�b�N
	if (pEbiPrts != NULL)
	{
		//�ʒu�ݒ�
		pEbiPrts->SetPos(Pos);
		//�����ݒ�
		pEbiPrts->SetRot(Rot);
		//�T�C�Y�ݒ�
		pEbiPrts->SetSize(Size);
		//�e�p�[�c�|�C���^�擾
		pEbiPrts->SetParent(pParent);
		//�^�C�v�ݒ�
		pEbiPrts->SetType(CFoodBase::TYPE_EBI);
		//�e�N�X�`���ݒ�
		pEbiPrts->BindTexture(Texture);
		//����������
		pEbiPrts->Init();
	}

	return pEbiPrts;
}
