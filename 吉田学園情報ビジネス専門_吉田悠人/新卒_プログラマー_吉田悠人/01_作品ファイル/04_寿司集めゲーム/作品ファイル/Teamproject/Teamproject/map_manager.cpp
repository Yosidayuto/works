//=============================================================================
//
// �}�b�v�Ǘ��̏��� [map_manager.cpp]
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
#include "map_manager.h"
#include "resource manager.h"
#include "map.h"
#include "locationpoint.h"
#include "game.h"
#include "player.h"
#include "player control.h"
#include "Fieldmanager.h"
#include "MapEdgeMask.h"
#include "MapEdgeOverlay.h"
#include "MapEdgeMaskOut.h"
#include "timer.h"
#include "ebi.h"
#include "egg.h"
#include "ikura.h"
#include "salmon.h"
#include "tuna.h"
#include "scoreup.h"
#include "shield.h"
#include <time.h>


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAP_LOCATION_VALUE		(0.34f) //�}�b�v�\���̌��݈ʒu�␳�l
#define MAP_SHRINK_TIME			(10)	//���̕b�������ɏk��ł�
#define MAP_SHIRINK_SIZE		(2.0f)	//�k�ރX�s�[�h
#define MAP_SHIRINK_TIME_VALUE	(60)	//1�k���ŏk�ޗʁi�t���[���j
#define MAP_LAST_SIZE			(50.0f) //�Ō�̃}�b�v�T�C�Y
#define MAX_SUSHI_SPAWN			(30*7)	//�a�̃X�|�[���܂ł̍ő厞��
#define MIN_SUSHI_SPAWN			(30*2)	//�a�̃X�|�[���܂ł̍Œ᎞��
#define MAX_SUSHI_NUMBER		(10)		//�a���X�|�[������Ƃ��̍ő��
//*****************************************************************************
// �ÓI�����o�[�ϐ�������
//*****************************************************************************
int CMapManager::m_nSushiProb[CFoodBase::TYPE_MAX] =
{
	//���i�̏o���m��
	20,				
	20,
	20,
	20,
	20,
};
//���i�̍ő�m��
int CMapManager::m_nMaxSushiProb = m_nSushiProb[CFoodBase::TYPE_EBI] + m_nSushiProb[CFoodBase::TYPE_EGG] + m_nSushiProb[CFoodBase::TYPE_IKURA] + m_nSushiProb[CFoodBase::TYPE_SALMON] + m_nSushiProb[CFoodBase::TYPE_TUNA];

int CMapManager::m_nItemProb[CItem::ITEM_MAX]=
{
	//�A�C�e���̏o���m��
	50,		//�X�R�A�A�b�v
	50		//�V�[���h
};
int CMapManager::m_nMaxItemProb = m_nItemProb[CItem::ITEM_SCOREUP] + m_nItemProb[CItem::ITEM_SHIELD];
int CMapManager::m_nSpawnItemCount[CGame::GAMESTATE_MAX] =
{
	0,
	5,
	3,
	3,
	2,
	1
};
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMapManager::CMapManager(int nPriority) : CScene(nPriority)
{
    m_originPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_pMapEdgeMask	= nullptr;
	m_pFieldManager = nullptr;
	m_nShrinkCount = 1;
	m_bShirnk = false;
	m_nSushiSpawn = 0;		// ���i�̃X�|�[�����鎞�Ԃ̏�����
	m_nSpawnSushiCount = 0;	// ���i�̃X�|�[�����鎞�Ԃ܂ł̃J�E���g�̏�����
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMapManager::~CMapManager()
{

}

//=============================================================================
// ��������
//=============================================================================
CMapManager * CMapManager::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size)
{
    CMapManager *pMap = nullptr;

    pMap = new CMapManager;
    if (pMap != nullptr)
    {
        pMap->m_originPos = Pos;
        pMap->m_MapSize = Size;
        pMap->Init();
    }
    return pMap;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CMapManager::Init(void)
{
	//���݂̏�Ԃ��擾
	m_GameState = CGame::GetGameState();
    //�X�e�[�W����
    m_pFieldManager = CFieldManager::Create(D3DXVECTOR3(0.0f, -50.0f, 0.0f), m_MapSize);
    //�X�e�[�W�����i���݂̃t�B�[���h�j
    m_pMapEdgeMask = CMapEdgeMask::Create(D3DXVECTOR3(0.0f, -50.0f, 0.0f), m_MapSize);
    //�X�e�[�W�����i�t�B�[���h�O���j
    CMapEdgeOverlay::Create(D3DXVECTOR3(0.0f, -49.0f, 0.0f), m_MapSize * 2.0f);
    //�~�j�}�b�v����
    CMap::Create(m_originPos,D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT,0.0f));

    //�v���C���[�ʒu�̐���
    m_pLocationPoint[0] = CLocationPoint::Create(m_originPos, D3DXVECTOR3(20.0f, 20.0f, 0.0f),0);
    //�v���C���[�ʒu�̐���
    m_pLocationPoint[1] = CLocationPoint::Create(m_originPos, D3DXVECTOR3(20.0f, 20.0f, 0.0f), 1);
    //�v���C���[�ʒu�̐���
    m_pLocationPoint[2] = CLocationPoint::Create(m_originPos, D3DXVECTOR3(20.0f, 20.0f, 0.0f), 2);
    //�v���C���[�ʒu�̐���
    m_pLocationPoint[3] = CLocationPoint::Create(m_originPos, D3DXVECTOR3(20.0f, 20.0f, 0.0f), 3);
    return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CMapManager::Uninit(void)
{
    Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CMapManager::Update(void)
{
	//1�t���[���O�̏�Ԃ��i�[���Ă���
	CGame::GAME_STATE OldGameState = m_GameState;
	//���݂̏�Ԃ��擾
	m_GameState = CGame::GetGameState();
	//���k���Ԃ����������ׂ�
	if (m_GameState != OldGameState)//�قȂ��Ă�������k�J�n
	{
		m_bShirnk = true;
	}
	
	if (m_bShirnk == true && m_nShrinkCount < MAP_SHIRINK_TIME_VALUE)
	{
		if (m_MapSize.x > MAP_LAST_SIZE)//�ŏ��T�C�Y�ɂȂ�܂ŏk�܂���
		{
			//�X�e�[�W���k
			m_MapSize.x -= MAP_SHIRINK_SIZE;
			m_MapSize.y -= MAP_SHIRINK_SIZE;
			m_MapSize.z -= MAP_SHIRINK_SIZE;
			m_nShrinkCount++;
		}
	}
	else if (m_bShirnk == true && m_nShrinkCount >= MAP_SHIRINK_TIME_VALUE)
	{
		m_bShirnk = false;	//���k��Ԃ����ɖ߂�
		m_nShrinkCount = 0;	//������
		ItemSpawn();		//�A�C�e���̐���
	}

    //�T�C�Y�Z�b�g
    m_pMapEdgeMask->SetSize(m_MapSize);
    m_pFieldManager->SetSize(m_MapSize);

    for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
    {
        //�v���C���[�̈ʒu�擾
        D3DXVECTOR3 pos = CManager::GetPlayerControl()->GetPlayer(nCount)->GetPos();
        //�v���C���[�̌��݈ʒu���Z�b�g
        m_pLocationPoint[nCount]->SetPos(D3DXVECTOR3(m_originPos.x + pos.x * MAP_LOCATION_VALUE, m_originPos.y - pos.z * MAP_LOCATION_VALUE, 0.0f));
    }

	//�a�̐�������
	SushiSpawn();

}
//=============================================================================
// �`�揈��
//=============================================================================
void CMapManager::Draw(void)
{
    
}

//=============================================================================
// ���i�̃����_�����������֐�
//=============================================================================
void CMapManager::SushiSpawn(void)
{
	//�J�E���g�_�E��
	m_nSpawnSushiCount++;
	//�J�E���g�����ɒB�����烉���_���ɃX�|�[��
	if (m_nSpawnSushiCount>m_nSushiSpawn)
	{
		//�G���A�̔��a
		float fRadius = (m_MapSize.x / 2) - 50;//(�R�R�̐��l��͈͐����̉~�̔��a�ɂ��邻���ė]�T��������-50)
		//���S�l
		D3DXVECTOR3 centre = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//(�R�R�̐��l��͈͐����̉~�̒��S���擾)
		
		srand((unsigned int)time(NULL));			//�����_���֐��̏�����
		int nNumber = rand() % MAX_SUSHI_NUMBER + 1; //�����_���ɉ��̎��i���X�|�[�������邩���߂�(+1�͊m���Ɉ�a���o������)

		//�����_���Ɍ��߂������X�|�[��������
		for (int nSushiNumber = 0; nSushiNumber < nNumber; nSushiNumber++)
		{
			float fAngle = (float)(rand() % 360 + 1);	//�����_���Ŋp�x�����߂�
			
			float nDistance = (float)(rand() % (int)fRadius);	//�����_���ȋ������擾

			//�����_�����X�|�[���ʒu
			D3DXVECTOR3 random = centre + D3DXVECTOR3((nDistance*cos(fAngle)), 0.0f, (nDistance*sin(fAngle)));

			//�����_���ɂǂ̎��i���X�|�[�������邩���߂�
			int nSpawn = rand() % m_nMaxSushiProb;				//�����_���ɒl���擾

			int nProd = 0;//�m���p�̕ϐ�
			
			//�ǂ̎��i���X�|�[�����邩
			for (int nSushi = 0; nSushi < (int)(CFoodBase::TYPE_MAX); nSushi++)
			{
				//�m���𑫂��Ă�
				nProd += m_nSushiProb[nSushi];
				//�m���̊m�F
				if (nSpawn <= nProd)
				{
					//�J�E���g������
					m_nSpawnSushiCount = 0;
					//�����_���Ɏ��̃X�|�[�����Ԃ����߂�
					m_nSushiSpawn = rand() % MAX_SUSHI_SPAWN + 1;

					//�ŏ��l���Ⴏ���
					if (m_nSushiSpawn<MIN_SUSHI_SPAWN)
					{
						//�ŏ��l�ɍ��킹��
						m_nSushiSpawn = MIN_SUSHI_SPAWN;
					}

					//���i�̃X�|�[������
					switch (nSushi)
					{
					case CFoodBase::TYPE_EBI:
						CEbi::Create(random, D3DXVECTOR3(10.0f, 10.0f, 10.0f));
						break;
					case CFoodBase::TYPE_EGG:
						CEgg::Create(random, D3DXVECTOR3(10.0f, 10.0f, 10.0f));
						break;
					case CFoodBase::TYPE_IKURA:
						CIkura::Create(random, D3DXVECTOR3(10.0f, 10.0f, 10.0f));
						break;
					case CFoodBase::TYPE_SALMON:
						CSalmon::Create(random, D3DXVECTOR3(10.0f, 10.0f, 10.0f));
						break;
					case CFoodBase::TYPE_TUNA:
						CTuna::Create(random, D3DXVECTOR3(10.0f, 10.0f, 10.0f));
						break;
					}
					break;
				}
			
			}
		}
	}
}

//=============================================================================
// �A�C�e���̃����_�����������֐�
//=============================================================================
void CMapManager::ItemSpawn(void)
{
	//�J�E���g�����ɒB�����烉���_���ɃX�|�[��
	for(int nCoutn=0; nCoutn<m_nSpawnItemCount[m_GameState]; nCoutn++)
	{
		//�G���A�̔��a
		float fRadius = (m_MapSize.x / 2) - 50;//(�R�R�̐��l��͈͐����̉~�̔��a�ɂ��邻���ė]�T��������-50)
		 //���S�l
		D3DXVECTOR3 centre = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//(�R�R�̐��l��͈͐����̉~�̒��S���擾)

		//�����_���p�x
		srand((unsigned int)time(NULL));			//�����_���֐��̏�����
		float fAngle = (float)(rand() % 360 + 1);	//�����_���Ŋp�x�����߂�

		//�����_���ȋ���
		int nDistance = rand() % (int)fRadius;		//�����_���ȋ������擾

		//�����_�����X�|�[���ʒu
		D3DXVECTOR3 random = centre + D3DXVECTOR3((float)(nDistance*cos(fAngle)), 0.0f, (float)(nDistance*sin(fAngle)));

		//�����_���ɂǂ̃A�C�e�����X�|�[�������邩���߂�
		int nSpawn = rand() % m_nMaxItemProb;			//�����_���ɒl���擾

		int nProd = 0;//�m���p�̕ϐ�

		//�ǂ̃A�C�e�����X�|�[�����邩
		for (int nItem = 0; nItem < CItem::ITEM_MAX; nItem++)
		{
			// �m���𑫂��Ă�
			nProd += m_nItemProb[nItem];
			// �m���̊m�F
			if (nSpawn <= nProd)
			{
				//�A�C�e���̃X�|�[������
				switch (nItem)
				{
				case CItem::ITEM_SCOREUP:	//�X�R�A�A�b�v����
					CScoreup::Create(random, D3DXVECTOR3(1.0f, 1.0f, 1.0f));
					break;
				case CItem::ITEM_SHIELD:	//�V�[���h����
					CShield::Create(random, D3DXVECTOR3(1.0f, 1.0f, 1.0f));
					break;
				}
				break;
			}
		}
	}

}
