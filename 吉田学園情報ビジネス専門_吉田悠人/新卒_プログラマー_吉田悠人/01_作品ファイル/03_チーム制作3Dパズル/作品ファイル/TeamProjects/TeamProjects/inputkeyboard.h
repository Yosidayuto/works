//=============================================================================
//
// キーボード入力処理 [inputkeyboard.h]
// Author : 吉田悠人
//
//=============================================================================
#ifndef _INPUTKEYBOARD_H_
#define _INPUTKEYBOARD_H_
//=============================================================================
// インクルードファイル
//=============================================================================
#include "input.h"
#include "main.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define NUM_KEY_MAX (256)    //キーボードの最大数

//=============================================================================
// クラス定義
//=============================================================================
class CInputKeyboard : public CInput
{
public:
    CInputKeyboard();	// コンストラクタ
	~CInputKeyboard();	// デストラクタ
    HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// 初期化処理
    void	Uninit(void);							// 終了終了処理
    void	Update(void);							// 更新処理

    bool GetKeyPress(int nkey);						// キー入力状況取得
    bool GetKeyTrigger(int nkey);					// トリガーキー入力状況取得
    bool GetKeyRelease(int nkey);					// リリースキー入力状況取得

private:
    BYTE m_aState[NUM_KEY_MAX];			// キー入力保存
    BYTE m_aStateTrigger[NUM_KEY_MAX];	// トリガーキー入力保存
    BYTE m_aStateRelease[NUM_KEY_MAX];	// リリースキー入力保存

};

#endif
