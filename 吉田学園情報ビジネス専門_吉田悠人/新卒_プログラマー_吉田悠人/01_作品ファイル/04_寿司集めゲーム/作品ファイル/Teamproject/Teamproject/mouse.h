//=============================================================================
//
//	マウス入力処理[mouse.h]
//	Author:吉田悠人
//
//=============================================================================

#ifndef _INPUTMOUSE_H_
#define _INPUTMOUSE_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "input.h"
#include "main.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define NUM_CLICK_MAX (3)						//キーの最大数
#define MOUSE_POS_TYPE							//マウスの移動量の処理変換

//=============================================================================
// クラス
//=============================================================================
class CMouse :public CInput
{
public:
	CMouse();
	~CMouse();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Update(void);
	bool GetClick(int nClick);
	bool GetClickTrigger(int nClick);
	bool GetClickRelease(int nClick);

	DIMOUSESTATE	GetMouseMove(void);
	POINT			GetMousePos(void);

private:
	DIMOUSESTATE	m_aClickState;			//マウスの入力情報ワーク
	DIMOUSESTATE	m_aClickTrigger;		//マウスのトリガー情報
	DIMOUSESTATE	m_aClickRelease;		//マウスのリリース情報

	DIMOUSESTATE	m_aMouseMove;			//マウスの移動量
	POINT			m_aMousePos;			//マウスの座標
	HWND			m_hPointerpos;			//ウィンドウのマウスポインターの座標

};


#endif