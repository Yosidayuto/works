//=============================================================================
//
//	ウェポンUI[weapon ui.h]
//	Author:吉田　悠人
//
//=============================================================================

#ifndef _WEAPON_UI_H_
#define _WEAPON_UI_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "scene2d.h"
#include "player.h"

//=============================================================================
// クラス定義
//=============================================================================
class CWeaponUi :public CScene2d
{
public:

	CWeaponUi(int nPriorit = PRIORITY_UI_0);	// コンストラクタ

	static HRESULT		Load(void);
	static void			Unload(void);
	static CWeaponUi*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);


	//HRESULT		Init(void);		// 初期化処理
	//void		Uninit(void);	// 終了処理
	//void		Update(void);	// 更新処理
	//void		Draw(void);		// 描画処理
	
	WEAPON_TYPE GetIconType(void);				// タイプセッター
	void		TypeChange(WEAPON_TYPE Type);	// アイコンの切替　
private:
	static TEXTURE_DATA	m_TextureData;	// テクスチャデータ
	WEAPON_TYPE			m_IconType;		// アイコンタイプ
	CScene2d*			m_pWeaponIcon;	// アイコンポインタ
};
#endif
