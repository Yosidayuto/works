//=============================================================================
//
// �������Ԃ̏��� [timer.h]
// Author : �V����s
//
//=============================================================================
#ifndef _TIMER_H_
#define _TIMER_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene.h"

//================================================
// �O���錾
//================================================
class CNumber;

//=============================================================================
//�}�N����`
//=============================================================================
#define MAX_MINUTES_DIGIT 1	//���̌���
#define MAX_SECONDS_DIGIT 2 //�b�̌���

#define MOOD1_SECONDS 00	//2�����[�h�J�n�b��
#define MOOD1_MINUTES 2		//2�����[�h�J�n��
		
#define MOOD2_SECONDS 30	//30�b���[�h�J�n�b��
#define MOOD2_MINUTES 00	//30�b���[�h�J�n��

// �^�C�}�[�̈ʒu�ƃT�C�Y
#define TIMER_POS D3DXVECTOR3(SCREEN_WIDTH / 2 - 40.0f,50.0f,0.0f)
#define TIMER_SIZE D3DXVECTOR3(40.0f,50.0f,0.0f)
#define TIMER_POSBG D3DXVECTOR3(SCREEN_WIDTH / 2,50.0f,0.0f)
#define TIMERBG_SIZE D3DXVECTOR3(120.0f,50.0f,0.0f)

//=============================================================================
// �N���X��`
//=============================================================================
class CTimer :public CScene
{
public:
	CTimer(int nPriority = 9);
	~CTimer();

	static CTimer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int Min,int Sec);
	HRESULT Init(void);
	void Update(void);
	void Uninit(void);
	void Draw(void);

	//�Q�b�^�[
	bool GetTimeUp(void) { return m_bTimeUp; }	//���Ԑ؂ꏊ���֐�
	//�Z�b�^�[
	void SetTimer(int Min, int Sec);	//�������Ԃ̐ݒ�
	int GetTime(void);//���Ԏ擾
private:
	bool m_bTimeUp;
	CNumber *m_pMINUtes;						//���̃|�C���^�[
	CNumber *m_pSexonds[MAX_SECONDS_DIGIT];		//�b�̃|�C���^�[
	int m_nSeconds;								//���J�E���g
	int m_nMinutes;								//�b�J�E���g
	int m_nCountF;								//�t���[���J�E���g
	D3DXVECTOR3  m_Pos;							//�ʒu
	D3DXVECTOR3  m_Size;						//�傫��
};


#endif