//=====================================================================
//
//	�J�������� [camera.h]
//	Author  �ѐ�ї���
//
//=====================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"
//======================================================
//�}�N����`
//======================================================
#define CAMERA_VIEW_RANGE (500.0f)
#define CAMERA_DISTANCE_FROM_PLAYER (100.0f)
#define CAMERA_DISTANCE_FROM_PLAYER_STAND (200.0f)
#define PLAYER_CAMERA_HEIGHT (20.0f) //�v���C���[�̍���

//======================================================
//�N���X��`
//======================================================
class CCamera
{
public:
	CCamera();
	~CCamera();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(void);					// �J�����ɂ��`��
	void SetCamera(int nCamera);			// �J�����ɂ�镪���`��

	bool SetUpViewport(int screen_id);		// �r���[�|�[�g(����)�ݒ�
	bool SetUpViewport(void);				// �r���[�|�[�g(�P��)�ݒ�

	D3DXVECTOR3 GetRot(void);
	void SetRot(D3DXVECTOR3 rot);
	void SetPos(int nCamera, D3DXVECTOR3 pos);
	//static void LoadScriptCamera(void);
	//void PlayerFlattery(void);		//�v���C���[�Ǐ]

#ifdef _DEBUG
	void		Move(void);			// �ړ�����
#endif
private:
	typedef struct 		//�����J����
	{
		float Width;	// �ʒu
		float Height;	// �����_
	}WindowSize;

	WindowSize m_WidowSize;
	void SetCameraView(D3DXVECTOR3 posV, D3DXVECTOR3 posR, float fInterpolation);
	D3DXVECTOR3 m_posV[MAX_PLAYER];            // �J�����̍��W
	D3DXVECTOR3 m_posR[MAX_PLAYER];            // �����_�̍��W
	D3DXVECTOR3 m_vecU;            // �J�����̏����
	D3DXMATRIX m_mtxProjection;    // �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;          // �r���[�}�g���b�N�X
	D3DXVECTOR3 m_RotateCenter;    // �J�����̉�]���S���W
	float m_fDistance;             // ���_-���ӓ_�̋���
	D3DXVECTOR3 m_pos[MAX_PLAYER];	// �ʒu
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_posVDest;         // �J�����̍��W(��)
	D3DXVECTOR3 m_posRDest;         // �����_�̍��W(��)
	bool m_bIsFollowPlayer;			// �v���C���[�ɒǏ]���邩
	float m_fInterpolation;			// �J������ԃX�s�[�h
	static D3DXVECTOR2 m_offset[MAX_PLAYER];//��ʂ̈ʒu

#ifdef _DEBUG						   
	float		m_fMoveRot;			// �ړ��������
	bool		m_bDebug;			// �f�o�b�N���
#endif
};

#endif
