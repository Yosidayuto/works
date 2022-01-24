//=============================================================================
//
// 荷物ブロック [luggage block.h]
// Author : 吉田悠人
//
//=============================================================================
#ifndef _LUGGSGE_BLOCK_H_
#define _LUGGSGE_BLOCK_H_
//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "goal block base.h"

//=============================================================================
// クラス定義
//=============================================================================
class CLuggageBlock : public CGoalBlockBase
{
public:
	CLuggageBlock();
	~CLuggageBlock();
	static CLuggageBlock*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, CGame::MAP_TYPE MapType ,bool Goal = true);

private:
	bool		bGoal;			//ゴールとして機能するか
	const int	m_nModel = 22;	// モデル番号

};
#endif