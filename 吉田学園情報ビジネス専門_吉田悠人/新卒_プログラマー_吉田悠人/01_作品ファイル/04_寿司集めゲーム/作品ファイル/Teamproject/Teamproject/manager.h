//=============================================================================
//
// �Ǘ� [manager.h]
// Author : �ѐ�ї���
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CRenderer;
class CKeyboard;
class CJoystick;
class CScene2d;
class CSound;
class CCamera;
class CLight;
class CMode;
class CGame;
class CPlayer;
class CMouse;
class CMapManager;
class CTitle;
class CSelect;
class CResource;
class CScore;
class CPlayerControl;
class CResult;
class CFade;
class CTutorial;
//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CManager
{
public:
	typedef enum
	{
		MODE_NONE = -1,
		MODE_TITLE,
		MODE_SELECT,
		MODE_GAME,
		MODE_TUTORIAL,
		MODE_RESULT,
		MODE_RANKING,
		MODE_END
	}MODE;
	CManager();
	~CManager();
	HRESULT Init(HINSTANCE hInsitance, HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static void SetMode(MODE mode);
	static MODE GetMode(void) { return m_mode; };
	static CRenderer * GetRenderer(void) { return m_pRenderer; };
	static CKeyboard * GetInputKeyboard(void) { return m_pKeyboard; };
	static CMouse * GetInputMouse(void) { return m_pMouse; };
	static CJoystick * GetInputJoystick(void) { return m_pJoystick; };
	static CSound * GetSound(void) { return m_pSound; };
	static CCamera *GetCamera(void) { return m_pCamera; }
	static CPlayer * GetPlayer(void) { return m_pPlayer; };
	static void CreateCamera(void);
	static void CreateLight(void);
	static void BindCamera(CCamera* pCamera);
	static bool GetIsActiveWindow(void);
	static CResource* GetResource(void) { return m_pResource; };			// ���\�[�X�Q�b�^�[
	static CScore * GetScore(int nPlayer) { return m_apScore[nPlayer]; };
	static void SetScore(CScore * pScore, int nPlayer);
	static void SetPlayerControl(CPlayerControl * pPlayerControl);
	static CPlayerControl * GetPlayerControl(void) { return m_pPlayerControl; };
	static void SetPlayerNumber(const int nNumber);							// �v���C���[�l���Z�b�^�[
	static int	GetPlayerNumber(void) { return m_nPlayerNumber; }			// �v���C���[�l���Q�b�^�[
	static CFade* GetFade(void) { return m_pFade; }   // �t�F�[�h�̎擾// �v���C���[�l���Q�b�^�[
	static void SetResultScore(int nPlayer, int nScore);
	static int GetResultScore(int nPlayer) { return m_nResultScore[nPlayer]; };
private:
	static CRenderer * m_pRenderer;
	static CKeyboard * m_pKeyboard;
	static CJoystick * m_pJoystick;
	static CMouse *	m_pMouse;
	static CSound * m_pSound;
	static CCamera *m_pCamera;
	static CLight *m_pLight;
	static CPlayer * m_pPlayer;
	static MODE m_mode;
	static CGame * m_pGame;
	static CResult* m_pResult;
	static CTitle * m_pTitle;
	static CTutorial * m_pTutorial;
	static CSelect * m_pSelect;
	static CMapManager * m_pMapManager;
	static HWND m_hWnd;
	static CResource* m_pResource;				// ���\�[�X�|�C���^
	static CScore * m_apScore[MAX_PLAYER];		// �v���C���[�X�R�A
	static CPlayerControl * m_pPlayerControl;	// �v���C���[�Ǘ��̃|�C���^
	static int m_nPlayerNumber;					// �v���C���[�̐l��
	static CFade* m_pFade;						// �t�F�[�h�̃|�C���^
	static int m_nResultScore[MAX_PLAYER];		// �ŏI�X�R�A
};
#endif