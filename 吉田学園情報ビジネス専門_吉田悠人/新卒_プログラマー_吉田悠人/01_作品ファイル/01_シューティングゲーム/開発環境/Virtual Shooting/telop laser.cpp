//=============================================================================
//
//	���[�U�[�e���b�v[telop laser.cpp]
//	Author:�g�c�@�I�l
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "telop laser.h"
#include "telop.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �ÓI�����o�[�ϐ�
//=============================================================================
TEXTURE_DATA CTelopLaser::m_TextureData = { NULL,"data/TEXTURE/Telop_Laser.png" };
//=============================================================================
// �R���X�g���N�g
//=============================================================================
CTelopLaser::CTelopLaser(int nPriorit) :CScene2d(nPriorit)
{
}

//=============================================================================
// �e�N�X�`�����[�h����
//=============================================================================
HRESULT CTelopLaser::Load(void)
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
void CTelopLaser::Unload(void)
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
CTelopLaser * CTelopLaser::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�������m��
	CTelopLaser* pTelopLaser = NULL;
	pTelopLaser = new CTelopLaser;

	//NULL�`�F�b�N
	if (pTelopLaser != NULL)
	{
		//�ʒu�ݒ�
		pTelopLaser->SetPos(D3DXVECTOR3(pos.x - TELOP_X_SIZE, pos.y, pos.z));
		//�T�C�Y�ݒ�
		pTelopLaser->SetSize(D3DXVECTOR3(size.x - TELOP_X_SIZE / 2, size.y, size.z));
		//�e�N�X�`���ݒ�
		pTelopLaser->BindTexture(m_TextureData.m_Texture);

		//����������
		pTelopLaser->Init();


	}
	return pTelopLaser;
}
