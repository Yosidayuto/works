//=============================================================================
//
// 勝者プレイヤー [winner player.h]
// Author : 吉田悠人
//
//=============================================================================
#ifndef _WINNER_PLAYER_H_
#define _WINNER_PLAYER_H_

//=============================================================================
// ヘッダーファイル
//=============================================================================
#include "model.h"

//=============================================================================
//クラス定義
//=============================================================================
class CWinnerPlayer : public CModel
{
public:
	CWinnerPlayer(int nPriority = 3);
	~CWinnerPlayer();
	static CWinnerPlayer* Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, D3DXVECTOR3 Size, int nModel);	//生成処理
	void			Update(void);
private:
};
#endif // !_PLAYER_H_


