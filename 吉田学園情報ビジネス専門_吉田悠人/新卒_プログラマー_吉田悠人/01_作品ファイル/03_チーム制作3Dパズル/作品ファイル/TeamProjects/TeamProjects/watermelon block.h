//=============================================================================
//
// スイカブロック [watermelon block.h]
// Author : 吉田悠人
//
//=============================================================================
#ifndef _WATERMELON_BLOCK_H_
#define _WATERMELON_BLOCK_H_
//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "item block base.h"

//=============================================================================
// クラス定義
//=============================================================================
class CWatermelonBlock : public CItemBlockBase
{
public:
	CWatermelonBlock();
	~CWatermelonBlock();
	static CWatermelonBlock*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);

private:
	const int					m_nModel = 44;	// モデル番号

};
#endif