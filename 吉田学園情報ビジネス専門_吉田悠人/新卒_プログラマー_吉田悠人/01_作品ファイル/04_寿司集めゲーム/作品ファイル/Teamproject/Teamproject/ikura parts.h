//=============================================================================
//
// ���i�@�C�N���p�[�c [ikura parts.h]
// Author : �g�c�I�l
//
//=============================================================================
#ifndef _IKURA_PARTS_H_
#define _IKURA_PARTS_H_
//=============================================================================
// �w�b�_�[�t�@�C��
//=============================================================================
#include "model.h"
#include "player parts.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CIkuraParts :public CPlayerParts
{
public:
	CIkuraParts();

	static CIkuraParts* Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, D3DXVECTOR3 Size, CScene3d* pParent);


private:
	const int m_nTexture = 11;		// �e�N�X�`���ԍ�
};

#endif