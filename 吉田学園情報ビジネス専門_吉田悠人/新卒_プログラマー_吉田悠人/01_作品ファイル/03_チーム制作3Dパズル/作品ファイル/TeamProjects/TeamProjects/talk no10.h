//=============================================================================
//
//	セリフNo.10[talk no10.h]
//	Author:吉田 悠人
//
//=============================================================================

// 二重インクルード防止
#ifndef _TALK_NO10_H_
#define _TALK_NO10_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "talk_base.h"

//=============================================================================
// クラス定義
//=============================================================================
class CTalkNo10 :public CTalkbase
{
public:
	CTalkNo10(int nPriorit = PRIORITY_UI_0);	// コンストラクタ
	static CTalkNo10* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT		Init(void);				// 初期化処理
	void		Talk(void);				// トークを進める関数

protected:
	const int m_nTexture = 19;			// テクスチャ番号

};
#endif
