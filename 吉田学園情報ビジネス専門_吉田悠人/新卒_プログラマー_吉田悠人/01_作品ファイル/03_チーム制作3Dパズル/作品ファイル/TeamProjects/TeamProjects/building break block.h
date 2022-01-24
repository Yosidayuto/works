//=============================================================================
//
// ビル（半壊）ブロック [building break block.h]
// Author : 吉田悠人
//
//=============================================================================
#ifndef _BUILDING_BREAK_BLOCK_H_
#define _BUILDING_BREAK_BLOCK_H_
//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "hindrance block base.h"

//=============================================================================
// クラス定義
//=============================================================================
class CBuildingBreakBlock : public CHindranceBlockBase
{
public:
	CBuildingBreakBlock();
	~CBuildingBreakBlock();
	static CBuildingBreakBlock*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);

private:
	const int	 m_nModel = 51;				// モデル番号

};
#endif