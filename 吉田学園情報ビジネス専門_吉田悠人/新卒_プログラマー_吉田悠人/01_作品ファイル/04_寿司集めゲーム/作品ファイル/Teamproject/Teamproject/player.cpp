//=============================================================================
//
//	�v���C���[[player.cpp]
//	Author:�g�c�I�l
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "player.h"
#include "renderer.h"
#include "resource manager.h"
#include "keyboard.h"
#include "mouse.h"
#include "joystick.h"
#include "player parts.h"
#include "ebi parts.h"
#include "egg parts.h"
#include "ikura parts.h"
#include "salmon parts.h"
#include "tuna parts.h"
#include "food base.h"
#include "ebi.h"
#include "egg.h"
#include "ikura.h"
#include "salmon.h"
#include "tuna.h"
#include "ShieldEffect.h"
#include "sound.h"
#include "effect powerup.h"
#include "game.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define PLAYER_SPEED		(1.0f)	// �v���C���[�̃X�s�[�h(��ŕύX)
#define PLAYER_BOOST_SPEED	(2.0f)	// �v���C���[�̃u�[�X�g�X�s�[�h(��ŕύX)
#define PLAYER_ROT_SPEED	(10.0f)	// �v���C���[�̐U��������x(��ŕύX)
#define PLAYER_REPEL		(15.0f)	// �v���C���[���͂�����鋗��
#define PLAYER_REPEL_FRAME	(10.0f)	// �v���C���[�̂͂����ꂽ�ۂ̃t���[��
#define PLAYER_INVINCIBLE	(30*3)	// �v���C���[�̖��G����
#define PLAYER_DASH_DEMERIT	(30*2)	// �v���C���[�̃_�b�V�����̃f�����b�g�J�E���g
#define ITEM_EFFECT_COUNT	(150)	// �A�C�e���̌��ʎ���


//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPlayer::CPlayer(int nPriority)
{
	SetObjType(OBJTYPE_PLAYER);								// �I�u�W�F�N�g�^�C�v�ݒ�
	m_nLife				 = 0;								// ���C�t�̏�����
	m_nRepelFrameCount	 = 0;								// �͂����ꂽ�ۂ̃t���[���l�̏�����
	m_nFlashing			 = 0;								// ���S���̃J�E���g�t���[���l�@�̏�����
	m_nInvinciFrameCount = 0;								// ���G��Ԃ̃t���[���J�E���g�̏�����
	m_MaxInvinciCount	 = 0;								// ���G��Ԃ̍ő吔�̏�����
	m_fDashDemeritCoutn	 = PLAYER_DASH_DEMERIT;				// �������̃f�����b�g�J�E���g�̏�����
	m_fDashCoutn	= 0;									// �����l�̏�����
	m_nParts		= 0;									// �p�[�c���̏�����
	m_nItemCount	= ITEM_EFFECT_COUNT;					// �X�R�A�A�b�v��Ԃ̎���
	m_PlayerStats	= PLAYER_STATS_NORMAL;					// �v���C���[�X�e�[�^�X�̏�����
	m_bInvincible	= false;								// ���G��Ԃ̏�����
	m_bDashSwitch	= false;								// �_�b�V���ؑւ̏�����
	m_bShield		= false;								// �A�C�e���V�[���h�X�C�b�`�̏�����
	m_bScoreUp		= false;					// �A�C�e���X�R�A�A�b�v�̏�����
	m_RotMove		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �����̈ړ��ʂ̏�����
	m_RepelMove		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �͂����ꂽ�ۂ̈ړ��ʂ̏�����

	for (int nParts = 0; nParts < MAX_PARTS; nParts++)
	{
		m_pParts[nParts] = nullptr;
	}
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPlayer::~CPlayer()
{

}

//=============================================================================
// ���������֐�
//=============================================================================
CPlayer * CPlayer::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, D3DXVECTOR3 Size, int nModel)
{
	//�������m��
	CPlayer* pPlayer = NULL;
	pPlayer = new CPlayer;
	//���\�[�X�m��
	CResource* pResource = CManager::GetResource();
	MODELDATA Model = pResource->ModelLoad(nModel);

	//NULL�`�F�b�N
	if (pPlayer != NULL)
	{
		//�ʒu�ݒ�
		pPlayer->SetPos(Pos);
		//�����ݒ�
		pPlayer->SetRot(Rot);
		//�J���[�ݒ�
		pPlayer->SetSize(Size);
		//���f���f�[�^�ݒ�
		pPlayer->SetModelData(Model);
		//����������
		pPlayer->Init();
	}

	return pPlayer;
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CPlayer::Update(void)
{
	//��Ԃɂ���ď����̕ύX
	switch (m_PlayerStats)
	{

	case PLAYER_STATS_NORMAL:	//�ʏ��Ԃ̏ꍇ
		//�ړ�����
		Move();
		//�p�x����
		Rot();
		//�_�b�V�����̃f�����b�g����
		DashDemerit();
		break;

	case PLAYER_STATS_REPEL:	//�͂�����Ă���ꍇ
		RepelMove();
		break;

	case PLAYER_STATS_RESPAWN:	// ���X�|�[�����
		RespawnStats();
		break;

	case PLAYER_STATS_DEATH:	//���S���Ă���ꍇ
		Death();
		break;
	}
	// ���G���ԏ����֐�
	Invincible();
	
	//�X�R�A�A�b�v�̃A�C�e�����E������
	if (m_bScoreUp == true)
	{
		// �X�R�A�A�b�v�̐������ԏ���
		ScoreUpCount();
	}
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CPlayer::Draw(void)
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

	//�`�揈��
	CModel::Draw();

	//�A���t�@�e�X�g�𖳌���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=============================================================================
// �ړ������֐�
//=============================================================================
void CPlayer::Move(void)
{
	//�ʒu�擾
	D3DXVECTOR3 pos = GetPos();
	//�����擾
	D3DXVECTOR3 rot = GetRot();
	//�ړ���
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//�ړ�����
	move = D3DXVECTOR3((float)(cos(rot.y + D3DXToRadian(90.0f))), 0.0f, (float)(sin(rot.y - D3DXToRadian(90.0f))));

	if (!m_bDashSwitch)
	{
		if (m_fDashCoutn <= PLAYER_SPEED)
		{
			m_fDashCoutn = m_fDashCoutn + 0.1f;
		}
		else if (m_fDashCoutn > PLAYER_SPEED)
		{
			m_fDashCoutn = m_fDashCoutn - 0.1f;

		}
	}
	else
	{
		if (m_fDashCoutn <= PLAYER_BOOST_SPEED)
		{
			m_fDashCoutn = m_fDashCoutn + 0.1f;
		}
		else if (m_fDashCoutn > PLAYER_BOOST_SPEED)
		{
			m_fDashCoutn = m_fDashCoutn - 0.1f;
		}
	}
	//�X�s�[�h���v�Z
	move *= m_fDashCoutn;
	// �ړ�����
	pos += move;

	// �ʒu�ۑ�
	SetPos(pos);

}

//=============================================================================
// ���������֐�
//=============================================================================
void CPlayer::Rot(void)
{
	//�p�x�̈ړ���
	float fRotMove = 0.0f;
	//�ʒu�擾
	D3DXVECTOR3 pos = GetPos();
	//�����擾
	D3DXVECTOR3 rot = GetRot();
	//���������p�x
	fRotMove = atan2f((pos.x - (m_RotMove.x + pos.x)), (pos.z - (m_RotMove.z + pos.z)));
	//�����̊p�x
	float fDiff = ((D3DXToRadian(180.0f) - (fRotMove*-1.0f)) - (D3DXToRadian(180.0f) - (rot.y*-1.0f)))*-1.0f;
	//��]�����̊m�F(���v����true:�����v���false)
	bool bRotation = fRotMove>rot.y ? !(fRotMove - rot.y > D3DXToRadian(180.0f)) : rot.y - fRotMove  > D3DXToRadian(180.0f);
	//�����̏C��
	fDiff = (fDiff + (bRotation ? D3DXToRadian(-360.0f) : D3DXToRadian(360.0f)));
	fDiff = (float)(fmod(fDiff, D3DXToRadian(360.0f)));
	//��������
	rot.y = rot.y - (fDiff*(0.04f));
	//�p�x�����ɒB������C��
	if (D3DXToDegree(rot.y) >= 360.0f
		|| D3DXToDegree(rot.y) <= -360.0f)
	{
		rot.y = 0.0f;
	}
	// �����ۑ�
	SetRot(rot);
}

//=============================================================================
// �͂����ꂽ�ۂ̈ړ������֐�
//=============================================================================
void CPlayer::RepelMove(void)
{
	//�ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	//�ړ�����
	pos = pos + (m_RepelMove - pos) / (PLAYER_REPEL_FRAME - m_nRepelFrameCount);
	//�ʒu�Z�b�g
	SetPos(pos);
	//�t���[�����Z
	m_nRepelFrameCount++;

	if (m_nRepelFrameCount >= PLAYER_REPEL_FRAME)
	{
		//�J�E���g������
		m_nRepelFrameCount = 0;
		//�X�e�[�^�X��ύX
		SetStats(PLAYER_STATS_NORMAL);
	}
}

//=============================================================================
// �͂�����鏈���֐�
//=============================================================================
void CPlayer::Repel(CScene3d* Player)
{
	//�v���C���[�̏�Ԃ��ʏ�̏ꍇ�����G��ԏo�Ȃ��Ƃ�
	if (m_PlayerStats == PLAYER_STATS_NORMAL
		&&m_bInvincible == false)
	{
		//���݈ʒu
		D3DXVECTOR3 pos = GetPos();
		//����̈ʒu
		D3DXVECTOR3 PlayerPos = Player->GetPos();
		//������������
		D3DXVECTOR3 HItPint = D3DXVECTOR3(0.0f, atan2f((PlayerPos.x - pos.x), (PlayerPos.z - pos.z)), 0.0f);;
		//�@���x�N�g���̌v�Z
		D3DXVECTOR3 Normal = PlayerPos - pos;
		//�ړ�����
		D3DXVECTOR3 move = D3DXVECTOR3((float)(cos(HItPint.y + D3DXToRadian(90.0f))), 0.0f, (float)(sin(HItPint.y - D3DXToRadian(90.0f))));

		//�ړ���
		D3DXVec3Normalize(&Normal, &Normal);
		//�ړ��ʂ̌v�Z
		D3DXVec3Normalize(&m_RepelMove, &(move - 2.0f * D3DXVec3Dot(&move, &Normal) * Normal));
		m_RepelMove = (-m_RepelMove*PLAYER_REPEL) + pos;
		//�����l�̏�����
		m_fDashCoutn = 0.0f;
		//��莞�Ԗ��G�ɂ���
		SwitchedInvincible(PLAYER_INVINCIBLE);

		//�V�[���h�A�C�e���������Ă��邩
		//�����Ă��Ȃ��ꍇ
		if (m_bShield == false)
		{
			//�͂������Ԃɕω�
			SetStats(PLAYER_STATS_REPEL);
		}
		//�����Ă����ꍇ
		else
		{
			//�A�C�e��������Ėh��
			m_bShield = false;
		}
	}
}

//=============================================================================
// �p�[�c�ǉ��i�H�ו���H�ׂ���̒ǉ��p�[�c�j�����֐�
//=============================================================================
void CPlayer::AddParts(CFoodBase::FOOD_TYPE FoodType)
{
	if (m_PlayerStats != PLAYER_STATS_DEATH|| m_PlayerStats != PLAYER_STATS_RESPAWN)
	{
		//�p�[�c���Ȃ���
		if (m_nParts == 0)
		{
			//�ʒu�擾
			D3DXVECTOR3 pos = GetPos();
			//�����擾
			D3DXVECTOR3 rot = GetRot();
			//��������
			switch (FoodType)
			{
			case CFoodBase::TYPE_EBI:
				m_pParts[m_nParts] = CEbiParts::Create(pos, rot, D3DXVECTOR3(10.0f, 10.0f, 10.0f), this);
				break;
			case CFoodBase::TYPE_EGG:
				m_pParts[m_nParts] = CEggParts::Create(pos, rot, D3DXVECTOR3(10.0f, 10.0f, 10.0f), this);
				break;
			case CFoodBase::TYPE_IKURA:
				m_pParts[m_nParts] = CIkuraParts::Create(pos, rot, D3DXVECTOR3(10.0f, 10.0f, 10.0f), this);
				break;
			case CFoodBase::TYPE_SALMON:
				m_pParts[m_nParts] = CSalmonParts::Create(pos, rot, D3DXVECTOR3(10.0f, 10.0f, 10.0f), this);
				break;
			case CFoodBase::TYPE_TUNA:
				m_pParts[m_nParts] = CTunaParts::Create(pos, rot, D3DXVECTOR3(10.0f, 10.0f, 10.0f), this);
				break;
			}
		}
		//�p�[�c���P�ł����鎞
		else if (m_nParts>0 && m_nParts<MAX_PARTS)
		{
			//�ʒu�擾
			D3DXVECTOR3 PartsPos = m_pParts[m_nParts - 1]->GetPos();
			//�����擾
			D3DXVECTOR3 PartsRot = m_pParts[m_nParts - 1]->GetRot();
			//��������
			switch (FoodType)
			{
			case CFoodBase::TYPE_EBI:
				m_pParts[m_nParts] = CEbiParts::Create(m_pParts[m_nParts - 1]->GetPos(), PartsRot, D3DXVECTOR3(10.0f, 10.0f, 10.0f), m_pParts[m_nParts - 1]);
				break;
			case CFoodBase::TYPE_EGG:
				m_pParts[m_nParts] = CEggParts::Create(m_pParts[m_nParts - 1]->GetPos(), PartsRot, D3DXVECTOR3(10.0f, 10.0f, 10.0f), m_pParts[m_nParts - 1]);
				break;
			case CFoodBase::TYPE_IKURA:
				m_pParts[m_nParts] = CIkuraParts::Create(m_pParts[m_nParts - 1]->GetPos(), PartsRot, D3DXVECTOR3(10.0f, 10.0f, 10.0f), m_pParts[m_nParts - 1]);
				break;
			case CFoodBase::TYPE_SALMON:
				m_pParts[m_nParts] = CSalmonParts::Create(m_pParts[m_nParts - 1]->GetPos(), PartsRot, D3DXVECTOR3(10.0f, 10.0f, 10.0f), m_pParts[m_nParts - 1]);
				break;
			case CFoodBase::TYPE_TUNA:
				m_pParts[m_nParts] = CTunaParts::Create(m_pParts[m_nParts - 1]->GetPos(), PartsRot, D3DXVECTOR3(10.0f, 10.0f, 10.0f), m_pParts[m_nParts - 1]);
				break;
			}
		}

		//�p�[�c���𑝂₷
		m_nParts++;

	}
}

//=============================================================================
// �R���g���[���[���쏈���֐�
//=============================================================================
void CPlayer::RotControl(D3DXVECTOR3 Control)
{
	//�X�e�B�b�N�ɐG��Ă��邩�̊m�F�iControl�̂��Ƃ����ǂ����0.0f�̏ꍇ�G��Ă��Ȃ��j
	bool TouchStick = Control.x == 0.0f&&Control.y == 0.0f ? true : false;
	
	//�X�e�B�b�N�ɐG��Ă���ꍇ�̏���
	if(TouchStick!= true)
	{
		//�P�ʃx�N�g���擾
		D3DXVec3Normalize(&m_RotMove, &D3DXVECTOR3(Control.x, 0.0f, Control.y));
	}
}

//=============================================================================
// �_�b�V����ԂɈڍs
//=============================================================================
void CPlayer::Dash(bool bDash)
{
	m_bDashSwitch = bDash;
}

//=============================================================================
// �v���C���[���_���[�W���󂯂郂�m�ɂԂ������ۂ̏����֐�
//=============================================================================
void CPlayer::DamageHit(void)
{
	if (m_PlayerStats == PLAYER_STATS_NORMAL)
	{
		//�V�[���h�A�C�e���������Ă��Ȃ������ꍇ
		if (m_bShield == false)
		{
			if (m_bInvincible == false)
			{
				//��Ԃ����X�|�[����ԂɕύX
				SetStats(PLAYER_STATS_RESPAWN);

				//���S��
				CSound *pSound = CManager::GetSound();
				pSound->PlaySound(CSound::LABEL_SE_DEATH);

				//�����Ă�����i���΂�T��
				for (int nParts = 0; nParts < m_nParts; nParts++)
				{
					if (m_pParts[nParts] != nullptr)
					{
						//�p�[�c�̈ʒu�擾
						D3DXVECTOR3 PartsPos = m_pParts[nParts]->GetPos();
						switch (m_pParts[nParts]->GetType())
						{
						case CFoodBase::TYPE_EBI:
							CEbi::Create(PartsPos, D3DXVECTOR3(10.0f, 10.0f, 10.0f));
							break;
						case CFoodBase::TYPE_EGG:
							CEgg::Create(PartsPos, D3DXVECTOR3(10.0f, 10.0f, 10.0f));
							break;
						case CFoodBase::TYPE_IKURA:
							CIkura::Create(PartsPos, D3DXVECTOR3(10.0f, 10.0f, 10.0f));
							break;
						case CFoodBase::TYPE_SALMON:
							CSalmon::Create(PartsPos, D3DXVECTOR3(10.0f, 10.0f, 10.0f));
							break;
						case CFoodBase::TYPE_TUNA:
							CTuna::Create(PartsPos, D3DXVECTOR3(10.0f, 10.0f, 10.0f));
							break;
						}
						m_pParts[nParts]->Uninit();
						m_pParts[nParts] = nullptr;
					}
				}
				m_nParts = 0;
			}
		}
		//�����Ă����ꍇ
		else
		{
			//�A�C�e��������
			m_bShield = false;
			//��莞�Ԗ��G�ɂ���
			m_bInvincible = true;
			//�q�b�g��
			CSound *pSound = CManager::GetSound();
			pSound->PlaySound(CSound::LABEL_SE_HITPLAYER);
		}
	}
}

//=============================================================================
// �}�b�v�[�ł̃_���[�W�q�b�g����
//=============================================================================
void CPlayer::BarrierHit(void)
{
	if (m_PlayerStats == PLAYER_STATS_NORMAL)
	{
		//��Ԃ����X�|�[����ԂɕύX
		SetStats(PLAYER_STATS_RESPAWN);

		//���S��
		CSound *pSound = CManager::GetSound();
		pSound->PlaySound(CSound::LABEL_SE_DEATH);

		//�����Ă�����i���΂�T��
		for (int nParts = 0; nParts < m_nParts; nParts++)
		{
			if (m_pParts[nParts] != nullptr)
			{
				//�p�[�c�̈ʒu�擾
				D3DXVECTOR3 PartsPos = m_pParts[nParts]->GetPos();
				switch (m_pParts[nParts]->GetType())
				{
				case CFoodBase::TYPE_EBI:
					CEbi::Create(PartsPos, D3DXVECTOR3(10.0f, 10.0f, 10.0f));
					break;
				case CFoodBase::TYPE_EGG:
					CEgg::Create(PartsPos, D3DXVECTOR3(10.0f, 10.0f, 10.0f));
					break;
				case CFoodBase::TYPE_IKURA:
					CIkura::Create(PartsPos, D3DXVECTOR3(10.0f, 10.0f, 10.0f));
					break;
				case CFoodBase::TYPE_SALMON:
					CSalmon::Create(PartsPos, D3DXVECTOR3(10.0f, 10.0f, 10.0f));
					break;
				case CFoodBase::TYPE_TUNA:
					CTuna::Create(PartsPos, D3DXVECTOR3(10.0f, 10.0f, 10.0f));
					break;
				}

				m_pParts[nParts]->Uninit();
				m_pParts[nParts] = nullptr;
			}
		}
		m_nParts = 0;
	}
}

//=============================================================================
// ���X�|�[������
//=============================================================================
void CPlayer::Respawn(D3DXVECTOR3 RespawnPos)
{
	if (m_PlayerStats == PLAYER_STATS_RESPAWN)
	{
		//���X�|�[���ʒu
		SetPos(RespawnPos);
		//�X�e�[�^�X�ݒ�
		SetStats(PLAYER_STATS_NORMAL);
		//���X�|�[�����Ɉ�莞�Ԗ��G�ɂ���
		SwitchedInvincible(PLAYER_INVINCIBLE);
		//�A�C�e���̌��ʂ�؂�
		m_bShield = false;
		m_bScoreUp = false;
		//�A���t�@�l��������
		SetAlphaValue(1.0f);
	}
}

//=============================================================================
// �V�[���h�擾����
//=============================================================================
void CPlayer::ShieldGet(void)
{
	//�A�C�e���������Ă��邩
	if (m_bShield == false)
	{
		//�q�b�g��
		CSound *pSound = CManager::GetSound();
		pSound->PlaySound(CSound::LABEL_SE_GETITEM);

		//�擾��Ԃ̂���true�ɕύX
		m_bShield = true;
		//�����ڂɕω��H
		D3DXVECTOR3 pos = GetPos();
		CShieldEffect::Create(D3DXVECTOR3(pos.x, pos.y + 13.0f ,pos.z), D3DXVECTOR3(30.0f, 30.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 125),this);
	}
}

//=============================================================================
// �X�R�A�A�b�v�擾����
//=============================================================================
void CPlayer::ScoreUpGet(void)
{
	//�A�C�e���������Ă��邩
	if (m_bScoreUp == false)
	{
		//�q�b�g��
		CSound *pSound = CManager::GetSound();
		pSound->PlaySound(CSound::LABEL_SE_GETITEM);

		//�擾��Ԃ̂���true�ɕύX
		m_bScoreUp = true;
		//�����ڂɕω��H
		D3DXVECTOR3 pos = GetPos();
		CEffectPowerUP::Create(pos, D3DXVECTOR3(30.0f, 30.0f, 0.0f), this);
	}
}

//=============================================================================
//�X�R�A�A�b�v��Ԃ̎���
//=============================================================================
void CPlayer::ScoreUpCount(void)
{
	//�J�E���g�����炷
	m_nItemCount--;

	if (m_nItemCount <= 0)
	{
		//��Ԃ����ɖ߂�
		m_bScoreUp = false;
		//���l�����ɖ߂�
		m_nItemCount = ITEM_EFFECT_COUNT;
	}

}

//=============================================================================
// ���S�����֐�
//=============================================================================
void CPlayer::Death(void)
{
	SetAlphaValue(0.0f);
}

//=============================================================================
// ���G���ԏ����֐�
//=============================================================================
void CPlayer::Invincible(void)
{
	//���G�X�C�b�`��true�̏ꍇ
	if (m_bInvincible == true)
	{
		//�_�ŏ���
		Flashing();
		//�J�E���g�_�E��
		m_nInvinciFrameCount++;
		//�J�E���g�����ɒB������
		if (m_nInvinciFrameCount >= PLAYER_INVINCIBLE)
		{
			//�J�E���g�̏�����
			m_nInvinciFrameCount = 0;
			//���G�X�C�b�`��false�ɂ���
			m_bInvincible = false;
			//�_�ŃX�g�b�v
			FlashingStop();
			return;
		}
	}
}

//=============================================================================
// ���G�X�C�b�`�I�������֐�
//=============================================================================
void CPlayer::SwitchedInvincible(int nInvincible)
{
	// ���G���ǂ���
	if (!m_bInvincible)
	{
		//�J�E���g�̍ő吔����������
		m_MaxInvinciCount = nInvincible;
		//���G�X�C�b�`�I��
		m_bInvincible = true;
	}
}

//=============================================================================
// ���X�|�[����Ԏ�����
//=============================================================================
void CPlayer::RespawnStats(void)
{
	SetAlphaValue(0.0f);
}

//=============================================================================
// �_�b�V�����̃f�����b�g�����֐�
//=============================================================================
void CPlayer::DashDemerit(void)
{
	//�_�b�V����ԃ`�F�b�N
	if (m_bDashSwitch)
	{
		//�J�E���g�_�E��
		m_fDashDemeritCoutn--;

		//�a�𗎂Ƃ�
		if (m_fDashDemeritCoutn == 0)
		{
			if (m_pParts[m_nParts - 1] != nullptr)
			{
				//�p�[�c�̈ʒu�擾
				D3DXVECTOR3 PartsPos = m_pParts[m_nParts - 1]->GetPos();
				switch (m_pParts[m_nParts - 1]->GetType())
				{
				case CFoodBase::TYPE_EBI:
					CEbi::Create(PartsPos, D3DXVECTOR3(10.0f, 10.0f, 10.0f));
					break;
				case CFoodBase::TYPE_EGG:
					CEgg::Create(PartsPos, D3DXVECTOR3(10.0f, 10.0f, 10.0f));
					break;
				case CFoodBase::TYPE_IKURA:
					CIkura::Create(PartsPos, D3DXVECTOR3(10.0f, 10.0f, 10.0f));
					break;
				case CFoodBase::TYPE_SALMON:
					CSalmon::Create(PartsPos, D3DXVECTOR3(10.0f, 10.0f, 10.0f));
					break;
				case CFoodBase::TYPE_TUNA:
					CTuna::Create(PartsPos, D3DXVECTOR3(10.0f, 10.0f, 10.0f));
					break;
				}

				m_pParts[m_nParts - 1]->Uninit();
				m_pParts[m_nParts - 1] = nullptr;
				m_nParts -= 1;
				m_fDashDemeritCoutn = PLAYER_DASH_DEMERIT;

			}
		}
	}
}

//=============================================================================
// �_�ŏ����֐�
//=============================================================================
void CPlayer::Flashing(void)
{
	//�J�E���g
	m_nFlashing++;
	if (m_nFlashing % 3)
	{
		SetAlphaValue(1.0f);
	}
	else
	{
		SetAlphaValue(0.0f);
	}
}

//=============================================================================
// �_�ŃX�g�b�v�����֐�
//=============================================================================
void CPlayer::FlashingStop(void)
{
	//�_�ł̃J�E���g������
	m_nFlashing = 0;
	//�A���t�@�l��������
	SetAlphaValue(1.0f);
}

