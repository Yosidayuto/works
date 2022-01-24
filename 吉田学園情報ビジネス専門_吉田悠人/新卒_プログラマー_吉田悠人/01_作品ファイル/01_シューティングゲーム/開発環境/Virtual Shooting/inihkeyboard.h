//=============================================================================
//
// キーボード処理 [inihkeyboard.h]
// Author : 吉田悠人
//
//=============================================================================
#ifndef _INPUTKEYBOARD_H_
#define _INPUTKEYBOARD_H_
//=============================================================================
// インクルードファイル
//=============================================================================
#include"main.h"
#include"input.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define NUM_KEY_MAX (256)						//キーの最大数

//=============================================================================
// クラス定義
//=============================================================================
class CInihKeyboard :public CInput
{
public:
	CInihKeyboard();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void	Update(void);

	bool GetKeyPress(int nKey);			//プッシュゲッター
	bool GetKeyPressTrigger(int nKey);	//プッシュトリガーゲッター
	bool GetKeyPressRelease(int nKey);	//プッシュリリースゲッター
private:
	BYTE m_akeyState[NUM_KEY_MAX];					//キーボードの入力情報ワーク
	BYTE m_aKesStateTrigger[NUM_KEY_MAX];			//キーボードのトリガー情報
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];			//キーボードのリリース情報
};

#endif