//=============================================================================
//
// ���i�@���p�[�c [egg parts.h]
// Author : �g�c�I�l
//
//=============================================================================
#ifndef _EGG_PARTS_H_
#define _EGG_PARTS_H_
//=============================================================================
// �w�b�_�[�t�@�C��
//=============================================================================
#include "model.h"
#include "food base.h"
#include "player parts.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CEggParts :public CPlayerParts
{
public:
	CEggParts();

	static CEggParts* Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, D3DXVECTOR3 Size, CScene3d* pParent);


private:
	const int m_nTexture = 14;		// �e�N�X�`���ԍ�
};

#endif