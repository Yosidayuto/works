//=============================================================================
//
//	チュートリアル [tutorial.h]
//	Author : 鈴木　聖大
//
//=============================================================================

//二重インクルード防止
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

//====================================
//インクルード
//====================================
#include "main.h"
#include "ui.h"

//====================================
// クラス定義
//====================================

//UIクラス
class CTutorial : public CUi
{
public:
	CTutorial(int nPriorit = PRIORITY_UI_0);
	static CTutorial *Create(void);

	HRESULT Init(void);
	void Update(void);
	void TutorialUninit(void);
private:
	CObject2D* m_pObject2d;
	const int m_nTexture = 30;			// テクスチャ番号

};
#endif // !_UI_H_