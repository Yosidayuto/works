//=============================================================================
//
// マップ端ポリゴン（マスク側）処理 [MapEdgeMask.h]
// Author : 林川紗梨夏
//
//=============================================================================
#ifndef _MAP_EDGE_MASK_H_
#define _MAP_EDGE_MASK_H_

#include "scene3d.h"
#include "polygon3d.h"
//=============================================================================
// マクロ定義
//=============================================================================

//=============================================================================
//クラス定義
//=============================================================================
class CMapEdgeMask : public CPolygon3d
{
public:
	CMapEdgeMask(int nPriority = 3);
	~CMapEdgeMask();

	static CMapEdgeMask * Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	int							m_nPatternAnim;			// アニメーションパターン
	int							m_nCountAnim;			// アニメーションパターン
	const int					m_nTexture = 30;			// テクスチャ番号
};
#endif 


