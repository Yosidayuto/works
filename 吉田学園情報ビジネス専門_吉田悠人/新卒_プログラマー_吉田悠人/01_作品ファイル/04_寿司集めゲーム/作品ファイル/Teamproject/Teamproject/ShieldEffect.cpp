//=============================================================================
//
// �V�[���h�G�t�F�N�g�̏��� [ShieldEffect.cpp]
// Author : �V����s
//
//=============================================================================

//=============================================================================
// �w�b�_�[�t�@�C��
//=============================================================================
#include "ShieldEffect.h"
#include "resource manager.h"
#include "player.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CShieldEffect::CShieldEffect(int nPriority) :CBillboard(nPriority)
{
	SetObjType(CScene::OBJTYPE_NONE);	//�^�C�v�ݒ�
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CShieldEffect::~CShieldEffect()
{
}

//=============================================================================
// �����֐�
//=============================================================================
CShieldEffect * CShieldEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR Col, CPlayer* pPlayer)
{
	// �������m��
	CShieldEffect *pShieldEffect = NULL;
	pShieldEffect = new CShieldEffect;

	//���\�[�X�f�[�^�擾
	CResource* pResource = CManager::GetResource();
	LPDIRECT3DTEXTURE9 Texture = pResource->TextureLoad(pShieldEffect->m_nTexture);

	//NULL�`�F�b�N
	if (pShieldEffect != NULL)
	{
		pShieldEffect->SetPos(pos);				// �ʒu�ݒ�
		pShieldEffect->SetSize(size);			// �T�C�Y�ݒ�
		pShieldEffect->SetColor(Col);			// �J���[�ݒ�
		pShieldEffect->BindTexture(Texture);	// �e�N�X�`���ݒ�
		pShieldEffect->m_pPlayer = pPlayer;		// �v���C���[�|�C���^�擾
		pShieldEffect->Init();					// ����������
	}

	return pShieldEffect;
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CShieldEffect::Update(void)
{
	//�v���C���[�̈ʒu�擾
	D3DXVECTOR3 pos = m_pPlayer->GetPos();
	//�v���C���[�̈ʒu�ɍ��킹�ăZ�b�g
	SetPos(D3DXVECTOR3(pos.x, pos.y + 13.0f, pos.z));

	//�v���C���[�̏󋵂ɍ��킹�ď���
	if (m_pPlayer->GetShield() == false)
	{
		CShieldEffect::Uninit();
	}
}
