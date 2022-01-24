//=============================================================================
//
// �v���C���[���� [player control.h]
// Author : �g�c�I�l
//
//=============================================================================
#ifndef _PLAYER_CONTROL_H_
#define _PLAYER_CONTROL_H_

//=============================================================================
// �w�b�_�[�t�@�C��
//=============================================================================
#include "scene3d.h"
#include "model.h"

//=============================================================================
// �O���錾
//=============================================================================
class CPlayer;
class CScene;
class CScore;
class CRespawnCount;

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_NPC (MAX_PLAYER - 1)	// NPC�̍ő吔�i-1����̂�1�l�̓v���C���[�����邽�߁j

//=============================================================================
//�N���X��`
//=============================================================================
class CPlayerControl : public CScene
{
public:
	CPlayerControl(int nPriority = 3);
	~CPlayerControl();
	static CPlayerControl *Create();	// ���������֐�
	HRESULT	Init(void);					// �����������֐�
	void	Uninit(void);				// �I�������֐�
	void	Update(void);				// �X�V�����֐�
	void	Draw(void);					// �`�揈���֐�

	CPlayer * GetPlayer(int nPlayer) { return m_pPlayer[nPlayer]; }	// �v���C���[�Q�b�^�[�֐�
	void	SetNumberPlayer(int nNumber);							// �v���C���[�l���擾
	void	SetRespawn(bool Respawn);								// ���X�|�[���X�C�b�`�Z�b�^�[
	void	SetMapSize(float fMapSize) { m_fMapSize = fMapSize; };	// �X�e�[�W�T�C�Y

private:

	void RespawnControl(int nPlayer);		// �v���C���[�̃��X�|�[��
	void DamageHit(int nPlayer);			// ���̃v���C���[�̓��������ۂ̃_���[�W����
	void PlayerHit(int nPlayer);			// �v���C���[�̃q�b�g����
	void PlayerControl(int nPlayer);		// �v���C���[����֐�
	void PlayerKeyControl(void);			// �v���C���[����֐��i�L�[�{�[�h�j
	void PlayerScore(int nPlayer);			// �v���C���[�̃X�R�A����

	void NpcControl(int nNpc);				// NPC����֐�
	void PlayerProcessCriteria(int nNpc);	// NPC�ƃv���C���[�̊֌W����
	void ItemProcessCriteria(int nNpc);		// NPC�ƃA�C�e���̊֌W����
	void SushiProcessCriteria(int nNpc);	// NPC�Ǝ��i�̊֌W����
	void NpcRandomProbability(int nNpc);	// �m���Ō����������_���ɕύX
	void NpcRandomControl(int nNpc);		// �����_�������ړ�
	void TargetSwitching(int nNpc);			// �^�[�Q�b�g�ؑ֊֐�
	void NpcRandomCount(int nNpc);			// �����_�������ړ�(������)
	void AvoidBarrier(int nNpc);			// �o���A������鏈��


	typedef struct
	{
		D3DXVECTOR3 m_TargetRot;				// �ړI�̌���
		int			m_nRandomCount;				// �����_�������ړ��p�̃J�E���g
		int			m_nTargetCount;				// �^�[�Q�b�g�̐؂�ւ��悤�̃J�E���g
		bool		m_bRandomControl;			// �����_���ړ���Ԃ��ǂ���
		CScene*		m_pTarget;					// ���݂̃^�[�Q�b�g�V�[��
		CScene*		m_pOldTarget;				// �L�����Ă���^�[�Q�b�g�V�[��
	}NPC_DATA;

	const int		m_nPlayerModel[MAX_PLAYER] = { 1,2,3,4 };		// �v���C���[���f���ԍ�
	CRespawnCount*	m_pRespawnCount[MAX_PLAYER];					// ���X�|�[�����̃J�E���gUI�|�C���^
	CPlayer*		m_pPlayer[MAX_PLAYER];				// �v���C���[�|�C���^
	int				m_nRespawn[MAX_PLAYER];				// �v���C���[�̃��X�|�[���J�E���g
	static D3DXVECTOR3 m_PlayerPos[MAX_PLAYER];			// �v���C���[�̈ʒu
	int				m_nNumberPlayer;					// ����v���C���[�̐l��
	bool			m_bRespawn;							// �v���C���[���X�|�[���X�C�b�`
	float			m_fMapSize;							// �}�b�v�T�C�Y
	NPC_DATA		m_NpcData[MAX_NPC];					// NPC�̏��
	bool			m_GemeEnd;							// �v���C���[�A��l�ɂȂ����ۂ̏����X�C�b�`
	static D3DXVECTOR3 m_RespawnCountPos[MAX_PLAYER];	// ���X�|�[���J�E���g�̈ʒu
};
#endif // !_PLAYER_CONTROL_H_

