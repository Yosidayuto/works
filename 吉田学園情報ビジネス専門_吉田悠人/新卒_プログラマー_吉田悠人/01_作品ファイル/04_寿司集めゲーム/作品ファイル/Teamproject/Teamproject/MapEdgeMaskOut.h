//=============================================================================
//
// マップ端ポリゴン（マップ外のマスク側）処理 [MapEdgeMaskOut.h]
// Author : 林川紗梨夏
//
//=============================================================================
#ifndef _MAP_EDGE_MASK_OUT_H_
#define _MAP_EDGE_MASK_OUT_H_

#include "scene3d.h"
#include "polygon3d.h"
//=============================================================================
// マクロ定義
//=============================================================================

//=============================================================================
//クラス定義
//=============================================================================
class CMapEdgeMaskOut : public CPolygon3d
{
public:
	CMapEdgeMaskOut(int nPriority = 3);
	~CMapEdgeMaskOut();

	static CMapEdgeMaskOut * Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	int							m_nPatternAnim;			// アニメーションパターン
	int							m_nCountAnim;			// アニメーションパターン
	const int					m_nTexture = 32;			// テクスチャ番号
};
#endif 


