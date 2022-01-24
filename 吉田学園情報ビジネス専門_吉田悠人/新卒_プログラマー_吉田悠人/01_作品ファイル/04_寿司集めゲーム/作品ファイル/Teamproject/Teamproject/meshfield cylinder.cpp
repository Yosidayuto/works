//=============================================================================
//
// �~���G�t�F�N�g���� [effect_cylinder.cpp]
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
#include "meshfield cylinder.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CYLINDER_Y_COUNT (4)
#define CYLINDER_X_COUNT (10)
#define CYLINDER_NUM_VERTEX ((CYLINDER_X_COUNT + 1) * (CYLINDER_Y_COUNT + 1))//���_��
#define CYLINDER_NUM_INDEX (((CYLINDER_X_COUNT + 1)*2)*CYLINDER_Y_COUNT + (CYLINDER_Y_COUNT - 1)*2)//�C���f�b�N�X��
#define CYLINDER_NUM_PRIMITIVE (CYLINDER_X_COUNT*CYLINDER_Y_COUNT * 2)+((CYLINDER_Y_COUNT-1) * 4)	
//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEffectCylinder::CEffectCylinder(int nPriority) : CScene3d(nPriority)
{
	m_pTexture = NULL;							//�e�N�X�`���ւ̃|�C���^
	m_pVtxBuff = NULL;							//���_�o�b�t�@�ւ̃|�C���^
	m_Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//���_�J���[							//�k��
	memset(m_mtxWorld, NULL, sizeof(m_mtxWorld));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEffectCylinder::~CEffectCylinder()
{
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CEffectCylinder::Init(void)
{
	SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	D3DXVECTOR3 nor;//�ق�
	
	//�����_���[�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();

	//�f�o�C�X�Ƀ����_���[�̃f�o�C�X����
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	SetObjType(CScene::OBJTYPE_NONE);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*CYLINDER_NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	// ���_����ݒ�
	VERTEX_3D *pVtx;

	WORD * pIdx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	int nIndex = 0;
	int nTexIndex = 0;
	for (int vIndex = 0; vIndex < CYLINDER_Y_COUNT + 1; vIndex++)
	{
		nTexIndex = 0;
		for (int hIndex = 0; hIndex < CYLINDER_X_COUNT + 1; hIndex++)
		{
			float fAngle = (float)hIndex * 360.0f / (float)CYLINDER_X_COUNT;
			pVtx[nIndex].pos = D3DXVECTOR3(sinf(D3DXToRadian(-fAngle))*(GetSize().x / 2),
				(-vIndex * (GetSize().y / CYLINDER_Y_COUNT)) + (GetSize().y / 2),
				cosf(D3DXToRadian(fAngle))*(GetSize().z / 2));
			//�@�����K��
			D3DXVec3Normalize(&nor, &GetRot());
			// �@���̐ݒ�
			pVtx[nIndex].nor = -GetRot();
			// ���_�J���[�̐ݒ�
			pVtx[nIndex].col = m_Col;
			// �e�N�X�`�����W�̐ݒ�
			pVtx[nIndex].tex = D3DXVECTOR2((float)nTexIndex, (float)vIndex);
			nIndex++;
			nTexIndex++;
		}
	}

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	// �C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(VERTEX_3D)*CYLINDER_NUM_INDEX, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pIdxBuff, NULL);
	// �C���f�b�N�X�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);
	nIndex = 0;
	for (int vIndex = 0; vIndex < CYLINDER_Y_COUNT + 1; vIndex++)
	{
		for (int hIndex = 0; hIndex < CYLINDER_X_COUNT + 1; hIndex++)
		{
			pIdx[nIndex] = (CYLINDER_X_COUNT + 1) + (nIndex / 2) - vIndex;
			pIdx[nIndex + 1] = (nIndex / 2) - vIndex;
			nIndex += 2;
		}
	}

	//���_�o�b�t�@�̃A�����b�N
	m_pIdxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CEffectCylinder::Uninit(void)
{
	//CScene3d::Uninit();
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	Release();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CEffectCylinder::Update(void)
{
	// ���_����ݒ�
	VERTEX_3D *pVtx;

	WORD * pIdx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	int nIndex = 0;
	int nTexIndex = 0;
	for (int vIndex = 0; vIndex < CYLINDER_Y_COUNT + 1; vIndex++)
	{
		float fAngleY = vIndex * 180.0f / CYLINDER_Y_COUNT;
		nTexIndex = 0;
		for (int hIndex = 0; hIndex < CYLINDER_X_COUNT + 1; hIndex++)
		{
			float fAngle = hIndex * 360.0f / CYLINDER_X_COUNT;
			pVtx[nIndex].pos = D3DXVECTOR3(cosf(D3DXToRadian(fAngleY))* (GetSize().y / 2)*sinf(D3DXToRadian(fAngle)),
				sinf(D3DXToRadian(fAngleY)) * (GetSize().y / 2),
				cosf(D3DXToRadian(fAngleY)) * (GetSize().y / 2)*cosf(D3DXToRadian(fAngle)));
			//�@�����K��
			D3DXVec3Normalize(&pVtx[nIndex].nor, &GetRot());
			// �@���̐ݒ�
			pVtx[nIndex].nor = -GetRot();
			// ���_�J���[�̐ݒ�
			pVtx[nIndex].col = m_Col;
			// �e�N�X�`�����W�̐ݒ�
			pVtx[nIndex].tex = D3DXVECTOR2(nTexIndex, (float)vIndex);
			nIndex++;
			nTexIndex++;
		}
	}

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	// �C���f�b�N�X�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);
	nIndex = 0;
	for (int vIndex = 0; vIndex < CYLINDER_Y_COUNT + 1; vIndex++)
	{
		for (int hIndex = 0; hIndex < CYLINDER_X_COUNT + 1; hIndex++)
		{
			pIdx[nIndex] = (CYLINDER_X_COUNT + 1) + (nIndex / 2) - vIndex;
			pIdx[nIndex + 1] = (nIndex / 2) - vIndex;
			nIndex += 2;
		}
	}

	//���_�o�b�t�@�̃A�����b�N
	m_pIdxBuff->Unlock();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CEffectCylinder::Draw(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	//�f�o�C�X�Ƀ����_���[�̃f�o�C�X����
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	//�A���t�@�e�X�g��L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//�A���t�@�e�X�g��l�̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHAREF, 100);
	//�A���t�@�e�X�g�̔�r���@�̐ݒ�iGREATER�͊�l���傫���ꍇ)
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;
	ZeroMemory(&matDef, sizeof(matDef));
	//���[���h�}�g���N�X������
	D3DXMatrixIdentity(&m_mtxWorld);
	//�������f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, D3DXToRadian(GetRot().y), D3DXToRadian(GetRot().x), D3DXToRadian(GetRot().z));
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	//�ʒu���f
	D3DXMatrixTranslation(&mtxTrans, GetPos().x, GetPos().y, GetPos().z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
	//���[���h�}�g���N�X
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	//�F�Z�b�g
	matDef.Ambient = m_Col;
	pDevice->SetMaterial(&matDef);
	//���_�t�H�[�}�b�g�ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);
	//�e�N�X�`���Z�b�g
	pDevice->SetTexture(0, m_pTexture);
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, CYLINDER_NUM_VERTEX, 0, CYLINDER_NUM_PRIMITIVE);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	//�ێ����Ă����}�e���A�������ɖ߂�
	ZeroMemory(&matDef, sizeof(matDef));
	pDevice->SetMaterial(&matDef);
	//�A���t�@�e�X�g�𖳌���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=============================================================================
// �e�N�X�`���̊��蓖�Ċ֐�
//=============================================================================
void CEffectCylinder::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	//�e�N�X�`���̊��蓖��
	m_pTexture = pTexture;
}

//=============================================================================
// ���_�J���[�ݒ�֐�
//=============================================================================
void CEffectCylinder::SetColor(D3DXCOLOR Col)
{
	//�J���[�̊��蓖��
	m_Col = Col;
}
