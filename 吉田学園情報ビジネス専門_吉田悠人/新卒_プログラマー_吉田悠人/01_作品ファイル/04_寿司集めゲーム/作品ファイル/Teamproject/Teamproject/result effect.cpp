//=============================================================================
//
// ���U���g�G�t�F�N�g(���i���~���Ă���) [result effect.h]
// Author : �g�c�I�l
//
//=============================================================================
//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "result effect.h"
#include "food base.h"
#include "floor.h"
#include "ebi.h"
#include "egg.h"
#include "ikura.h"
#include "salmon.h"
#include "tuna.h"
#include "sushi model.h"
#include "sushi bg.h"
#include <time.h>

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_SPAWN_COUNT (10)	//���i�����̃J�E���g
#define MOVE_SPEED (5)
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CResultEffect::CResultEffect(int nPriority):CScene(nPriority)
{
	for (int nSushi = 0; nSushi < MAX_SUSHI_EFFECT; nSushi++)
	{
		m_pSushi[nSushi] = nullptr;
	}
	m_nSpawnCount = 0;
	m_nSushiCount = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CResultEffect::~CResultEffect()
{
}

//=============================================================================
// ��������
//=============================================================================
CResultEffect * CResultEffect::Create()
{
	//�������m��
	CResultEffect* pResultEffect = nullptr;
	pResultEffect = new CResultEffect;

	//NULL�`�F�b�N
	if (pResultEffect != nullptr)
	{
		pResultEffect->Init();
	}

	return pResultEffect;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CResultEffect::Init(void)
{
	CSushiBg::Create(D3DXVECTOR3(0.0f, -700.0f, 0.0f), D3DXVECTOR3(1600.0f, 1200.0f, 0.0f));
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CResultEffect::Uninit(void)
{
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CResultEffect::Update(void)
{
	//���i�̃����_����������
	RandomSpawn();
	////���i�̈ړ�����
	//MoveSushi();
	////���i�̉�ʊO����
	//Offscreen();

}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CResultEffect::Draw(void)
{

}

//=============================================================================
// ���i�̃����_�����������֐�
//=============================================================================
void CResultEffect::RandomSpawn(void)
{

	////�擾�������l���P��艺�̏ꍇ
	//if (m_nSpawnCount>MAX_SPAWN_COUNT)
	//{
	//	//�����ʒu
	//	D3DXVECTOR3 pos;
	//	//�����_����X�ʒu��ݒ�
	//	float XPosRandom = (float)(rand() % 500 * 2) - 500 ;
	//	pos = D3DXVECTOR3(XPosRandom, -250.0f, 300.0f);
	//	
	//	for (int nSushi = 0; nSushi < MAX_SUSHI_EFFECT; nSushi++)
	//	{
	//		if (m_pSushi[nSushi] == NULL)
	//		{
	//			//�����_���ɂǂ̎��i���X�|�[�������邩���߂�
	//			srand(nSushi);
	//			int nSushiType = rand() % 3;			//�����_���ɒl���擾
	//			//���i�̃X�|�[������
	//			m_pSushi[nSushi] = CSushiModel::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f), nSushiType);
	//			
	//			//���݂̎��i�̐����v���X
	//			m_nSushiCount += 1;

	//			//���l�̏�����
	//			m_nSpawnCount = 0;
	//			return;
	//		}
	//	}
	//}

	//�J�E���g�A�b�v
	m_nSpawnCount++;
	if (m_nSpawnCount % MAX_SPAWN_COUNT == 0)
	{
			//�����ʒu
			D3DXVECTOR3 pos;
			//�����_����X�ʒu��ݒ�
			float XPosRandom = (float)(rand() % 500 * 2) - 500 ;
			pos = D3DXVECTOR3(XPosRandom, -250.0f, 300.0f);
			
			//�����_���ɂǂ̎��i���X�|�[�������邩���߂�
			srand(m_nSpawnCount);
			int nSushiType = rand() % 3;			//�����_���ɒl���擾
			//���i�̃X�|�[������
			CSushiModel::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f), nSushiType);
	}
}

//=============================================================================
// ���i�̈ړ�����
//=============================================================================
void CResultEffect::MoveSushi(void)
{
	for (int nSushi = 0; nSushi < MAX_SUSHI_EFFECT; nSushi++)
	{
		if (m_pSushi[nSushi] != NULL)
		{
			//�ʒu�擾
			D3DXVECTOR3 pos = m_pSushi[nSushi]->GetPos();
			//�ʒu�̍X�V
			pos.z -= MOVE_SPEED;
			//�ʒu�Z�b�g
			m_pSushi[nSushi]->SetPos(pos);
		}
	}
}

//=============================================================================
// ���i�̉�ʊO�����֐�
//=============================================================================
void CResultEffect::Offscreen(void)
{
	for (int nSushi = 0; nSushi < MAX_SUSHI_EFFECT; nSushi++)
	{
		if (m_pSushi[nSushi] != NULL)
		{
			//�ʒu�擾
			D3DXVECTOR3 pos = m_pSushi[nSushi]->GetPos();
			//��ʊO�ɏo�Ă��邩
			if (pos.y>SCREEN_HEIGHT + 40)
			{
				//��ʊO�ɂ��鎞�ɏ���
				m_pSushi[nSushi]->Uninit();
				m_pSushi[nSushi] = NULL;
				//�ő吔�����炷
				m_nSushiCount -= 1;
			}
		}
	}
}
