//=============================================================================
//
// �r���i����j�u���b�N [building break block.h]
// Author : �g�c�I�l
//
//=============================================================================
#ifndef _BUILDING_BREAK_BLOCK_H_
#define _BUILDING_BREAK_BLOCK_H_
//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "hindrance block base.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CBuildingBreakBlock : public CHindranceBlockBase
{
public:
	CBuildingBreakBlock();
	~CBuildingBreakBlock();
	static CBuildingBreakBlock*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);

private:
	const int	 m_nModel = 51;				// ���f���ԍ�

};
#endif