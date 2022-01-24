//=============================================================================
//
//	マウス処理[input mouse.h]
//	Author:吉田　悠人
//
//=============================================================================

#ifndef _INPUTMOUSE_H_
#define _INPUTMOUSE_H_

#define NUM_CLICK_MAX (3)						//キーの最大数

//=============================================================================
//フラグ
//=============================================================================
#define MOUSE_POS_TYPE
#undef MOUSE_POS_TYPE

//=============================================================================
// インクルードファイル
//=============================================================================
#include"main.h"
#include "input.h"
//=============================================================================
//前方宣言
//=============================================================================
typedef enum	//クリック種類
{
	CLICK_LEFT = 0,	//左クリック
	CLICK_RIGHT,	//右クリック
	CLICK_WHEEL,	//マウスホイール
	CLICK_MAX
}CLICK_TYPE;

//=============================================================================
// クラス定義
//=============================================================================
class CInihMouse :public CInput
{
public:
	CInihMouse();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void	Update(void);
#ifdef  MOUSE_POS_TYPE
	DIMOUSESTATE GetMousePos(void);
#else 
	POINT	GetMousePos(void);
#endif

	bool	GetClick(int nClick);			// クリック処理
	bool	GetClickTrigger(int nClick);	// クリックトリガー処理
	bool	GetClickRelease(int nClick);	// クリックリリース処理
private:
	DIMOUSESTATE m_aClickState;		//マウスの入力情報ワーク
	DIMOUSESTATE m_aClickTrigger;	//マウスのトリガー情報
	DIMOUSESTATE m_aClickRelease;	//マウスのリリース情報
#ifdef  MOUSE_POS_TYPE
	DIMOUSESTATE m_aMousePos;		//マウスの移動量
#else 
	POINT	posMouse;				//マウスの座標
	HWND	hPointerpos;			//ウィンドウのマウスポインターの座標
#endif



};



#endif