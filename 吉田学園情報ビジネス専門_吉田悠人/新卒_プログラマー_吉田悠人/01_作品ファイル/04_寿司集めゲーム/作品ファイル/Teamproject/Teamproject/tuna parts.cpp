//=============================================================================
//
// ���i�@�}�O���p�[�c [tuna parts.cpp]
//	Author:�g�c�I�l
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "tuna parts.h"
#include "renderer.h"
#include "resource manager.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTunaParts::CTunaParts()
{

}

//=============================================================================
// ���������֐�
//=============================================================================
CTunaParts * CTunaParts::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, D3DXVECTOR3 Size, CScene3d * pParent)
{
	//�������m��
	CTunaParts* pTunaPrts = NULL;
	pTunaPrts = new CTunaParts;
	//���\�[�X�m��(���\�[�X�}�l�[�W���[����Ăяo��)
	CResource* pResource = CManager::GetResource();
	LPDIRECT3DTEXTURE9 Texture = pResource->TextureLoad(pTunaPrts->m_nTexture);

	//NULL�`�F�b�N
	if (pTunaPrts != NULL)
	{
		//�ʒu�ݒ�
		pTunaPrts->SetPos(Pos);
		//�����ݒ�
		pTunaPrts->SetRot(Rot);
		//�T�C�Y�ݒ�
		pTunaPrts->SetSize(Size);
		//�e�p�[�c�|�C���^�擾
		pTunaPrts->SetParent(pParent);
		//�^�C�v�ݒ�
		pTunaPrts->SetType(CFoodBase::TYPE_TUNA);
		//�e�N�X�`���ݒ�
		pTunaPrts->BindTexture(Texture);
		//����������
		pTunaPrts->Init();
	}

	return pTunaPrts;
}
