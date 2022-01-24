//=============================================================================
//
// 制限時間背景の処理 [timerBg.h]
// Author : 齋藤大行
//
//=============================================================================
#ifndef _CTIMERBG_
#define _CTIMERBG_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "billboard.h"
#include "resource manager.h"
#include "manager.h"
#include "renderer.h"
#include "scene2d.h"
//================================================
// 前方宣言
//================================================


//=============================================================================
//マクロ定義
//=============================================================================


class CtimerBg :public CScene2d
{
public:
	CtimerBg(int nPriority = 8);
	~CtimerBg();

	static CtimerBg *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR Col);
	void Update(void);
	void Uninit(void);
	void Draw(void);


private:

	int							m_Alpha;		//透明度
	bool						m_bUse;			//使うか使わないか
	const int					m_nTexture = 23;// テクスチャ番号


};


#endif 