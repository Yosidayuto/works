//=============================================================================
//
// ���҃v���C���[ [winner player.h]
// Author : �g�c�I�l
//
//=============================================================================
#ifndef _WINNER_PLAYER_H_
#define _WINNER_PLAYER_H_

//=============================================================================
// �w�b�_�[�t�@�C��
//=============================================================================
#include "model.h"

//=============================================================================
//�N���X��`
//=============================================================================
class CWinnerPlayer : public CModel
{
public:
	CWinnerPlayer(int nPriority = 3);
	~CWinnerPlayer();
	static CWinnerPlayer* Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, D3DXVECTOR3 Size, int nModel);	//��������
	void			Update(void);
private:
};
#endif // !_PLAYER_H_


