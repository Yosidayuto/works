//=============================================================================
//
// �W���C�X�e�B�b�N���� [joystick.h]
// Author : �ѐ�ї���
//
//=============================================================================
#ifndef _JOYSTICK_H_
#define _JOYSTICK_H_
//*****************************************************************************
// �w�b�_�[�t�@�C��
//*****************************************************************************
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define JS_X	   (0)
#define JS_Y	   (1)
#define JS_A	   (2)
#define JS_B	   (3)
#define JS_LB	   (4)
#define JS_RB	   (5)
#define JS_LT	   (6)
#define JS_RT	   (7)
#define JS_LP	   (8)
#define JS_RP	   (9)
#define JS_BACK	   (10)
#define JS_START   (11)
#define JS_HOME    (12)
#define	NUM_JS_MAX (256)

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CJoystick : public CInput
{
public:
	CJoystick();
	~CJoystick();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetJoystickPress(int nKey, int nJoystick);
	bool GetJoystickTrigger(int nKey, int nJoystick);
	bool GetJoystickRelease(int nKey, int nJoystick);
	DIJOYSTATE	GetJoyStick(int nJoystick);
	BOOL CreateEffect(HWND hWnd, int nJoystick);
	static BOOL CALLBACK EnumFFDevicesCallback(const DIDEVICEINSTANCE * pdidInstance, VOID * pContext);
	static BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE *pdidInstance, VOID *pContext);
	static BOOL CALLBACK EnumAxesCallback(const DIDEVICEOBJECTINSTANCE *pdidoi, VOID *pContext);
	static LPDIRECTINPUTDEVICE8 GetDevice(int nJoystick) { return m_pJDevice[nJoystick]; }
	static LPDIRECTINPUTEFFECT GetEffect(int nJoystick) { return m_IpDIEffect[nJoystick]; }

private:
	static LPDIRECTINPUTDEVICE8 m_pJDevice[MAX_PLAYER];		//�f�o�C�X
	static LPDIRECTINPUTEFFECT m_IpDIEffect[MAX_PLAYER];	//�G�t�F�N�g
	static DIDEVCAPS	m_diDevCaps;					//Caps
	DWORD m_dwNumForceFeedbackAxis;				//�t�H�[�X�t�B�[�h�o�b�N
	DWORD m_rgdwAxes[2] = { DIJOFS_X , DIJOFS_Y };
	LONG  m_rglDirection[2] = { 1 , 1 };
	DICONSTANTFORCE cf;
	DIEFFECT        eff;
	BYTE m_aJoyState[NUM_JS_MAX][MAX_PLAYER];				// �W���C�X�e�B�b�N�̓��͏�񃏁[�N
	BYTE m_aJoyStateTrigger[NUM_JS_MAX][MAX_PLAYER];		// �W���C�X�e�B�b�N�g���K�[���
	BYTE m_aJoyStateRelease[NUM_JS_MAX][MAX_PLAYER];		// �W���C�X�e�B�b�N�����[�X���

};
#endif