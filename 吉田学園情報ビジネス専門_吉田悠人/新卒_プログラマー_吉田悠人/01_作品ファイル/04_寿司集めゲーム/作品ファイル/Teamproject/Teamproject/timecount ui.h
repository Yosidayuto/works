//=============================================================================
//
// �������Ԓʒm�̏��� [timecount ui.h]
// Author : �ѐ�ї���
//
//=============================================================================
#ifndef _TIME_COUNT_UI_H_
#define _TIME_COUNT_UI_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene2d.h"


//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CTimecountUi : public CScene2d
{
public:
	CTimecountUi(int nPriority = 8);
	~CTimecountUi();
	static CTimecountUi *Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size);
	static CTimecountUi *Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Move, D3DXVECTOR3 Size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	D3DXVECTOR3				m_move;			//�ړ���
	int                     m_nPatternAnim;	//�A�j���[�V�����p�^�[��
	int                     m_nCountAnim;	//�A�j���[�V�����p�^�[��
	int                     m_nTexture = 58;//�e�N�X�`���ԍ�
};
#endif // !_MAP_H_


