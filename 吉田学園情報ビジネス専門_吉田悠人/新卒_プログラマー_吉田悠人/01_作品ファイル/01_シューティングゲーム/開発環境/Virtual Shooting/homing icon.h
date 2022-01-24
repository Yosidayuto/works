//=============================================================================
//
//	ホーミングアイコン[homing icon.h]
//	Author:吉田　悠人
//
//=============================================================================

#ifndef _HOMING_ICON_H_
#define _HOMING_ICON_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "scene2d.h"

//=============================================================================
// クラス定義
//=============================================================================
class CHomingIcon :public CScene2d
{
public:
	CHomingIcon();	//コンストラクタ

	static HRESULT			Load(void);
	static void				Unload(void);
	static CHomingIcon*		Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

private:
	static TEXTURE_DATA	m_TextureData;	// テクスチャデータ
};
#endif
