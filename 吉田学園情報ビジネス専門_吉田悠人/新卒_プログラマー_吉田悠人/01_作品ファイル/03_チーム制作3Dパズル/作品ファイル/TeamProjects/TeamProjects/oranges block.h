//=============================================================================
//
// �~�J���u���b�N [oranges block.h]
// Author : �g�c�I�l
//
//=============================================================================
#ifndef _ORANGES_BLOCK_H_
#define _ORANGES_BLOCK_H_
//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "item block base.h"

//=============================================================================
// �N���X��`
//=============================================================================
class COrangesBlock : public CItemBlockBase
{
public:
	COrangesBlock();
	~COrangesBlock();
	static COrangesBlock*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);

private:
	const int					m_nModel = 43;	// ���f���ԍ�

};
#endif