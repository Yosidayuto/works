//=============================================================================
//
//	レーザーボタン[laser button.h]
//	Author:吉田　悠人
//
//=============================================================================

#ifndef _LASER_BUTTON_H_
#define _LASER_BUTTON_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "button.h"
#include "player.h"

//=============================================================================
// クラス定義
//=============================================================================
class CLaserButton :public CButton
{
public:

	CLaserButton(int nPriorit = PRIORITY_UI_1);	//コンストラクタ
	static HRESULT			Load(void);
	static void				Unload(void);
	static CLaserButton*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);


	HRESULT			Init(void);		// 初期化処理
	void			MouseOver(void);// マウスオーバー判定
	void			Push(void);		// プッシュ判定処理
private:
	static TEXTURE_DATA	m_TextureData;	// テクスチャデータ
};
#endif
