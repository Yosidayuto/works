//=============================================================================
//
// ビルブロック [building block.h]
// Author : 吉田悠人
//
//=============================================================================
#ifndef _BUILDING_BLOCK_H_
#define _BUILDING_BLOCK_H_
//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "hindrance block base.h"

//=============================================================================
// クラス定義
//=============================================================================
class CBuildingBlock : public CHindranceBlockBase
{
public:
	CBuildingBlock();
	~CBuildingBlock();
	static CBuildingBlock*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);

private:
	const int	 m_nModel = 50;					// モデル番号

};
#endif