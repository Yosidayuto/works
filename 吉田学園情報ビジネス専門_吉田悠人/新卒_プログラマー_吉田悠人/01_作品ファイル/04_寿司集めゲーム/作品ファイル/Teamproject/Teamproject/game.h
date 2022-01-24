//=============================================================================
//
// �Q�[���V�[������ [game.h]
// Author : �ѐ�ї���
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "scene.h"
#include "camera.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CInput;
class CScene2D;
class CCamera;
class CScore;
class CPlayerControl;
class CTimer;
class CMapManager;
//=============================================================================
//�}�l�[�W���[�N���X
//=============================================================================
class CGame : public CScene
{
public:
	typedef enum
	{
		MODETYPE_NONE = 0,
		MODETYPE_1,
		MODETYPE_2,
	} MODETYPE;

	typedef enum //���݂̏��
	{
		GAMESTATE_NONE = 0,
		GAMESTATE_1,
		GAMESTATE_2,
		GAMESTATE_3,
		GAMESTATE_4,
		GAMESTATE_5,
		GAMESTATE_6,
		GAMESTATE_7,
		GAMESTATE_MAX
	}GAME_STATE;

	CGame();
	~CGame();
	static CGame *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void GameOut(void);		// �Q�[���I�����̏���

	CScene2D * GetScene(void) { return m_pScene; };
	CGame * GetManager(void) { return this; };

	static bool GetIsStopUpdate(void) { return m_bIsStopUpdate; };
	static void SetIsStopUpdate(bool bIsStopUpdate) { m_bIsStopUpdate = bIsStopUpdate; };
	static bool GetIsStopUpdateContinue(void) { return m_bIsStopUpdateContinue; };
	static void SetIsStopUpdateContinue(bool bIsStopUpdateContinue) { m_bIsStopUpdateContinue = bIsStopUpdateContinue; };
	static CTimer * GetTimer(void) { return m_pTimer; };
	static GAME_STATE GetGameState(void) { return m_GameState; };
	static void SetGameType(MODETYPE mode) { m_mode = mode; };
	static MODETYPE GetGameType(void) { return m_mode; };
private:

	CScene2D*		m_pScene;				// �V�[���|�C���^
	int				m_nGameCount;			// �Q�[���J�E���g
	CPlayerControl* m_pPlayerControl;		// �v���C���[�R���g���[���|�C���^
	CMapManager *	m_pMapManager;			// �}�b�v�}�l�[�W���[�|�C���^
	
	static CCamera*	m_pCamera;				// �J�����|�C���^
	static CTimer*	m_pTimer;				// �^�C���|�C���^
	static D3DXVECTOR3 m_Score[MAX_PLAYER];	// �X�R�A�̈ʒu
	static MODETYPE		m_mode;				// �Q�[�����[�h

	static bool		m_bPlayerUse;			// �v���C���[���g���Ă��邩
	static bool		m_bIsStopUpdate;		// �A�b�v�f�[�g��~���Ă��邩
	static bool		m_bIsStopUpdateContinue;// �R���e�B�j���[�������Ă��邩
	static const int	m_aGameStateTime[GAMESTATE_MAX];	// �C�x���g�����^�C�~���O�i�[
	static GAME_STATE	m_GameState;		//���݂̏��
	int					m_endcount;			//�I���J�E���^
};
#endif