//=============================================================================
//
// �S�~�u���b�N [garbage block.h]
// Author : �g�c�I�l
//
//=============================================================================
#ifndef _GARBAGE_BLOCK_H_
#define _GARBAGE_BLOCK_H_
//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "item block base.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CGarbageBlock : public CItemBlockBase
{
public:
	CGarbageBlock();
	~CGarbageBlock();
	static CGarbageBlock*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);

private:
	const int					m_nModel = 40;	// ���f���ԍ�

};
#endif