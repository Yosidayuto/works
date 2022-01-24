//=============================================================================
//
// 穴ブロック [hole block.h]
// Author : 吉田悠人
//
//=============================================================================
#ifndef _HOLE_BLOCK_H_
#define _HOLE_BLOCK_H_
//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "model.h"
#include "goal block base.h"

//=============================================================================
// クラス定義
//=============================================================================
class CHoleBlock : public CGoalBlockBase
{
public:
	CHoleBlock();
	~CHoleBlock();
	static CHoleBlock*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, CGame::MAP_TYPE MapType);
	void	Update(void);
	void	Goal(void);		// ゴール処理

private:
	const int	 m_nModel = 20;				// モデル番号

};
#endif