//=============================================================================
//
// �G�t�F�N�g���� [effect.h]
// Author : �ѐ�ї���
//
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "billboard.h"
#include "effect 3d.h"
#include "resource manager.h"
//****************************************************************************************************
//�ÓI�����o�ϐ��錾
//****************************************************************************************************
LPDIRECT3DTEXTURE9 CEffect::m_apTexture = nullptr;
//****************************************************************************************************
// �R���X�g���N�^
//****************************************************************************************************
CEffect::CEffect(int nPriority) : CBillboard(nPriority)
{
	m_nLife = 0;
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pPlayer = nullptr;
}
//****************************************************************************************************
// �f�X�g���N�^
//****************************************************************************************************
CEffect::~CEffect()
{
}

//****************************************************************************************************
// �����֐�
//****************************************************************************************************
CEffect * CEffect::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Move, D3DXVECTOR3 Size, D3DXCOLOR col, int nLife, int TexNum)
{
	CEffect *pEffect = nullptr;

	pEffect = new CEffect;
	if (pEffect != nullptr)
	{
		//���\�[�X�m��(���\�[�X�}�l�[�W���[����Ăяo��)
		CResource* pResource = CManager::GetResource();
		LPDIRECT3DTEXTURE9 Texture = pResource->TextureLoad(TexNum);
		pEffect->BindTexture(Texture);
		pEffect->SetPos(Pos);
		pEffect->SetSize(Size);
		pEffect->SetColor(col);
		pEffect->m_Move = Move;
		pEffect->m_nLife = nLife;
		pEffect->Init();
	}

	return pEffect;
}

CEffect * CEffect::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Move, D3DXVECTOR3 Size, D3DXCOLOR col, int nLife, int TexNum, CPlayer * pPlayer)
{
	CEffect *pEffect = nullptr;

	pEffect = new CEffect;
	if (pEffect != nullptr)
	{
		//���\�[�X�m��(���\�[�X�}�l�[�W���[����Ăяo��)
		CResource* pResource = CManager::GetResource();
		LPDIRECT3DTEXTURE9 Texture = pResource->TextureLoad(TexNum);
		pEffect->BindTexture(Texture);
		pEffect->SetPos(Pos);
		pEffect->SetSize(Size);
		pEffect->SetColor(col);
		pEffect->m_Move = Move;
		pEffect->m_nLife = nLife;
		pEffect->m_pPlayer = pPlayer;
		pEffect->Init();
	}

	return pEffect;
}

//=============================================================================
// ������
//=============================================================================
HRESULT CEffect::Init(void)
{
	// ������
	CBillboard::Init();

	return S_OK;
}
//=============================================================================
// �j��
//=============================================================================
void CEffect::Uninit(void)
{
	// �I��
	CBillboard::Uninit();
}
//=============================================================================
// �X�V
//=============================================================================
void CEffect::Update(void)
{
	// �ǂ�ǂ񏬂����ǂ�ǂ񓧖���
	SetSize(GetSize() - D3DXVECTOR3(GetSize().x / m_nLife, GetSize().y / m_nLife, GetSize().z / m_nLife));
	SetColor(D3DXCOLOR(GetColor().r, GetColor().g, GetColor().b, GetColor().a - (1.0f / m_nLife)));

	m_nLife--;
	

	//��莞�ԂŔj��
	if (m_nLife <= 0)
	{
		Uninit();
		return;
	}
	if (m_pPlayer != nullptr)
	{
		//�ʒu�X�V
		SetPos(D3DXVECTOR3(m_pPlayer->GetPos().x, GetPos().y, m_pPlayer->GetPos().z) + m_Move);
	}
	else
	{
		//�ʒu�X�V
		SetPos(GetPos() + m_Move);
	}

	// �X�V
	CBillboard::Update();
}
//=============================================================================
// �`�揈��
//=============================================================================
void CEffect::Draw(void)
{
	CRenderer * pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//���Z����
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	// �`��
	CBillboard::Draw();
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}

void CEffect::SetLife(int nLife)
{
	m_nLife = nLife;
}
