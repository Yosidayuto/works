//=============================================================================
//
//	�z�[�~���O�A�C�R��[homing icon.cpp]
//	Author:�g�c�@�I�l
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "homing icon.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �ÓI�����o�[�ϐ�
//=============================================================================
TEXTURE_DATA CHomingIcon::m_TextureData = { NULL,"data/TEXTURE/UI_Homing.png" };
//=============================================================================
// �R���X�g���N�g
//=============================================================================
CHomingIcon::CHomingIcon()
{

}

//=============================================================================
// �e�N�X�`�����[�h����
//=============================================================================
HRESULT CHomingIcon::Load(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		m_TextureData.m_cFileName,
		&m_TextureData.m_Texture);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���j������
//=============================================================================
void CHomingIcon::Unload(void)
{
	//�e�N�X�`���̔j��
	if (m_TextureData.m_Texture != NULL)
	{
		m_TextureData.m_Texture->Release();
		m_TextureData.m_Texture = NULL;
	}
}

//=============================================================================
// ��������
//=============================================================================
CHomingIcon * CHomingIcon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�������m��
	CHomingIcon* pHomingIcon=NULL;
	pHomingIcon = new CHomingIcon;

	//NULL�`�F�b�N
	if (pHomingIcon != NULL)
	{
		//�ʒu�ݒ�
		pHomingIcon->SetPos(D3DXVECTOR3(pos.x, pos.y, pos.z));
		//�T�C�Y�ݒ�
		pHomingIcon->SetSize(D3DXVECTOR3(size.x, size.y, size.z));
		//�e�N�X�`���ݒ�
		pHomingIcon->BindTexture(m_TextureData.m_Texture);

		//����������
		pHomingIcon->Init();

	}

	return pHomingIcon;
}
