//=============================================================================
//
//  ���i�@�C�N���p�[�c [ikura parts.cpp]
//	Author:�g�c�I�l
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "ikura parts.h"
#include "renderer.h"
#include "resource manager.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CIkuraParts::CIkuraParts()
{

}

//=============================================================================
// ���������֐�
//=============================================================================
CIkuraParts * CIkuraParts::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, D3DXVECTOR3 Size, CScene3d * pParent)
{
	//�������m��
	CIkuraParts* pIkuraPrts = NULL;
	pIkuraPrts = new CIkuraParts;
	//���\�[�X�m��(���\�[�X�}�l�[�W���[����Ăяo��)
	CResource* pResource = CManager::GetResource();
	LPDIRECT3DTEXTURE9 Texture = pResource->TextureLoad(pIkuraPrts->m_nTexture);

	//NULL�`�F�b�N
	if (pIkuraPrts != NULL)
	{
		//�ʒu�ݒ�
		pIkuraPrts->SetPos(Pos);
		//�����ݒ�
		pIkuraPrts->SetRot(Rot);
		//�T�C�Y�ݒ�
		pIkuraPrts->SetSize(Size);
		//�e�p�[�c�|�C���^�擾
		pIkuraPrts->SetParent(pParent);
		//�^�C�v�ݒ�
		pIkuraPrts->SetType(CFoodBase::TYPE_IKURA);
		//�e�N�X�`���ݒ�
		pIkuraPrts->BindTexture(Texture);
		//����������
		pIkuraPrts->Init();
	}

	return pIkuraPrts;
}
