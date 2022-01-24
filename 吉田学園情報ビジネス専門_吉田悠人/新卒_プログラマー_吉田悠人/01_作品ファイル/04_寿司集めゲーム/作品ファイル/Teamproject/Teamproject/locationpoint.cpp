//=============================================================================
//
// �v���C���[���݈ʒu�̏���[locationpoint.cpp]
// Author : �ѐ�ї���
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "locationpoint.h"
#include "resource manager.h"

//*****************************************************************************
// �ÓI�����o�ϐ�������
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CLocationPoint::CLocationPoint(int nPriority) : CScene2d(nPriority)
{
	m_nPatternAnim = 1;
	m_nCountAnim = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CLocationPoint::~CLocationPoint()
{

}

//=============================================================================
// ��������
//=============================================================================
CLocationPoint * CLocationPoint::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size, int number)
{
	CLocationPoint *pLocationPoint = nullptr;

	pLocationPoint = new CLocationPoint;
	if (pLocationPoint != nullptr)
	{
		//���\�[�X�m��(���\�[�X�}�l�[�W���[����Ăяo��)
		CResource* pResource = CManager::GetResource();
		LPDIRECT3DTEXTURE9 Texture = pResource->TextureLoad(pLocationPoint->m_nTexture);
		pLocationPoint->BindTexture(Texture);
		pLocationPoint->m_nPlayerNum = number;
		pLocationPoint->SetPos(Pos);
		pLocationPoint->SetSize(Size);
		pLocationPoint->Init();
	}
	return pLocationPoint;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CLocationPoint::Init(void)
{
	SetObjType(CScene::OBJTYPE_NONE);

	CScene2d::Init();

	//�e�N�X�`���Z�b�g
	D3DXVECTOR2 Tex[NUM_VERTEX];
	Tex[0] = D3DXVECTOR2(m_nPlayerNum * 0.25f, 0.0f);
	Tex[1] = D3DXVECTOR2(m_nPlayerNum * 0.25f + 0.25f, 0.0f);
	Tex[2] = D3DXVECTOR2(m_nPlayerNum * 0.25f, 1.0f);
	Tex[3] = D3DXVECTOR2(m_nPlayerNum * 0.25f + 0.25f, 1.0f);
	SetTexture(Tex);
	//���_�J���[�Z�b�g
	SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));
	return S_OK;
}


//=============================================================================
// �X�V����
//=============================================================================
void CLocationPoint::Update(void)
{
	CScene2d::Update();

	//�e�N�X�`���Z�b�g
	D3DXVECTOR2 Tex[NUM_VERTEX];
	Tex[0] = D3DXVECTOR2(m_nPlayerNum * 0.25f, 0.0f);
	Tex[1] = D3DXVECTOR2(m_nPlayerNum * 0.25f + 0.25f, 0.0f);
	Tex[2] = D3DXVECTOR2(m_nPlayerNum * 0.25f, 1.0f);
	Tex[3] = D3DXVECTOR2(m_nPlayerNum * 0.25f + 0.25f, 1.0f);
	SetTexture(Tex);

	//���_�J���[�Z�b�g
	SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));
}

