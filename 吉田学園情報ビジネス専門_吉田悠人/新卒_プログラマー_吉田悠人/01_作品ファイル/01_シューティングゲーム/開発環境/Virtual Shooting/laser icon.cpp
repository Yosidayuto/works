//=============================================================================
//
//	���[�U�[�A�C�R��[laser icon.cpp]
//	Author:�g�c�@�I�l
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "laser icon.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �ÓI�����o�[�ϐ�
//=============================================================================
TEXTURE_DATA CLaserIcon::m_TextureData = { NULL,"data/TEXTURE/UI_Laser.png" };
//=============================================================================
// �R���X�g���N�g
//=============================================================================
CLaserIcon::CLaserIcon()
{

}

//=============================================================================
// �e�N�X�`�����[�h����
//=============================================================================
HRESULT CLaserIcon::Load(void)
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
void CLaserIcon::Unload(void)
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
CLaserIcon * CLaserIcon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�������m��
	CLaserIcon* pLaserIcon=NULL;
	pLaserIcon = new CLaserIcon;

	//NULL�`�F�b�N
	if (pLaserIcon != NULL)
	{
		//�ʒu�ݒ�
		pLaserIcon->SetPos(D3DXVECTOR3(pos.x, pos.y, pos.z));
		//�T�C�Y�ݒ�
		pLaserIcon->SetSize(D3DXVECTOR3(size.x, size.y, size.z));
		//�e�N�X�`���ݒ�
		pLaserIcon->BindTexture(m_TextureData.m_Texture);

		//����������
		pLaserIcon->Init();

	}
	return pLaserIcon;
}

