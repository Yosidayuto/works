//=============================================================================
//
// �G�t�F�N�g�p���i���� [effect sushi.h]
// Author : �g�c�I�l
//
//=============================================================================

//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "effect sushi.h"
#include "resource manager.h"
#include "renderer.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEffectSushi::CEffectSushi(int nPriority):CScene2d(nPriority)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEffectSushi::~CEffectSushi()
{
}

//=============================================================================
// ��������
//=============================================================================
CEffectSushi * CEffectSushi::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size, int nType)
{
	//�������m��
	CEffectSushi *pEffectSushi = nullptr;
	pEffectSushi = new CEffectSushi;

	//���\�[�X�m��(���\�[�X�}�l�[�W���[����Ăяo��)
	CResource* pResource = CManager::GetResource();
	LPDIRECT3DTEXTURE9 		Texture = pResource->TextureLoad(pEffectSushi->m_nEffectSushiTexture[nType]);

	//NULL�`�F�b�N
	if (pEffectSushi != nullptr)
	{
		pEffectSushi->BindTexture(Texture);
		pEffectSushi->SetPos(Pos);
		pEffectSushi->SetSize(Size);
		pEffectSushi->Init();
	}
	return pEffectSushi;

}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CEffectSushi::Draw(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	//�f�o�C�X�Ƀ����_���[�̃f�o�C�X����
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//Z�o�b�t�@��؂�
	pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

	//�A���t�@�e�X�g��L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//�A���t�@�e�X�g��l�̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	//�A���t�@�e�X�g�̔�r���@�̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	
	//�`�揈��
	CScene2d::Draw();

	//�A���t�@�e�X�g�𖳌���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//Z�o�b�t�@������
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

}


