//====================================================
//
// titletransition_tileヘッダ [titletransition_tile.h]
// Author : 伊藤陽梧
//
//====================================================

//二重インクルード防止
#ifndef _TITLETRANSITION_TILE_H_
#define _TITLETRANSITION_TILE_H_

//====================================================
// インクルード
//====================================================
#include "tile.h"

//====================================================
//前方宣言
//====================================================
class CScene3d;

//====================================================
// クラス定義
//====================================================

// ダミータイルクラス
class CTitleTransitionTile : public CTile
{
public:
	//============
	// メンバ関数
	//===========
	CTitleTransitionTile();
	~CTitleTransitionTile();

	static void Create(D3DXVECTOR3 pos, D3DXCOLOR col = TILE_DEFAULT_COLOR);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
private:

	//============
	// メンバ変数
	//===========
	int m_nPlayerCount;			// プレイヤーのカウント用
};

#endif