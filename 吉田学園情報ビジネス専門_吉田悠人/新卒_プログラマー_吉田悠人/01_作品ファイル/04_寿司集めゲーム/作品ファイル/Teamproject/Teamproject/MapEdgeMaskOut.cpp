//=============================================================================
//
// �t�B�[���h�[�̃|���S���i�}�X�N���邪��j�̏��� [MapEdgeMask.cpp]
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
#include "MapEdgeMaskOut.h"
#include "MapEdgeOverlay.h"
#include "resource manager.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMapEdgeMaskOut::CMapEdgeMaskOut(int nPriority) : CPolygon3d(nPriority)
{
	m_nPatternAnim = 0;
	m_nCountAnim = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMapEdgeMaskOut::~CMapEdgeMaskOut()
{

}

//=============================================================================
// ��������
//=============================================================================
CMapEdgeMaskOut * CMapEdgeMaskOut::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size)
{
	CMapEdgeMaskOut *pFloor;

	pFloor = new CMapEdgeMaskOut;
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
HRESULT CMapEdgeMaskOut::Init(void)
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

//=============================================================================
// �I������
//=============================================================================
void CMapEdgeMaskOut::Uninit(void)
{
	CPolygon3d::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CMapEdgeMaskOut::Update(void)
{
	CPolygon3d::Update();
	//�e�N�X�`���Z�b�g
	D3DXVECTOR2 Tex[NUM_VERTEX];
	Tex[0] = D3DXVECTOR2(0.0f, 0.0f);
	Tex[1] = D3DXVECTOR2(1.0f, 0.0f);
	Tex[2] = D3DXVECTOR2(0.0f, 1.0f);
	Tex[3] = D3DXVECTOR2(1.0f, 1.0f);
	SetTexture(Tex);
}

//=============================================================================
// �`�揈��
//=============================================================================
void CMapEdgeMaskOut::Draw(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	//�f�o�C�X�Ƀ����_���[�̃f�o�C�X����
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//�A���t�@�e�X�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHAREF, (DWORD)0x00000001);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
	//�[�x�e�X�g�̐ݒ�(�K���s���i�ɂ���)
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_NEVER);
	//�X�e���V���e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);
	//�X�e���V���o�b�t�@�֏������ގQ�ƒl�ݒ�
	pDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);
	pDevice->SetRenderState(D3DRS_STENCILREF, 0x01);

	//�X�e���V���o�b�t�@�ɏ������ޏ���
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
	// �X�e���V���e�X�g�̃e�X�g�ݒ�
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_REPLACE);
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);
	CPolygon3d::Draw();

	//�X�e���V���e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
}