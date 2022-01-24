//=============================================================================
//
// プレイヤー現在位置の処理 [locationpoint.h]
// Author : 林川紗梨夏
//
//=============================================================================
#ifndef _LOCATION_POINT_H_
#define _LOCATION_POINT_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene2d.h"
class CLocationPoint : public CScene2d
{
public:
	CLocationPoint(int nPriority = 8);
	~CLocationPoint();

	static CLocationPoint *Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size,int number);
	HRESULT Init(void);
	void Update(void);
private:
	int                     m_nPatternAnim; //アニメーションパターン
	int                     m_nCountAnim; //アニメーションパターン
	int                     m_nPlayerNum;//プレイヤー番号
	const int               m_nTexture = 22;//テクスチャ番号
};
#endif // !_LOCATION_POINT_H_


