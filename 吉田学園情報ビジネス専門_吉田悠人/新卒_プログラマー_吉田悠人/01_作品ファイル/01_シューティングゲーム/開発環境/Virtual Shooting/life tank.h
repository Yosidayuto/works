//=============================================================================
//
//	ライフタンク[life tank.h]
//	Author:吉田　悠人
//
//=============================================================================

#ifndef _LIFE_ICON_H_
#define _LIFE_ICON_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "scene2d.h"

//=============================================================================
// クラス定義
//=============================================================================
class CLifeTank :public CScene2d
{
public:
	CLifeTank(int nPriorit = PRIORITY_UI_3);	//コンストラクタ

	static HRESULT		Load(void);
	static void			Unload(void);
	static CLifeTank*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT				Init(void);		// 初期化処理

private:
	static TEXTURE_DATA	m_TextureData;	// テクスチャデータ
};
#endif
