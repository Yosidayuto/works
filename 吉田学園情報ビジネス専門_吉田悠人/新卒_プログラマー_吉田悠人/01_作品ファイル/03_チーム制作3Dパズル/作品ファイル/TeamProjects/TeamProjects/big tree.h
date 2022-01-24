//=============================================================================
//
// 針葉樹（高い） [big tree.h]
// Author : 吉田悠人
//
//=============================================================================
#ifndef _BIG_TREE_H_
#define _BIG_TREE_H_
//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "hindrance block base.h"

//=============================================================================
// クラス定義
//=============================================================================
class CBigTree : public CHindranceBlockBase
{
public:
	CBigTree();
	~CBigTree();
	static CBigTree*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);

private:
	const int	 m_nModel = 52;				// モデル番号

};
#endif