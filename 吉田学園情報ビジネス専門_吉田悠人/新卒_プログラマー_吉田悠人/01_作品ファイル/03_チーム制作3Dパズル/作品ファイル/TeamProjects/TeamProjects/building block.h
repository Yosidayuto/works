//=============================================================================
//
// �r���u���b�N [building block.h]
// Author : �g�c�I�l
//
//=============================================================================
#ifndef _BUILDING_BLOCK_H_
#define _BUILDING_BLOCK_H_
//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "hindrance block base.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CBuildingBlock : public CHindranceBlockBase
{
public:
	CBuildingBlock();
	~CBuildingBlock();
	static CBuildingBlock*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);

private:
	const int	 m_nModel = 50;					// ���f���ԍ�

};
#endif