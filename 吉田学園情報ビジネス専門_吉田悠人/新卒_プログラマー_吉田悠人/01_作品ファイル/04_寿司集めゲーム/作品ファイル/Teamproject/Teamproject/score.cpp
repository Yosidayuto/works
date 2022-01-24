//=============================================================================
//
// �X�R�A�Ǘ����� [score.cpp]
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
#include "score.h"
#include <cmath>

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScore::CScore(int nPriority) : CScene(nPriority)
{
	memset(m_apNumber, 0, sizeof(m_apNumber));
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	m_nScore = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScore::~CScore()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CScore::Init(void)
{
	SetObjType(CScene::OBJTYPE_NONE);
	for (int nCntNum = 0; nCntNum < MAX_DIGITS; nCntNum++)
	{
		m_apNumber[nCntNum] = CNumber::Create(D3DXVECTOR3(m_Pos.x - (m_Size.x * nCntNum), m_Pos.y, 0.0f), m_Size.x, m_Size.y);
	}
	SetScore(m_nScore);
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CScore::Uninit(void)
{
	for (int nCntNum = 0; nCntNum < MAX_DIGITS; nCntNum++)
	{
		m_apNumber[nCntNum]->Uninit();
		delete m_apNumber[nCntNum];
		m_apNumber[nCntNum] = NULL;
	}
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CScore::Update(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void CScore::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	for (int nCntNum = 0; nCntNum < MAX_DIGITS; nCntNum++)
	{
		m_apNumber[nCntNum]->Draw();
	}
}

//=============================================================================
// ��������
//=============================================================================
CScore * CScore::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size)
{
	CScore *pScore = NULL;

	if (pScore == NULL)
	{
		pScore = new CScore;
		pScore->m_Pos = Pos;
		pScore->m_Size = Size;
		pScore->Init();
	}

	return pScore;
}

//=============================================================================
// �X�R�A�Z�b�g
//=============================================================================
void CScore::SetScore(int nScore)
{
	m_nScore = nScore;
	int integer = 0;//�v�Z�p�ϐ�
	int nCntNumber = 0;

	for (int nCntDigit = 1; nCntDigit <= MAX_DIGITS; nCntDigit++, nCntNumber++)
	{
		integer = int(m_nScore / pow(10, nCntDigit)); //1�̈ʈȉ���؂�̂Ă�
		integer = int(integer * pow(10, nCntDigit));
		m_apNumber[nCntNumber]->SetNumber(int((m_nScore - integer) / pow(10, nCntDigit - 1)));
	}
}

//=============================================================================
// �X�R�A���Z
//=============================================================================
void CScore::AddScore(int nValue)
{
	m_nScore += nValue;
	SetScore(m_nScore);
}
