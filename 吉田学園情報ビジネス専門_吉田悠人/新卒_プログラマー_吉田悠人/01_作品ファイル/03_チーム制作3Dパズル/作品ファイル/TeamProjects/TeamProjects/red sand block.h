//=============================================================================
//
// �ԍ��u���b�N [red sand block.h]
// Author : �g�c�I�l
//
//=============================================================================
#ifndef _RED_SAND_BLOCK_H_
#define _RED_SAND_BLOCK_H_
//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "tile block base.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CRedSandBlock : public CTileBlockBase
{
public:
	CRedSandBlock();
	~CRedSandBlock();
	static CRedSandBlock*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);

private:
	const int					m_nModel = 10;	// ���f���ԍ�

};
#endif