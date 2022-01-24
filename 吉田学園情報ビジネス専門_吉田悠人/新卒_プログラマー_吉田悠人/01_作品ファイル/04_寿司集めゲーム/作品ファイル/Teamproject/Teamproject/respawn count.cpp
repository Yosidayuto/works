//=============================================================================
//
// ���X�|�[���J�E���gUI���� [respawn count.cpp]
// Author : �g�c�I�l
//
//=============================================================================
//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "respawn count.h"
#include "renderer.h"
#include "manager.h"
#include "number.h"
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CRespawnCount::CRespawnCount(int nPriority):CScene(nPriority)
{
	SetObjType(CScene::OBJTYPE_NONE);
	m_nControl = 0;
	memset(m_pNumber, 0, sizeof(m_pNumber));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CRespawnCount::~CRespawnCount()
{
}

//=============================================================================
// ���������֐�
//=============================================================================
CRespawnCount * CRespawnCount::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size)
{
	//�������m��
	CRespawnCount *pRespawnCount = nullptr;
	pRespawnCount = new CRespawnCount;

	//NULL�`�F�b�N
	if (pRespawnCount != nullptr)
	{
		pRespawnCount->m_Pos = Pos;		//�ʒu�ݒ�
		pRespawnCount->m_Size = Size;	//�T�C�Y�ݒ�
		pRespawnCount->Init();			//����������
	}

	return pRespawnCount;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CRespawnCount::Init(void)
{
	//�i���o�[�̐�������
	for (int nCntNum = 0; nCntNum < MAX_NUMBER; nCntNum++)
	{
		m_pNumber[nCntNum] = CNumber::Create(D3DXVECTOR3(m_Pos.x - (m_Size.x * nCntNum), m_Pos.y, 0.0f), m_Size.x, m_Size.y);
	}
	//���l�̃Z�b�g
	SetControl(m_nControl);
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CRespawnCount::Uninit(void)
{
	//�i���o�[�̏I������
	for (int nCntNum = 0; nCntNum < MAX_NUMBER; nCntNum++)
	{
		m_pNumber[nCntNum]->Uninit();
		delete m_pNumber[nCntNum];
		m_pNumber[nCntNum] = NULL;
	}
	Release();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CRespawnCount::Update(void)
{
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CRespawnCount::Draw(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	//�f�o�C�X�Ƀ����_���[�̃f�o�C�X����
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�A���t�@�e�X�g��L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//�A���t�@�e�X�g��l�̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	//�A���t�@�e�X�g�̔�r���@�̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	//�i���o�[�̕`�揈��
	for (int nCntNum = 0; nCntNum < MAX_NUMBER; nCntNum++)
	{
		m_pNumber[nCntNum]->Draw();
	}

	//�A���t�@�e�X�g�𖳌���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=============================================================================
// �J�E���g�Z�b�g�֐�
//=============================================================================
void CRespawnCount::SetControl(int nControl)
{
	m_nControl = nControl;
	int integer = 0;//�v�Z�p�ϐ�
	int nCntNumber = 0;

	for (int nCntDigit = 1; nCntDigit <= MAX_NUMBER; nCntDigit++, nCntNumber++)
	{
		integer = int(m_nControl / pow(10, nCntDigit)); //1�̈ʈȉ���؂�̂Ă�
		integer = int(integer * pow(10, nCntDigit));
		m_pNumber[nCntNumber]->SetNumber(int((m_nControl - integer) / pow(10, nCntDigit - 1)));
	}
}
