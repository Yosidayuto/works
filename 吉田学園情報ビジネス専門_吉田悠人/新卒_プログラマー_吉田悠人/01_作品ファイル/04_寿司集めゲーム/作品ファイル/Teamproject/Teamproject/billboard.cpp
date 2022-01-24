//=============================================================================
//
// �r���{�[�h [billboard.cpp]
// Author : �g�c�I�l
//
//=============================================================================

//=============================================================================
// �w�b�_�[�t�@�C��
//=============================================================================
#include "billboard.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBillboard::CBillboard(int nPriority) : CScene3d(nPriority)
{
	m_pTexture	= NULL;
	m_pVtxBuff	= NULL;
	m_col		= D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBillboard::~CBillboard()
{

}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CBillboard::Init(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	
	// ���_���
	VERTEX_3D *pVtx = NULL;

	//�傫���擾
	D3DXVECTOR3 size = GetSize();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);
	
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(-size.x / 2, size.y / 2, +size.z / 2);
	pVtx[1].pos = D3DXVECTOR3(size.x / 2, size.y / 2, +size.z / 2);
	pVtx[2].pos = D3DXVECTOR3(-size.x / 2, -size.y / 2, +size.z / 2);
	pVtx[3].pos = D3DXVECTOR3(size.x / 2, -size.y / 2, +size.z / 2);

	pVtx[0].nor = D3DXVECTOR3(0, 0, -1);
	pVtx[1].nor = D3DXVECTOR3(0, 0, -1);
	pVtx[2].nor = D3DXVECTOR3(0, 0, -1);
	pVtx[3].nor = D3DXVECTOR3(0, 0, -1);

	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CBillboard::Update(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();

	// ���_���
	VERTEX_3D *pVtx = NULL;

	//�傫���擾
	D3DXVECTOR3 size = GetSize();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(-size.x / 2, size.y / 2, +size.z / 2);
	pVtx[1].pos = D3DXVECTOR3(size.x / 2, size.y / 2, +size.z / 2);
	pVtx[2].pos = D3DXVECTOR3(-size.x / 2, -size.y / 2, +size.z / 2);
	pVtx[3].pos = D3DXVECTOR3(size.x / 2, -size.y / 2, +size.z / 2);

	pVtx[0].nor = D3DXVECTOR3(0, 0, -1);
	pVtx[1].nor = D3DXVECTOR3(0, 0, -1);
	pVtx[2].nor = D3DXVECTOR3(0, 0, -1);
	pVtx[3].nor = D3DXVECTOR3(0, 0, -1);

	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	m_pVtxBuff->Unlock();

}

//=============================================================================
// �I�������֐�
//=============================================================================
void CBillboard::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	Release();
}


//=============================================================================
// �`�揈���֐�
//=============================================================================
void CBillboard::Draw(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX	 mtxRot, mtxTrans;	// �s��v�Z�p�̃}�g���N�X
	D3DMATERIAL9 matDef;			// �}�e���A���p
	D3DXVECTOR3  pos = GetPos();	// �ʒu�擾
	
	//�e�N�X�`���Z�b�g
	pDevice->SetTexture(0, m_pTexture);
	//�A���t�@�e�X�g�L��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//�A���t�@�e�X�g��l�̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHAREF, 100);
	//�A���t�@�e�X�g�̔�r���@�̐ݒ�iGREATER�͊�l���傫���ꍇ�j
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//���[���h�}�g���N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//��]�̋t�s��
	pDevice->GetTransform(D3DTS_VIEW, &mtxRot);
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxRot);
	m_mtxWorld._41 = 0;
	m_mtxWorld._42 = 0;
	m_mtxWorld._43 = 0;

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//�}�e���A�����
	ZeroMemory(&matDef, sizeof(matDef));
	matDef.Ambient.r = m_col.r;
	matDef.Ambient.g = m_col.g;
	matDef.Ambient.b = m_col.b;
	matDef.Ambient.a = m_col.a;	//�}�e���A���Z�b�g
	pDevice->SetMaterial(&matDef);

	//�|���S���`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);   //���l
	pDevice->SetTexture(0, NULL);

	//�A���t�@�e�X�g������
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_AMBIENT, 0x44444444);
	ZeroMemory(&matDef, sizeof(matDef));
	pDevice->SetMaterial(&matDef);


}

//=============================================================================
// �J���[�Z�b�^�[�֐�
//=============================================================================
void CBillboard::SetColor(D3DXCOLOR col)
{
	m_col = col;
}

//=============================================================================
// �e�N�X�`���ݒ�֐�
//=============================================================================
void CBillboard::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}
