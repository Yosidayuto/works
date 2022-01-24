//=============================================================================
//
//	�X�R�A�w�i[score bar.cpp]
//	Author:�g�c�@�I�l
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "score bar.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �ÓI�����o�[�ϐ�
//=============================================================================
TEXTURE_DATA CScoreBar::m_TextureData = { NULL,"data/TEXTURE/UI_score.png" };
//=============================================================================
// �R���X�g���N�g
//=============================================================================
CScoreBar::CScoreBar(int nPriorit) :CScene2d(nPriorit)
{

}

//=============================================================================
// �e�N�X�`�����[�h����
//=============================================================================
HRESULT CScoreBar::Load(void)
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
void CScoreBar::Unload(void)
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
CScoreBar * CScoreBar::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�������m��
	CScoreBar* pScoreBar = NULL;
	pScoreBar = new CScoreBar;

	//NULL�`�F�b�N
	if (pScoreBar != NULL)
	{
		//�ʒu�ݒ�
		pScoreBar->SetPos(D3DXVECTOR3(pos.x, pos.y, pos.z));
		//�T�C�Y�ݒ�
		pScoreBar->SetSize(D3DXVECTOR3(size.x, size.y, size.z));
		//�e�N�X�`���ݒ�
		pScoreBar->BindTexture(m_TextureData.m_Texture);
		//����������
		pScoreBar->Init();
	}
	return pScoreBar;
}

