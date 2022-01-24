//=============================================================================
//
// �������Ԓʒm�̏��� [timecount ui.cpp]
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
#include "timecount ui.h"
#include "resource manager.h"

//*****************************************************************************
// �ÓI�����o�ϐ�������
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTimecountUi::CTimecountUi(int nPriority) : CScene2d(nPriority)
{
	m_nPatternAnim = 1;
	m_nCountAnim = 0;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTimecountUi::~CTimecountUi()
{

}

//=============================================================================
// ��������
//=============================================================================
CTimecountUi * CTimecountUi::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size)
{
	CTimecountUi *pMap = nullptr;

	pMap = new CTimecountUi;
	if (pMap != nullptr)
	{
		//���\�[�X�m��(���\�[�X�}�l�[�W���[����Ăяo��)
		CResource* pResource = CManager::GetResource();
		LPDIRECT3DTEXTURE9 Texture = pResource->TextureLoad(pMap->m_nTexture);
		pMap->BindTexture(Texture);
		pMap->SetPos(Pos);
		pMap->SetSize(Size);
		pMap->Init();
	}
	return pMap;
}

CTimecountUi * CTimecountUi::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Move, D3DXVECTOR3 Size)
{
	CTimecountUi *pMap = nullptr;

	pMap = new CTimecountUi;
	if (pMap != nullptr)
	{
		//���\�[�X�m��(���\�[�X�}�l�[�W���[����Ăяo��)
		CResource* pResource = CManager::GetResource();
		LPDIRECT3DTEXTURE9 Texture = pResource->TextureLoad(58);
		pMap->BindTexture(Texture);
		pMap->SetPos(Pos);
		pMap->SetSize(Size);
		pMap->m_move = Move;
		pMap->Init();
	}
	return pMap;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTimecountUi::Init(void)
{
	SetObjType(CScene::OBJTYPE_NONE);

	CScene2d::Init();

	//�e�N�X�`���Z�b�g
	D3DXVECTOR2 Tex[NUM_VERTEX];
	Tex[0] = D3DXVECTOR2(0.0f, 0.0f);
	Tex[1] = D3DXVECTOR2(1.0f, 0.0f);
	Tex[2] = D3DXVECTOR2(0.0f, 1.0f);
	Tex[3] = D3DXVECTOR2(1.0f, 1.0f);
	SetTexture(Tex);

	//���_�J���[�Z�b�g
	SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CTimecountUi::Uninit(void)
{
	CScene2d::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CTimecountUi::Update(void)
{
	CScene2d::Update();

	//�e�N�X�`���Z�b�g
	D3DXVECTOR2 Tex[NUM_VERTEX];
	Tex[0] = D3DXVECTOR2(0.0f, 0.0f);
	Tex[1] = D3DXVECTOR2(1.0f, 0.0f);
	Tex[2] = D3DXVECTOR2(0.0f, 1.0f);
	Tex[3] = D3DXVECTOR2(1.0f, 1.0f);
	SetTexture(Tex);

	//���_�J���[�Z�b�g
	SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));
	//�ʒu�X�V
	SetPos(GetPos() + m_move);

	if (GetPos().x <= -GetSize().x / 2)//��ʊO�ɍs���������
	{
		Uninit();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CTimecountUi::Draw(void)
{
	CScene2d::Draw();
}
