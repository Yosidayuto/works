//=============================================================================
//
// �v���C���[�̔ԍ�UI [player number.h]
// Author : �g�c�I�l
//
//=============================================================================
#ifndef _PLAYER_NUMBER_H_
#define _PLAYER_NUMBER_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene2d.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CPlayerNumber :public CScene2d
{
public:
	CPlayerNumber();
	~CPlayerNumber();

	static CPlayerNumber *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nNumber);

private:
	const int nPlayerNumberTexture[MAX_PLAYER] = { 52,53,54,55 };		//�e�N�X�`���ԍ�
};

#endif