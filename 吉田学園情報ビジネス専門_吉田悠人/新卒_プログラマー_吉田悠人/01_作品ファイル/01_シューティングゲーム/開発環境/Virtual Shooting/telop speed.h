//=============================================================================
//
//	スピードテロップ[telop speed.h]
//	Author:吉田　悠人
//
//=============================================================================
#ifndef  _TELOP_SPEED_H
#define  _TELOP_SPEED_H
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
class CTelopSpeed :public CScene2d
{
public:
	CTelopSpeed(int nPriorit = PRIORITY_UI_1);	// コンストラクタ

	static HRESULT		Load(void);
	static void			Unload(void);
	static CTelopSpeed*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

private:
	static TEXTURE_DATA	m_TextureData;	// テクスチャデータ

};
#endif