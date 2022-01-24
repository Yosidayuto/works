//=============================================================================
//
// �������Ԓʒm�̏��� [gameend ui.cpp]
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
#include "gameend ui.h"
#include "resource manager.h"

//*****************************************************************************
// �ÓI�����o�ϐ�������
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGameEndUi::CGameEndUi(int nPriority) : CScene2d(nPriority)
{
	m_nPatternAnim = 1;
	m_nCountAnim = 0;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGameEndUi::~CGameEndUi()
{

}

//=============================================================================
// ��������
//=============================================================================
CGameEndUi * CGameEndUi::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size)
{
	CGameEndUi *pMap = nullptr;

	pMap = new CGameEndUi;
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

CGameEndUi * CGameEndUi::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Move, D3DXVECTOR3 Size)
{
	CGameEndUi *pMap = nullptr;

	pMap = new CGameEndUi;
	if (pMap != nullptr)
	{
		//���\�[�X�m��(���\�[�X�}�l�[�W���[����Ăяo��)
		CResource* pResource = CManager::GetResource();
		LPDIRECT3DTEXTURE9 Texture = pResource->TextureLoad(59);
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
HRESULT CGameEndUi::Init(void)
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
void CGameEndUi::Uninit(void)
{
	CScene2d::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CGameEndUi::Update(void)
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

	if (GetPos().y >= SCREEN_CENTER_Y)
	{
		m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CGameEndUi::Draw(void)
{
	CScene2d::Draw();
}
