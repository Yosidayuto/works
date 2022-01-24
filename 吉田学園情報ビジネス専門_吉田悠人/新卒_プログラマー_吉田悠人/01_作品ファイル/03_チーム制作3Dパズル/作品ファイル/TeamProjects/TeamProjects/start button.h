//=============================================================================
//
//	スタートボタン[start button.h]
//	Author:吉田　悠人
//
//=============================================================================

#ifndef _START_BUTTONP_H_
#define _START_BUTTONP_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "button.h"

//=============================================================================
// クラス定義
//=============================================================================
class CStartButton :public CButton
{
public:
	CStartButton();						// コンストラクタ
	static CStartButton* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void				 Push(void);	// プッシュ判定処理

private:
	const int m_nTexture = 3;			// テクスチャ番号

};
#endif
