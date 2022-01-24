//=============================================================================
//
// ミッション処理[mission.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _MISSION_H_
#define _MISSION_H_
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "object2d.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CMission :public CObject2D
{
public:
	CMission();
	~CMission();
	static HRESULT Load(void);
	static void Unload(void);
	static CMission * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		// テクスチャへのポインタ
	D3DXVECTOR3				m_pos;					// ポリゴンの位置
	D3DXVECTOR3				m_size;
	D3DCOLOR				m_col;
	D3DXVECTOR2 m_texpos[NUM_VERTEX];
};
#endif