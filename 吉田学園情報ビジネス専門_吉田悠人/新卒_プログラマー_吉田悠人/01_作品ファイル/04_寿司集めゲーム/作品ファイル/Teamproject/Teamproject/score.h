//=============================================================================
//
// �X�R�A���� [score.h]
// Author : �ѐ�ї���
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "number.h"
#include "scene2d.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_DIGITS (5) //�ő包��
#define SCORE_SIZE_WIDTH (60.0f)
#define SCORE_SIZE_HEIGHT (100.0f)
#define SCORE_POS (D3DXVECTOR3(SCREEN_WIDTH / 2 + SCORE_SIZE_WIDTH,80.0f,0.0f))
#define SCORE_SIZE (D3DXVECTOR3(50.0f,80.0f,0.0f))
//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CScore : public CScene
{
public:

	CScore(int nPriority = 8);
	~CScore();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CScore * Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size);
	void SetScore(int nScore);
	void AddScore(int nValue);
	int GetScore(void) { return m_nScore; }

private:
	CNumber                           *m_apNumber[MAX_DIGITS];//�i���o�[�i�ő包�����j
	D3DXVECTOR3                        m_Pos;
	D3DXVECTOR3                        m_Size;
	int                                m_nScore; //�X�R�A�̐��l
};
#endif // !_SCORE_H_
