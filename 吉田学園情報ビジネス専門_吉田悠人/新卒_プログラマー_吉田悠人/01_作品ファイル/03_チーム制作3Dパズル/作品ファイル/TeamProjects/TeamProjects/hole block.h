//=============================================================================
//
// ���u���b�N [hole block.h]
// Author : �g�c�I�l
//
//=============================================================================
#ifndef _HOLE_BLOCK_H_
#define _HOLE_BLOCK_H_
//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "model.h"
#include "goal block base.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CHoleBlock : public CGoalBlockBase
{
public:
	CHoleBlock();
	~CHoleBlock();
	static CHoleBlock*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, CGame::MAP_TYPE MapType);
	void	Update(void);
	void	Goal(void);		// �S�[������

private:
	const int	 m_nModel = 20;				// ���f���ԍ�

};
#endif