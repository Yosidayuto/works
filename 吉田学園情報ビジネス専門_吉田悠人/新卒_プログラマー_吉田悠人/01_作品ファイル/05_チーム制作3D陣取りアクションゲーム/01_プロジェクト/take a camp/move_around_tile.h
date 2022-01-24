//=============================================================================
//
// 前後に動く床 ヘッダー [move_around_tile.h]
// Author : 吉田 悠人
//
//=============================================================================

//二重インクルード防止
#ifndef _MOVE_TILE_AROUND_H_
#define _MOVE_TILE_AROUND_H_

//*****************************
// インクルード
//*****************************
#include "move_tile.h"

//*****************************
//前方宣言
//*****************************
class CScene3d;

//*****************************
//マクロ定義
//*****************************

//*****************************
// クラス定義
//*****************************
class CAroundTile : public CMoveTile
{
public:

	//メンバ関数
	CAroundTile();
	~CAroundTile();

	static void	Create(D3DXVECTOR3 pos, D3DXCOLOR col = TILE_DEFAULT_COLOR);
	HRESULT		Init(void);
	void		Update(void);

	void		MoveRot(bool bReversal);
	void		TileCheck(void);

private:
	// メンバ変数
	CScene3d*	m_Texture;

};

#endif