//=============================================================================
//
// ���i�@�T�[�����p�[�c [salmon parts.h]
// Author : �g�c�I�l
//
//=============================================================================
#ifndef _SALMON_PARTS_H_
#define _SALMON_PARTS_H_
//=============================================================================
// �w�b�_�[�t�@�C��
//=============================================================================
#include "model.h"
#include "player parts.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CSalmonParts :public CPlayerParts
{
public:
	CSalmonParts();

	static CSalmonParts* Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, D3DXVECTOR3 Size, CScene3d* pParent);


private:
	const int m_nTexture = 13;		// �e�N�X�`���ԍ�
};

#endif