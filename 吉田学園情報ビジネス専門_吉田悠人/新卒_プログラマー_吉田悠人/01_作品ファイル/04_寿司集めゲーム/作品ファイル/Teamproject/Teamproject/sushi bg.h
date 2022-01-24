//=============================================================================
//
// 床処理 [floor.h]
// Author : 林川紗梨夏
//
//=============================================================================
#ifndef _SUSHI_BG_H_
#define _SUSHI_BG_H_

#include "scene3d.h"
#include "polygon3d.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define TEXTURE_FLOOR		"Data/TEXTURE/FLOOR/bg001.png"

//=============================================================================
//クラス定義
//=============================================================================
class CSushiBg : public CPolygon3d
{
public:
	CSushiBg(int nPriority = 3);
	~CSushiBg();

	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_BLOCK_001,
		TYPE_MAX,
	}TYPE;

	static CSushiBg * Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size);
	HRESULT			Init(void);
	void			Update(void);

private:
	int							m_nPatternAnim;			// アニメーションパターン
	int							m_nCountAnim;			// アニメーションパターン
	const int					m_nTexture = 80;			// テクスチャ番号
};
#endif


