//=============================================================================
//
//	ライフテロップ[telop life.h]
//	Author:吉田　悠人
//
//=============================================================================
#ifndef  _TELOP_LIFE_H
#define  _TELOP_LIFE_H
//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "scene2d.h"
//=============================================================================
// 前方宣言
//=============================================================================
//=============================================================================
// クラス定義
//=============================================================================
class CTelopLife :public CScene2d
{
public:
	CTelopLife(int nPriorit = PRIORITY_UI_1);	// コンストラクタ

	static HRESULT		Load(void);
	static void			Unload(void);
	static CTelopLife*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

private:
	static TEXTURE_DATA	m_TextureData;	// テクスチャデータ

};
#endif