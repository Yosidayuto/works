//=============================================================================
//
// �A�C�e���x�[�X [item.cpp]
// Author : �V����s
//
//=============================================================================

//=============================================================================
// �w�b�_�[�t�@�C��
//=============================================================================
#include "item.h"
#include "timer.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "number.h"
#include "scene.h"

//=============================================================================
// �}�N����`
//=============================================================================



//=============================================================================
//�ÓI�����o�[�ϐ��錾
//=============================================================================


//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTimer::CTimer(int nPriority) : CScene(nPriority)
{
	m_nCountF = 0;
	m_nMinutes = 0;
	m_nSeconds = 0;
	m_bTimeUp = false;

	for (int nCnt = 0; nCnt < MAX_SECONDS_DIGIT; nCnt++)
	{
		m_pSexonds[nCnt] = NULL;
	}

	m_pMINUtes = NULL;

	m_bTimeUp = false;
}


//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTimer::~CTimer()
{
}


//=============================================================================
// ���������֐�
//=============================================================================
CTimer * CTimer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int Min, int Sec)
{
	//�C���X�^���X����
	CTimer *pTimer;
	
	//�������m��
	pTimer = new CTimer;
	
	//���Ԑݒ�
	pTimer->SetTimer(Min, Sec);

	//�ꏊ�ݒ�
	pTimer->m_Pos = pos;

	//�傫���ݒ�
	pTimer->m_Size = size;

	//����������
	pTimer->Init();

	return pTimer;
}


//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CTimer::Init(void)
{
	//���̐���
	m_pMINUtes = CNumber::Create(m_Pos, m_Size.x, m_Size.y);
	
	//�b�̐���
	for (int nCnt = 0;  nCnt < MAX_SECONDS_DIGIT;  nCnt++)
	{
		m_pSexonds[nCnt] = CNumber::Create(D3DXVECTOR3(m_Pos.x + (nCnt * m_Size.x) + 40.0f, m_Pos.y, 0.0f), m_Size.x, m_Size.y);
	}
	
	
	return S_OK;
}


//=============================================================================
// �X�V�����֐�
//=============================================================================
void CTimer::Update(void)
{
	
	//if(�Q�[�����̏ꍇ)

	//�t���[���̃J�E���g
	m_nCountF++;

	if (m_nCountF == 30)
	{
		//�t���[���̃J�E���g�����Z�b�g
		m_nCountF = 0;
		//�b�̃J�E���g��������
		m_nSeconds--;
	}

	//�`��0�ȉ��ɂȂ�����
	if (m_nSeconds <= -1)
	{
		//���̃J�E���g��1�ȏ�̎�
		if (m_nMinutes >= 1)
		{
			// �b�̃J�E���g��59�ɖ߂�
			m_nSeconds = 59;

			// ���̃J�E���g��������
			m_nMinutes--;
		}
	}
	//�^�C���A�b�v�@
	if (m_pMINUtes && m_nSeconds <= -1)
	{
		m_nCountF = 0;
		m_nMinutes = 0;
		m_nSeconds = 0;

		//�^�C���A�b�v�̃t���O
		m_bTimeUp = true;

		//�Q�[���I������
		//�Q�[�����Ȃ�
		//�Q�[�����[�h�������ɂ���
	}


	// �����̕ύX
	int nRadix = 10;

	for (int nCnt = 0; nCnt < MAX_SECONDS_DIGIT; nCnt++)
	{
		int nAnswer = m_nSeconds % (int)pow(nRadix, MAX_SECONDS_DIGIT - nCnt) / (int)pow(nRadix, MAX_SECONDS_DIGIT - nCnt - 1);

		m_pSexonds[nCnt]->SetNumber(nAnswer);
	}

	//�^�C�}�[���̐����ݒ�
	m_pMINUtes->SetNumber(m_nMinutes);

}


//=============================================================================
// �I�������֐�
//=============================================================================
void CTimer::Uninit(void)
{
	//�b�̔j��
	for (int nCnt = 0; nCnt < MAX_SECONDS_DIGIT; nCnt++)
	{
		if (m_pSexonds[nCnt] != NULL)
		{
			m_pSexonds[nCnt]->Uninit();
			delete 	m_pSexonds[nCnt];
			m_pSexonds[nCnt] = NULL;
		}
	}

	//���̔j��
	if (m_pMINUtes != NULL)
	{
		m_pMINUtes->Uninit();
		delete 	m_pMINUtes;
		m_pMINUtes = NULL;
	}

	//�I�u�W�F�N�g�̔j��
	Release();
}


//=============================================================================
// �`�揈��
//=============================================================================
void CTimer::Draw(void)
{

	//�b�̕`��
	for (int nCnt = 0; nCnt < MAX_SECONDS_DIGIT; nCnt++)
	{
		m_pSexonds[nCnt]->Draw();
	}

	//���̕`��
	m_pMINUtes->Draw();

}


//=============================================================================
// ���Ԑݒ菈��
//=============================================================================
void CTimer::SetTimer(int Min, int Sec)
{
	m_nMinutes = Min;
	m_nSeconds = Sec;
}

//=============================================================================
// ���ݎ��Ԏ擾�i�t���[���j
//=============================================================================
int CTimer::GetTime(void)
{
	int nTime = (m_nMinutes * 60 * 30) + (m_nSeconds * 30);
	return nTime;//�t���[���ŕԂ�
}
