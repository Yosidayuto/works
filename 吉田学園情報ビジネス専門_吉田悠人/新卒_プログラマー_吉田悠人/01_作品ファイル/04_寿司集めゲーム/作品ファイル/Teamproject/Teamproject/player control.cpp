//=============================================================================
//
//	�v���C���[���� [player control.cpp]
//	Author:�g�c�I�l
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "manager.h"
#include "player control.h"
#include "player.h"
#include "joystick.h"
#include "keyboard.h"
#include "player parts.h"
#include "score.h"
#include <time.h>
#include "sound.h"
#include "respawn count.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define PLAYER_SIZE				(7.0f)		// �v���C���[�̓����蔻��̃T�C�Y
#define PLAYER_DEATH			(30*10)		// �v���C���[�����S����
#define NPC_AVOID				(50.0f)		// NPC�̃v���C���[�������
#define NPC_ITEM				(200.0f)	// NPC�̃A�C�e���D�����
#define NPC_SUSHI				(1000.0f)	// NPC�̎��i�D�����
#define NPC_MAX_RANDOM_ROT		(100)		// �����_���Ɍ�������
#define NPC_MAX_RANDOM			(50)		// �����_���Ɍ����ۂ̍ő�J�E���g
#define NPC_MAX_TARGET_COUNT	(60*10)		// �^�[�Q�b�g�J�E���g�̍ő吔
#define NPC_AVOID_BARRIER		(100)		// �o���A���悯�鋗��

//*****************************************************************************
// �ÓI�����o�ϐ�������
//*****************************************************************************
D3DXVECTOR3 CPlayerControl::m_RespawnCountPos[MAX_PLAYER]=
{
	D3DXVECTOR3(340.0f, 150.0f, 0.0f),
	D3DXVECTOR3(1050.0f, 150.0f, 0.0f),
	D3DXVECTOR3(340.0f, 505.0f, -50.0f),
	D3DXVECTOR3(1050.0f, 505.0f, -50.0f)

};
D3DXVECTOR3 CPlayerControl::m_PlayerPos[MAX_PLAYER] =
{
	D3DXVECTOR3(-50.0f, 0.0f, 0.0f),
	D3DXVECTOR3(50.0f, 0.0f, 0.0f),
	D3DXVECTOR3(-50.0f, 0.0f, -50.0f),
	D3DXVECTOR3(50.0f, 0.0f, -50.0f)
};
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPlayerControl::CPlayerControl(int nPriority)
{
	for (int nPlayer = 0; nPlayer<MAX_PLAYER; nPlayer++)
	{
		m_pPlayer[nPlayer] = nullptr;
		m_nRespawn[nPlayer] = PLAYER_DEATH;
		m_pRespawnCount[nPlayer] = NULL;
	}
	m_bRespawn = true;

	for (int nNpc = 0; nNpc < MAX_NPC; nNpc++)
	{
		m_NpcData[nNpc] = { D3DXVECTOR3(0.0f,0.0f,0.0f),NPC_MAX_RANDOM ,NPC_MAX_TARGET_COUNT,false,nullptr,nullptr };
	}
	m_nNumberPlayer = 1;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPlayerControl::~CPlayerControl()
{
}

//=============================================================================
// ���������֐�
//=============================================================================
CPlayerControl * CPlayerControl::Create()
{
	//�������m��
	CPlayerControl *pPlayerControl = nullptr;
	pPlayerControl = new CPlayerControl;

	if (pPlayerControl != nullptr)
	{
		pPlayerControl->Init();
	}
	return pPlayerControl;

}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CPlayerControl::Init(void)
{
	//�v���C���[����
	for (int nPlayer = 0; nPlayer < MAX_PLAYER; nPlayer++)
	{
		m_pPlayer[nPlayer] = CPlayer::Create(m_PlayerPos[nPlayer], D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), m_nPlayerModel[nPlayer]);
	}

	//�v���C���[�l���擾
	m_nNumberPlayer = CManager::GetPlayerNumber();
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CPlayerControl::Uninit(void)
{
	Release();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CPlayerControl::Update(void)
{
	for (int nPlayer = 0; nPlayer<MAX_PLAYER; nPlayer++)
	{
		//NULL�`�F�b�N
		if (m_pPlayer[nPlayer] != nullptr)
		{
			//�v���C���[�̐l��
			if (nPlayer < m_nNumberPlayer)
			{
				//�v���C���[�A��l�ЂƂ�̑���Ǘ�
				PlayerControl(nPlayer);

				if (m_nNumberPlayer == 1)
				{
					PlayerKeyControl();
				}
			}
			else
			{
				//NPC�Ƃ��ĊǗ�
				NpcControl(nPlayer);
			}
			//�v���C���[���m�̓����蔻��
			PlayerHit(nPlayer);
			//�v���C���[�̃_���[�W����
			DamageHit(nPlayer);
			//���X�|�[������
			RespawnControl(nPlayer);
			//�X�R�A�Ǘ�
			PlayerScore(nPlayer);
		}
	}

}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CPlayerControl::Draw(void)
{
}

//=============================================================================
// �v���C���[�l���Z�b�^�[�����֐�
//=============================================================================
void CPlayerControl::SetNumberPlayer(int nNumber)
{
	m_nNumberPlayer = nNumber;
}

//=============================================================================
// ���X�|�[���X�C�b�`�Z�b�^�[�����֐�
//=============================================================================
void CPlayerControl::SetRespawn(bool Respawn)
{
	m_bRespawn = Respawn;
}

//=============================================================================
// �v���C���[�̃��X�|�[�������֐�
//=============================================================================
void CPlayerControl::RespawnControl(int nPlayer)
{
	//�v���C���[�̏�Ԃ�����ł����ԂȂ̂�+���X�|�[���̃X�C�b�`�������Ă��邩
	if (m_pPlayer[nPlayer]->GetStats() == CPlayer::PLAYER_STATS_RESPAWN&&m_bRespawn == true)
	{
		//�J�E���g��UI
		if (m_pRespawnCount[nPlayer] == NULL)
		{
			m_pRespawnCount[nPlayer] = CRespawnCount::Create(m_RespawnCountPos[nPlayer], D3DXVECTOR3(60.0f, 120.0f, 0.0f));
			m_pRespawnCount[nPlayer]->SetControl(m_nRespawn[nPlayer]/30);
		}
		//���X�|�[���J�E���g
		m_nRespawn[nPlayer]--;
		m_pRespawnCount[nPlayer]->SetControl(m_nRespawn[nPlayer]/30);

		//���X�|�[���J�E���g�����ɒB������
		if (m_nRespawn[nPlayer] <= 0)
		{
			//���S�n
			D3DXVECTOR3 centre = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//(�R�R�̐��l��͈͐����̉~�̒��S���擾)
			//�����_���p�x
			srand((unsigned int)time(NULL));					//�����_���֐��̏�����
			float fAngle = (float)(rand() % 360 + 1);			//�����_���Ŋp�x�����߂�
			//�����_���ȋ���
			srand((unsigned int)time(NULL));					//�����_���֐��̏�����
			int nDistance = rand() % (int)((m_fMapSize / 2) - 50);		//�����_���ȋ������擾(�}�b�v�̃T�C�Y���ɓ���悤��)
			//�����_�����X�|�[���ʒu
			D3DXVECTOR3 random = centre + D3DXVECTOR3((float)(nDistance*cos(fAngle)), 0.0f, (float)(nDistance*sin(fAngle)));

			//���X�|�[������
			m_pPlayer[nPlayer]->Respawn(random);
			//���X�|�[���J�E���g�̏�����
			m_nRespawn[nPlayer] = PLAYER_DEATH;

			//���X�|�[���J�E���gUI�̏���
			if (m_pRespawnCount[nPlayer] != NULL)
			{
				m_pRespawnCount[nPlayer]->Uninit();
				m_pRespawnCount[nPlayer] = NULL;
			}
		}
	}
}

//=============================================================================
// ���̃v���C���[�̓��������ۂ̃_���[�W����
//=============================================================================
void CPlayerControl::DamageHit(int nPlayer)
{
	//NULL�`�F�b�N
	if (m_pPlayer[nPlayer] != nullptr)
	{
		for (int nPlayerCount = 0; nPlayerCount < MAX_PLAYER; nPlayerCount++)
		{
			if (m_pPlayer[nPlayerCount] != nullptr
				&& nPlayer != nPlayerCount)
			{
				//�v���C���[�̈ʒu
				D3DXVECTOR3 PlayerPos = m_pPlayer[nPlayer]->GetPos();
				//���Ă�ꂽ�v���C���[�̃p�[�c��
				int nPlayerParts = m_pPlayer[nPlayerCount]->GetPartsCount();

				for (int nPartsCount = 0; nPartsCount<nPlayerParts; nPartsCount++)
				{
					//�p�[�c�̈ʒu
					D3DXVECTOR3 PartsPos = m_pPlayer[nPlayerCount]->GetParts(nPartsCount)->GetPos();

					//�v���C���[�ƃp�[�c�̋������v�Z
					float RangeX = PlayerPos.x - PartsPos.x;
					float RangeZ = PlayerPos.z - PartsPos.z;
					float Range = (float)(sqrt(RangeX * RangeX + RangeZ * RangeZ));

					//�͈͂ɓ����Ă��邩
					if (Range <= PLAYER_SIZE + PLAYER_SIZE)
					{
						//�v���C���[�̏���
						m_pPlayer[nPlayer]->DamageHit();
						return;
					}
				}

			}
		}
	}
}

//=============================================================================
//�v���C���[�̓��m�̃q�b�g�����֐�
//=============================================================================
void CPlayerControl::PlayerHit(int nPlayer)
{
	//NULL�`�F�b�N
	if (m_pPlayer[nPlayer] != nullptr)
	{
		if (m_pPlayer[nPlayer]->GetStats() == CPlayer::PLAYER_STATS_NORMAL)
		{
			//��x�����������������Ȃ����߂�+1
			int nPlayerCount = nPlayer + 1;
			//�v���C���[���m�̏���
			for (nPlayerCount; nPlayerCount < MAX_PLAYER; nPlayerCount++)
			{
				//�v���C���[�̃|�C���^��NULL�`�F�b�N
				if (m_pPlayer[nPlayerCount] != nullptr)
				{
					//����v���C���[�̏�ԃ`�F�b�N
					if (m_pPlayer[nPlayerCount]->GetStats() == CPlayer::PLAYER_STATS_NORMAL)
					{
						//�v���C���[�̈ʒu
						D3DXVECTOR3 PlayerPos = m_pPlayer[nPlayer]->GetPos();
						//���Ă�ꂽ�v���C���[�̈ʒu
						D3DXVECTOR3 HitPlayerPos = m_pPlayer[nPlayerCount]->GetPos();
						//�v���C���[���m�̋������v�Z
						float RangeX = PlayerPos.x - HitPlayerPos.x;
						float RangeZ = PlayerPos.z - HitPlayerPos.z;
						float Range = (float)(sqrt(RangeX * RangeX + RangeZ * RangeZ));

						//�v���C���[���߂��ɂ��邩
						if (Range <= PLAYER_SIZE + PLAYER_SIZE)
						{
							//�v���C���[���m�̔���
							m_pPlayer[nPlayer]->Repel(m_pPlayer[nPlayerCount]);
							m_pPlayer[nPlayerCount]->Repel(m_pPlayer[nPlayer]);
							return;
						}
					}
				}
			}
		}
	}
}

//=============================================================================
// �v���C���[���쏈���֐�
//=============================================================================
void CPlayerControl::PlayerControl(int nPlayer)
{
	// �R���g���[���[�̎擾
	CJoystick* pJoystick = CManager::GetInputJoystick();
	//���͐�
	D3DXVECTOR3 Joystic = D3DXVECTOR3((float)pJoystick->GetJoyStick(nPlayer).lX, (float)-pJoystick->GetJoyStick(nPlayer).lY, 0.0f);
	// �v���C���[�̑��� 
	m_pPlayer[nPlayer]->RotControl(Joystic);
	//�v���C���[�̉�������
	if (pJoystick->GetJoystickPress(JS_A, nPlayer))
	{
		//�p�[�c����0�ȏ�
		if (m_pPlayer[nPlayer]->GetPartsCount()>0)
		{
			m_pPlayer[nPlayer]->Dash(true);
		}
		else
		{
			m_pPlayer[nPlayer]->Dash(false);
		}
	}
	else
	{
		m_pPlayer[nPlayer]->Dash(false);
	}
}

//=============================================================================
// �v���C���[����(�L�[�{�[�h)�֐�
//=============================================================================
void CPlayerControl::PlayerKeyControl(void)
{
	//�L�[�{�[�h�̎擾
	CKeyboard* pKeyBoard = CManager::GetInputKeyboard();
	//���͐�
	D3DXVECTOR3 Key = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
	//�L�[���͎擾
	if (pKeyBoard->GetKeyPress(DIK_UP))Key.y += 1.0f;
	if (pKeyBoard->GetKeyPress(DIK_LEFT)) Key.x -= 1.0f;
	if (pKeyBoard->GetKeyPress(DIK_RIGHT)) Key.x += 1.0f;
	if (pKeyBoard->GetKeyPress(DIK_DOWN))Key.y -= 1.0f;

	// �v���C���[�̑��� 
	m_pPlayer[0]->RotControl(Key);
	
	//�v���C���[�̉�������
	if (pKeyBoard->GetKeyPress(DIK_Z))
	{
		//�p�[�c����0�ȏ�
		if (m_pPlayer[0]->GetPartsCount()>0)
		{
			m_pPlayer[0]->Dash(true);
		}
		else
		{
			m_pPlayer[0]->Dash(false);
		}
	}
	else
	{
		m_pPlayer[0]->Dash(false);
	}
}

//=============================================================================
// �v���C���[�̃X�R�A�����֐�
//=============================================================================
void CPlayerControl::PlayerScore(int nPlayer)
{
	//�X�R�A�|�C���^�擾
	CScore* pScore = CManager::GetScore(nPlayer);
	
	//�X�R�A�Z�b�g
	pScore->SetScore(m_pPlayer[nPlayer]->GetPartsCount());
	
}

//=============================================================================
// NPC����֐�
//=============================================================================
void CPlayerControl::NpcControl(int nNpc)
{
	//�߂��ɂ�����̂����ď����ɂ����s�������߂�(�d�v�x�������قǌ�ɏ���)
	SushiProcessCriteria(nNpc);		// ���i�̋����𑪂�
	ItemProcessCriteria(nNpc);		// �A�C�e���̋����𑪂�
	PlayerProcessCriteria(nNpc);	// �v���C���[�̋����𑪂�
	NpcRandomProbability(nNpc);		// ���܂Ƀ����_���ɍs��
	TargetSwitching(nNpc);			// �ړ����̒�ؑ΍�
	NpcRandomCount(nNpc);			// �����_���ړ�����
	AvoidBarrier(nNpc);				// �o���A��������

	//����������ɓ���ēn��
	m_pPlayer[nNpc]->RotControl(m_NpcData[nNpc - 1].m_TargetRot);
}

//=============================================================================
// NPC�ƃv���C���[�̊֌W�����֐�
//=============================================================================
void CPlayerControl::PlayerProcessCriteria(int nNpc)
{
	//NULL�`�F�b�N
	if (m_pPlayer[nNpc] != nullptr)
	{
		//NPC�̈ʒu
		D3DXVECTOR3 NPCPos = m_pPlayer[nNpc]->GetPos();
		//�����̋L�^�p�ϐ�
		float fDistance = NPC_AVOID;

		for (int nPlayerCount = 0; nPlayerCount < MAX_PLAYER; nPlayerCount++)
		{
			if (m_pPlayer[nPlayerCount] != nullptr
				&& nNpc != nPlayerCount)
			{
				//����v���C���[�̈ʒu
				D3DXVECTOR3 PlayerPos = m_pPlayer[nPlayerCount]->GetPos();
				//NPC�ƃv���C���[�̋������v�Z
				float RangeX = PlayerPos.x - NPCPos.x;
				float RangeZ = PlayerPos.z - NPCPos.z;
				float Range = (float)(sqrt(RangeX * RangeX + RangeZ * RangeZ));

				//���������ȏ�߂���
				if (NPC_AVOID>Range)
				{
					//���݋L�^���Ă��鋗�����߂���
					if (fDistance>Range)
					{
						//�߂��ꍇ�L�^����
						fDistance = Range;
						//�����̋L�^
						m_NpcData[nNpc - 1].m_TargetRot = D3DXVECTOR3(-RangeX, -RangeZ, 0.0f);
						//���݂̃^�[�Q�b�g���擾
						m_NpcData[nNpc - 1].m_pTarget = m_pPlayer[nPlayerCount];
					}
				}
			}
		}
	}
}

//=============================================================================
// NPC�ƃA�C�e���̊֌W�����֐�
//=============================================================================
void CPlayerControl::ItemProcessCriteria(int nNpc)
{
	//NULL�`�F�b�N
	if (m_pPlayer[nNpc] != nullptr)
	{
		//�V�[���擾�p
		CScene* pTop[PRIORITY_MAX] = {};
		//���`�F�b�N����V�[���̃|�C���^
		CScene* pNext = NULL;
		//NPC�̈ʒu
		D3DXVECTOR3 NPCPos = m_pPlayer[nNpc]->GetPos();
		//�����̋L�^�p�ϐ�
		float fDistance = NPC_ITEM;

		//top�̃A�h���X���擾
		for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
		{
			pTop[nCount] = *(CScene::GetTop() + nCount);
		}

		//�I�u�W�F�N�g�T��
		for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
		{
			if (pTop[nCount] != NULL)
			{
				pNext = pTop[nCount];
				//���̕`��D��x�̃I�u�W�F�N�g���Ȃ��Ȃ�܂Ń��[�v
				while (pNext != NULL)
				{
					if (pNext->GetObjType() == CScene::OBJTYPE_ITEM)
					{
						//�A�C�e���̈ʒu�擾
						D3DXVECTOR3 ItemPos = ((CPlayer*)pNext)->GetPos();
						//NPC�ƃA�C�e���̋������v�Z
						float RangeX = ItemPos.x - NPCPos.x;
						float RangeZ = ItemPos.z - NPCPos.z;
						float Range = (float)(sqrt(RangeX * RangeX + RangeZ * RangeZ));

						//����̋������߂���
						if (NPC_ITEM > Range)
						{
							//���݋L�^���Ă��鋗�����߂���
							if (fDistance > Range)
							{
								//�߂��ꍇ�L�^����
								fDistance = Range;
								//�����̋L�^
								m_NpcData[nNpc - 1].m_TargetRot = D3DXVECTOR3(RangeX, RangeZ, 0.0f);
								//���݂̃^�[�Q�b�g���擾
								m_NpcData[nNpc - 1].m_pTarget = pNext;
							}
						}
					}
					//���̃I�u�W�F�N�g�̃|�C���^���X�V
					pNext = pNext->GetNext();
				}
			}
		}
	}
}

//=============================================================================
// NPC�Ǝ��i�̊֌W�����֐�
//=============================================================================
void CPlayerControl::SushiProcessCriteria(int nNpc)
{
	//NULL�`�F�b�N
	if (m_pPlayer[nNpc] != nullptr)
	{
		//�V�[���擾�p
		CScene* pTop[PRIORITY_MAX] = {};
		//���`�F�b�N����V�[���̃|�C���^
		CScene* pNext = NULL;
		//NPC�̈ʒu
		D3DXVECTOR3 NPCPos = m_pPlayer[nNpc]->GetPos();
		//�����̋L�^�p�ϐ�
		float fDistance = NPC_SUSHI;

		//top�̃A�h���X���擾
		for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
		{
			pTop[nCount] = *(CScene::GetTop() + nCount);
		}

		//�I�u�W�F�N�g�T��
		for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
		{
			if (pTop[nCount] != NULL)
			{
				pNext = pTop[nCount];
				//���̕`��D��x�̃I�u�W�F�N�g���Ȃ��Ȃ�܂Ń��[�v
				while (pNext != NULL)
				{
					if (pNext->GetObjType() == CScene::OBJTYPE_SUSHI)
					{
						//���i�̈ʒu�擾
						D3DXVECTOR3 SushiPos = ((CPlayer*)pNext)->GetPos();
						//NPC�Ǝ��i�̋������v�Z
						float RangeX = SushiPos.x - NPCPos.x;
						float RangeZ = SushiPos.z - NPCPos.z;
						float Range = (float)(sqrt(RangeX * RangeX + RangeZ * RangeZ));

						//���̋������߂���
						if (NPC_SUSHI>Range)
						{
							//���݋L�^���Ă��鋗�����߂���
							if (fDistance>Range)
							{
								//�߂��ꍇ�L�^����
								fDistance = Range;
								//�����̋L�^
								m_NpcData[nNpc - 1].m_TargetRot = D3DXVECTOR3(RangeX, RangeZ, 0.0f);
								//���݂̃^�[�Q�b�g���擾
								m_NpcData[nNpc - 1].m_pTarget = pNext;
							}
						}
					}
					//���̃I�u�W�F�N�g�̃|�C���^���X�V
					pNext = pNext->GetNext();
				}
			}
		}
	}
}

//=============================================================================
// �m���Ō����������_���ɕύX�����֐�
//=============================================================================
void CPlayerControl::NpcRandomProbability(int nNpc)
{
	//�����_���֐��̏�����
	srand((unsigned int)time(NULL));
	//�����_���ɓ����p�̊m��
	int nRandom = (rand() % NPC_MAX_RANDOM);
	//���l��10�ȉ��ɂȂ�����
	if (nRandom <= 10)
	{
		//�����_���Ɍ����ύX
		NpcRandomControl(nNpc);
	}
}

//=============================================================================
// �����_�������ړ��֐�
//=============================================================================
void CPlayerControl::NpcRandomControl(int nNpc)
{
	//�����_���֐��̏�����
	srand((unsigned int)time(NULL));

	//X�̐��l
	float fXRandom = (float)((rand() % NPC_MAX_RANDOM_ROT) - NPC_MAX_RANDOM_ROT/2);
	//Y�̐��l
	float fYRandom = (float)((rand() % NPC_MAX_RANDOM_ROT) - NPC_MAX_RANDOM_ROT/2);
	//�����_���ɐݒ�
	m_NpcData[nNpc - 1].m_TargetRot = D3DXVECTOR3(fXRandom, fYRandom, 0.0f);

}

//=============================================================================
// �^�[�Q�b�g�ؑ֊֐�
//=============================================================================
void CPlayerControl::TargetSwitching(int nNpc)
{
	//�^�[�Q�b�g���ς���Ă��Ȃ���
	if (m_NpcData[nNpc - 1].m_pTarget == m_NpcData[nNpc - 1].m_pOldTarget)
	{
		//�ς���Ă��Ȃ��ƃJ�E���g�_�E��
		m_NpcData[nNpc - 1].m_nTargetCount--;
	}

	//�ς�����ۂ̏���
	else
	{
		//�^�[�Q�b�g���X�V
		m_NpcData[nNpc - 1].m_pOldTarget = m_NpcData[nNpc - 1].m_pTarget;
		//�J�E���g�_�E���̏�����
		m_NpcData[nNpc - 1].m_nTargetCount = NPC_MAX_TARGET_COUNT;
	}

	//�J�E���g�_�E����0�����ɂȂ�����
	if (m_NpcData[nNpc - 1].m_nTargetCount <= 0)
	{
		m_NpcData[nNpc - 1].m_bRandomControl = true;
		m_NpcData[nNpc - 1].m_nTargetCount = NPC_MAX_TARGET_COUNT;
	}
}

//=============================================================================
// �����_�������ړ�(������)�����֐�
//=============================================================================
void CPlayerControl::NpcRandomCount(int nNpc)
{
	//�����_���ړ��̃X�C�b�`�������Ă��邩
	if (m_NpcData[nNpc - 1].m_bRandomControl == true)
	{
		//�J�E���g�_�E��
		m_NpcData[nNpc - 1].m_nRandomCount--;

		//�����_���ړ�
		NpcRandomControl(nNpc);

		//�J�E���g��0�ɂȂ�����
		if (m_NpcData[nNpc - 1].m_nRandomCount <= 0)
		{
			//�J�E���g��������
			m_NpcData[nNpc - 1].m_nRandomCount = NPC_MAX_RANDOM;
			//�X�C�b�`��؂�
			m_NpcData[nNpc - 1].m_bRandomControl = false;
			return;
		}
	}
}

//=============================================================================
// �o���A������鏈���֐�
//=============================================================================
void CPlayerControl::AvoidBarrier(int nNpc)
{
	//�G���A�̒��S�擾
	D3DXVECTOR3 centre = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//(�R�R�̐��l��͈͐����̉~�̒��S���擾)
	//�G���A�̔��a
	float fRadius = (m_fMapSize / 2) - NPC_AVOID_BARRIER;									//(�R�R�̐��l��͈͐����̉~�̔��a���擾)

	//NPC�̈ʒu
	D3DXVECTOR3 NpcPos = m_pPlayer[nNpc]->GetPos();
	//NPC�ƃo���A����̋���
	float RangeX = NpcPos.x - centre.x;
	float RangeZ = NpcPos.z - centre.z;
	float Range = (float)(sqrt(RangeX * RangeX + RangeZ * RangeZ));

	if (Range >= PLAYER_SIZE + (fRadius))
	{
		//�����̋L�^
		m_NpcData[nNpc - 1].m_TargetRot = D3DXVECTOR3(-RangeX, -RangeZ, 0.0f);
	}
}
