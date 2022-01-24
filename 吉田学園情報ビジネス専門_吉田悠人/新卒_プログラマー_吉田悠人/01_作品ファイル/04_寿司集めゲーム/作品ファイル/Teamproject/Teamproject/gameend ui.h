//=============================================================================
//
// �������Ԓʒm�̏��� [gameend ui.h]
// Author : �ѐ�ї���
//
//=============================================================================
#ifndef _GAME_END_UI_H_
#define _GAME_END_UI_H_

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
class CGameEndUi : public CScene2d
{
public:
	CGameEndUi(int nPriority = 8);
	~CGameEndUi();
	static CGameEndUi *Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size);
	static CGameEndUi *Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Move, D3DXVECTOR3 Size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	D3DXVECTOR3				m_move;			//�ړ���
	int                     m_nPatternAnim;	//�A�j���[�V�����p�^�[��
	int                     m_nCountAnim;	//�A�j���[�V�����p�^�[��
	int                     m_nTexture = 59;//�e�N�X�`���ԍ�
};
#endif // !_MAP_H_


