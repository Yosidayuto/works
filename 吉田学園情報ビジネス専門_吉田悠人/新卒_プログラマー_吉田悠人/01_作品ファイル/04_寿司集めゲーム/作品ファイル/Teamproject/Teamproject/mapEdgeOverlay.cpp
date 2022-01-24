//=============================================================================
//
// �t�B�[���h�[�̃|���S���i�G���A�O����j�̏��� [MapEdgeOverlay.cpp]
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
#include "MapEdgeOverlay.h"
#include "resource manager.h"
#include "MapEdgeMask.h"

#define MAX_SCROLL (10) // �X�N���[���J�E���g�ő�
#define MAX_SCROLL_SPEED (0.001f)//�X�N���[���̃X�s�[�h
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMapEdgeOverlay::CMapEdgeOverlay(int nPriority) : CPolygon3d(nPriority)
{
	m_nPatternAnim = 0;
	m_nCountAnim = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMapEdgeOverlay::~CMapEdgeOverlay()
{

}

//=============================================================================
// ��������
//=============================================================================
CMapEdgeOverlay * CMapEdgeOverlay::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size)
{
	CMapEdgeOverlay *pFloor;

	pFloor = new CMapEdgeOverlay;
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
HRESULT CMapEdgeOverlay::Init(void)
{
	//���\�[�X�m��
	CResource* pResource = CManager::GetResource();
	LPDIRECT3DTEXTURE9 Texture = pResource->TextureLoad(m_nTexture);

	SetObjType(CScene::OBJTYPE_NONE);
	CPolygon3d::Init();
	
	//�e�N�X�`���Z�b�g
	D3DXVECTOR2 Tex[NUM_VERTEX];
	Tex[0] = D3DXVECTOR2(m_nCountAnim * 0.001f, m_nCountAnim * 0.001f);
	Tex[1] = D3DXVECTOR2(m_nCountAnim * 0.001f + 0.001f, m_nCountAnim * 0.001f);
	Tex[2] = D3DXVECTOR2(m_nCountAnim * 0.001f, m_nCountAnim * 0.001f + 0.001f);
	Tex[3] = D3DXVECTOR2(m_nCountAnim * 0.001f + 0.001f, m_nCountAnim * 0.001f + 0.001f);
	SetTexture(Tex);

	SetRot(D3DXVECTOR3(D3DXToRadian(-90.0f), D3DXToRadian(90.0f), D3DXToRadian(-90.0f)));
	SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	BindTexture(Texture);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CMapEdgeOverlay::Uninit(void)
{
	CPolygon3d::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CMapEdgeOverlay::Update(void)
{
	m_nCountAnim++;
	if (float(m_nCountAnim * MAX_SCROLL_SPEED) > 1.0f)
	{
		m_nCountAnim = 0;
	}

	CPolygon3d::Update();
	//�e�N�X�`���Z�b�g
	D3DXVECTOR2 Tex[NUM_VERTEX];
	Tex[0] = D3DXVECTOR2(m_nCountAnim * MAX_SCROLL_SPEED, m_nCountAnim * MAX_SCROLL_SPEED);
	Tex[1] = D3DXVECTOR2(5.0f + m_nCountAnim * MAX_SCROLL_SPEED, m_nCountAnim * MAX_SCROLL_SPEED);
	Tex[2] = D3DXVECTOR2(m_nCountAnim * MAX_SCROLL_SPEED, 5.0f + m_nCountAnim * MAX_SCROLL_SPEED);
	Tex[3] = D3DXVECTOR2(5.0f + m_nCountAnim * MAX_SCROLL_SPEED, 5.0f + m_nCountAnim * MAX_SCROLL_SPEED);
	SetTexture(Tex);
}

//=============================================================================
// �`�揈��
//=============================================================================
void CMapEdgeOverlay::Draw(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	//�f�o�C�X�Ƀ����_���[�̃f�o�C�X����
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//�X�e���V���e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);
	//�[�x�e�X�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	//�X�e���V���Q�ƒl�̐ݒ�
	pDevice->SetRenderState(D3DRS_STENCILREF, 0x01);
	//�X�e���V���}�X�N�̐ݒ�
	pDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_GREATER);
	//�X�e���V���e�X�g�̃e�X�g�ݒ�
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);
	CPolygon3d::Draw();
	//�X�e���V���e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
	
}