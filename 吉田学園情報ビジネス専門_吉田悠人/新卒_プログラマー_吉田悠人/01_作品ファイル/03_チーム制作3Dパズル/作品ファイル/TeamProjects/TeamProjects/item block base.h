//=============================================================================
//
// アイテム（つかめる）ブロックベース [item block base.h]
// Author : 吉田悠人
//
//=============================================================================
#ifndef _ITEM_BLOCK_BASE_H_
#define _ITEM_BLOCK_BASE_H_

//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "block base.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define ITEM_HEIGHT (25.0f)	//アイテムブロックの高さ

//=============================================================================
// クラス定義
//=============================================================================
class CItemBlockBase : public CBlockBase
{
public:
	CItemBlockBase();
	~CItemBlockBase();
	HRESULT Init(void);
private:

};
#endif