//=============================================================================
//
// �ו��u���b�N [luggage block.h]
// Author : �g�c�I�l
//
//=============================================================================
#ifndef _LUGGSGE_BLOCK_H_
#define _LUGGSGE_BLOCK_H_
//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "goal block base.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CLuggageBlock : public CGoalBlockBase
{
public:
	CLuggageBlock();
	~CLuggageBlock();
	static CLuggageBlock*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, CGame::MAP_TYPE MapType ,bool Goal = true);

private:
	bool		bGoal;			//�S�[���Ƃ��ċ@�\���邩
	const int	m_nModel = 22;	// ���f���ԍ�

};
#endif