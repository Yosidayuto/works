//=============================================================================
//
// �X�C�J�u���b�N [watermelon block.h]
// Author : �g�c�I�l
//
//=============================================================================
#ifndef _WATERMELON_BLOCK_H_
#define _WATERMELON_BLOCK_H_
//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "item block base.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CWatermelonBlock : public CItemBlockBase
{
public:
	CWatermelonBlock();
	~CWatermelonBlock();
	static CWatermelonBlock*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);

private:
	const int					m_nModel = 44;	// ���f���ԍ�

};
#endif