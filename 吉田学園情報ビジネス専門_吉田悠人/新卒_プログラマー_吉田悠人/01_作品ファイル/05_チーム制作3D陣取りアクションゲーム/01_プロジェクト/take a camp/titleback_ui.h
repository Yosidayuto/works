//====================================================
//
// titleback_uiヘッダ [titleback_ui.h]
// Author : 伊藤陽梧
//
//====================================================

//二重インクルード防止
#ifndef _TITLEBACK_UI_H_
#define _TITLEBACK_UI_H_

//*****************************
//インクルード
//*****************************
#include "main.h"
#include "scene.h"

//*****************************
// 前方宣言
//*****************************
class CPolygon;

//*****************************
//クラス定義
//*****************************

//チュートリアルクラス
class CTitlebackui : public CScene
{
public:
	//============
	// メンバ関数
	//===========
	CTitlebackui();
	~CTitlebackui();
	static CTitlebackui *Create(void); // クラス生成

	HRESULT Init(void); // 初期化
	void Uninit(void);  // 終了
	void Update(void);  // 更新
	void Draw(void);    // 描画

private:
	//============
	// メンバ関数
	//===========

	//============
	// メンバ変数
	//===========
	CPolygon *m_pTitlebackTex;	// タイトル戻る用のポリゴンのポインタ
	float m_fAlpha;
	bool m_bAlphaChange;
};
#endif