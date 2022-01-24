//=============================================================================
//
// ���̏��� [floor.cpp]
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
#include "polygon3d.h"
#include "floor.h"
#include "resource manager.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CFloor::CFloor(int nPriority) : CPolygon3d(nPriority)
{
	m_nPatternAnim = 0;
	m_nCountAnim = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CFloor::~CFloor()
{

}

//=============================================================================
// ��������
//=============================================================================
CFloor * CFloor::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size)
{
	CFloor *pFloor;

	pFloor = new CFloor;
	if (pFloor != NULL)
	{
		pFloor->SetPos(Pos);
		pFloor->SetSize(Size);
		pFloor->Init();
	}

	return pFloor;
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CFloor::Init(void)
{
	//���\�[�X�m��
	CResource* pResource = CManager::GetResource();
	LPDIRECT3DTEXTURE9 Texture = pResource->TextureLoad(m_nTexture);

	SetObjType(CScene::OBJTYPE_NONE);

	CPolygon3d::Init();

	//�e�N�X�`���Z�b�g
	D3DXVECTOR2 Tex[NUM_VERTEX];
	Tex[0] = D3DXVECTOR2(0.0f, 0.0f);
	Tex[1] = D3DXVECTOR2(1.0f, 0.0f);
	Tex[2] = D3DXVECTOR2(0.0f, 1.0f);
	Tex[3] = D3DXVECTOR2(1.0f, 1.0f);
	SetTexture(Tex);

	SetRot(D3DXVECTOR3(D3DXToRadian(-90.0f), D3DXToRadian(0.0f), D3DXToRadian(90.0f)));
	SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	BindTexture(Texture);

	return S_OK;
}