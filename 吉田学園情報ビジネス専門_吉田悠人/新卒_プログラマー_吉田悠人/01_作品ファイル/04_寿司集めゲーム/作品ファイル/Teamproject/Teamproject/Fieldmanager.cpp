//=============================================================================
//
// �t�B�[���h�Ǘ� [fieldmanager.cpp]
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
#include "fieldmanager.h"
#include "resource manager.h"
#include "map.h"
#include "locationpoint.h"
#include "game.h"
#include "player.h"
#include "floor.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAP_SIZE (500.0f)		//�}�b�ՃT�C�Y
#define PLAYER_HIT_SIZE (5.0f)	//�}�b�ՃT�C�Y


//=============================================================================
// �R���X�g���N�^
//=============================================================================
CFieldManager::CFieldManager(int nPriority) : CScene(nPriority)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CFieldManager::~CFieldManager()
{

}

//=============================================================================
// ��������
//=============================================================================
CFieldManager * CFieldManager::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size)
{
	CFieldManager *pMap = nullptr;

	pMap = new CFieldManager;
	if (pMap != nullptr)
	{
		pMap->m_size = Size;
		pMap->Init();
	}
	return pMap;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CFieldManager::Init(void)
{
	//������
	CFloor::Create(D3DXVECTOR3(0.0f, -50.0f, 0.0f), D3DXVECTOR3(m_size.x, m_size.z, m_size.z));
	m_originsize = m_size;//�}�b�v�ő�̃T�C�Y���i�[���Ă���
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CFieldManager::Uninit(void)
{
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CFieldManager::Update(void)
{
	//�[�����蔻��
	EdgeCollision();

}
//=============================================================================
// �`�揈��
//=============================================================================
void CFieldManager::Draw(void)
{

}

void CFieldManager::SetSize(D3DXVECTOR3 Size)
{
	m_size = Size;
}

//=============================================================================
// �[���S����
//=============================================================================
void CFieldManager::EdgeCollision(void)
{
	CScene* pTop[PRIORITY_MAX] = {};
	CScene* pNext = nullptr;
	D3DXVECTOR3 distance; //�v���C���[�ƓG�̋���
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		//���X�g�擪�擾
		pTop[nCount] = *(CScene::GetTop() + nCount);
	}

	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		if (pTop[nCount] != nullptr)
		{
			pNext = pTop[nCount];
			while (pNext != nullptr)
			{
				//pNext(CScene)��CPlayer�Ƀ_�E���L���X�g
				CPlayer * pPlayer = dynamic_cast<CPlayer*> (pNext);
				if (pPlayer != nullptr)
				{
					distance = pPlayer->GetPos();//�}�b�v�̌��_���O�A�O�Ȃ̂ł��̂܂܃v���C���[�̈ʒu�����

					//�G�ƃv���C���[�̋��������ꂼ��̔��a�̘a���傫��������}�b�v����͂ݏo�Ă�
					if (powf(distance.x, 2) + powf(distance.z, 2)
						>= pow(((m_size.x / 2) + PLAYER_HIT_SIZE), 2))
					{
						//���S�����i�}�b�v���k�Q�T���ȉ��Ȃ�j
						//����ȊO�̓��X�|�[��
						pPlayer->BarrierHit();
					}
					
				}
				//���̑Ώۂ�ǂݍ���
				pNext = pNext->GetNext();
			}
		}
	}
}