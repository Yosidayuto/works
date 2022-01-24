//=============================================================================
//
//	バレットアイコン[bullet icon.h]
//	Author:吉田　悠人
//
//=============================================================================

#ifndef _BULLET_ICON_H_
#define _BULLET_ICON_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "scene2d.h"

//=============================================================================
// クラス定義
//=============================================================================
class CBulletIcon :public CScene2d
{
public:
	CBulletIcon();	//コンストラクタ

	static HRESULT			Load(void);
	static void				Unload(void);
	static CBulletIcon*		Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

private:
	static TEXTURE_DATA	m_TextureData;	// テクスチャデータ
};
#endif
