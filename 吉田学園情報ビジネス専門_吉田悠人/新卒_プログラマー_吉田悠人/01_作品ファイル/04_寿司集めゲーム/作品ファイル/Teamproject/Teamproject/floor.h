//=============================================================================
//
// 床処理 [floor.h]
// Author : 林川紗梨夏
//
//=============================================================================
#ifndef _FLOOR_H_
#define _FLOOR_H_

#include "scene3d.h"
#include "polygon3d.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define TEXTURE_FLOOR		"Data/TEXTURE/FLOOR/bg001.png"

//=============================================================================
//クラス定義
//=============================================================================
class CFloor : public CPolygon3d
{
public:
	CFloor(int nPriority = 3);
	~CFloor();

	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_BLOCK_001,
		TYPE_MAX,
	}TYPE;

	static CFloor * Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size);
	HRESULT			Init(void);

private:
	int							m_nPatternAnim;			// アニメーションパターン
	int							m_nCountAnim;			// アニメーションパターン
	const int					m_nTexture = 1;			// テクスチャ番号
};
#endif


