//=============================================================================
//
// �v���C���[ [player.h]
// Author : �g�c�I�l
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//=============================================================================
// �w�b�_�[�t�@�C��
//=============================================================================
#include "scene3d.h"
#include "model.h"
#include "food base.h"
//=============================================================================
// �O���錾
//=============================================================================
class CPlayerParts;
//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_PARTS (500)	//�ő�p�[�c��

//=============================================================================
//�N���X��`
//=============================================================================
class CPlayer : public CModel
{
public:
	CPlayer(int nPriority = 3);
	~CPlayer();
	typedef enum	//�v���C���[�̏��
	{
		PLAYER_STATS_NONE = 0,	// NULL
		PLAYER_STATS_NORMAL,	// �ʏ���
		PLAYER_STATS_REPEL,		// �͂�������
		PLAYER_STATS_RESPAWN,	// ���X�|�[�����
		PLAYER_STATS_DEATH		// ���S���
	}PLAYER_STATS;

	static CPlayer* Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, D3DXVECTOR3 Size,int nModel);	//��������

	void			Update(void);
	void			Draw(void);
	void			Repel(CScene3d* Player);					// �͂�����鏈��
	void			AddParts(CFoodBase::FOOD_TYPE FoodType);	// �p�[�c�ǉ��i�H�ו���H�ׂ���̒ǉ��p�[�c�j�����֐�
	virtual void	RotControl(D3DXVECTOR3 Control);			// �R���g���[���[�ł̑���
	void			Dash(bool bDash);							// �_�b�V����ԂɈڍs
	void			DamageHit(void);							// �v���C���[���_���[�W���󂯂郂�m�ɂԂ������ۂ̏���
	void			BarrierHit(void);							// �}�b�v�[�ł̃_���[�W�q�b�g����
	void			Respawn(D3DXVECTOR3 RespawnPos);			// ���X�|�[������
	void			ShieldGet(void);							// �V�[���h�擾����
	void			ScoreUpGet(void);							// �X�R�A�A�b�v����
	void			ScoreUpCount(void);							// �X�R�A�A�b�v
	void			SwitchedInvincible(int nInvincible);		// ���G��ԂɈڍs

	CPlayerParts*	GetParts(int nParts) { return m_pParts[nParts]; }				// �p�[�c�Q�b�^�[
	int				GetPartsCount(void) { return m_nParts; }						// �p�[�c���Q�b�^�[
	void			SetStats(const PLAYER_STATS Stats) { m_PlayerStats = Stats; }	// �v���C���[��ԃZ�b�^�[
	PLAYER_STATS	GetStats(void) { return m_PlayerStats; }						// �v���C���[��ԃQ�b�^�[
	bool			GetScoreUp(void) { return m_bScoreUp; }							// �X�R�A�A�b�v��Ԃ̃Q�b�^�[
	bool			GetShield(void) { return m_bShield; }							// �V�[���h��Ԃ̃Q�b�^�[

private:
	void			Move(void);								// �ړ�����
	void			Rot(void);								// ��������
	void			Invincible(void);						// ���G����
	void			DashDemerit(void);		// �_�b�V�����̃f�����b�g����
	void			RepelMove(void);		// �͂�����ړ�����
	void			RespawnStats(void);		// ���X�|�[����Ԏ�����
	void			Death(void);			// ���S����
	void			Flashing(void);			// �_�ŏ���
	void			FlashingStop(void);		// �_�ŃX�g�b�v����

	PLAYER_STATS	m_PlayerStats;			// �v���C���[�X�e�[�^�X
	int				m_nLife;				// ���C�t
	D3DXVECTOR3		m_RotMove;				// �����̈ړ���
	int				m_nRepelFrameCount;		// �͂����ꂽ�ۂ̈ړ����̃t���[���J�E���g
	D3DXVECTOR3		m_RepelMove;			// �͂�����ړ���
	int				m_nFlashing;			// �_�ł���ۂ̃t���[���J�E���g
	bool			m_bInvincible;			// ���G��Ԃ̃X�C�b�`
	int				m_nInvinciFrameCount;	// ���G��Ԃ̃t���[���J�E���g
	int				m_MaxInvinciCount;		// ���G��Ԃ̍ő�J�E���g��
	bool			m_bShield;				// �A�C�e���̃V�[���h�X�C�b�`�i�����Ă��邩�j
	bool			m_bScoreUp;				// �A�C�e���̃X�R�A�A�b�v�́@(��ԂɂȂ��Ă��邩)
	float			m_fDashCoutn;			// �����l
	float			m_fDashDemeritCoutn;	// �������̃f�����b�g�J�E���g
	bool			m_bDashSwitch;			// �����ؑփX�C�b�`
	int				m_nParts;				// �p�[�c��
	CPlayerParts*	m_pParts[MAX_PARTS];	// �p�[�c�|�C���^
	int				m_nItemCount;			// ���ʃJ�E���g�p�ϐ�
};
#endif // !_PLAYER_H_


