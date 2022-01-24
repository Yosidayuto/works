//=============================================================================
//
//	ボタン[button.h]
//	Author:吉田　悠人
//
//=============================================================================

#ifndef _BUTTONP_H_
#define _BUTTONP_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "inputmouse.h"
#include "scene2d.h"

//=============================================================================
//前方宣言
//=============================================================================
typedef enum  //ボタンテクスチャ種類
{
	BUTTON_STATE_NORMAL =0,
	BUTTON_STATE_PUSH,
	BUTTON_STATE_MAX
}BUTTON_STATE;

//=============================================================================
// クラス定義
//=============================================================================
class CButton :public CScene2d
{
public:

	CButton(int nPriorit = PRIORITY_UI_0);	// コンストラクタ
	static HRESULT	Load(void);
	static void		Unload(void);

	HRESULT		Init(void);				// 初期化処理
	bool		Hit(void);				// 当たり判定
	
	virtual void MouseOver(void) = 0;	// マウスオーバー判定
	virtual void Push(void) = 0;		// プッシュ判定処理

private:
	static TEXTURE_DATA	m_TextureData[BUTTON_STATE_MAX];	//テクスチャデータ
	CScene2d*			m_pScene2d;					//オブジェクトポインタ
	
};
#endif
