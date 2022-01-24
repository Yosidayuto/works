//=============================================================================
//
// マップ端ポリゴン（エリア外側）処理 [MapEdgeOverlay.h]
// Author : 林川紗梨夏
//
//=============================================================================
#ifndef _MAP_EDGE_OVERLAY_H_
#define _MAP_EDGE_OVERLAY_H_

#include "scene3d.h"
#include "polygon3d.h"

//=============================================================================
// マクロ定義
//=============================================================================

//=============================================================================
//クラス定義
//=============================================================================
class CMapEdgeOverlay : public CPolygon3d
{
public:
	CMapEdgeOverlay(int nPriority = 3);
	~CMapEdgeOverlay();

	static CMapEdgeOverlay * Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	int							m_nPatternAnim;			// アニメーションパターン
	int							m_nCountAnim;			// アニメーションパターン
	const int					m_nTexture = 31;			// テクスチャ番号
};
#endif 


