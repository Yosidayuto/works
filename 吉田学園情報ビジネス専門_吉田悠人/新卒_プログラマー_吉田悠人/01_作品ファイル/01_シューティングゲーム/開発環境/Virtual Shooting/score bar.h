//=============================================================================
//
//	スコア背景[score bar.h]
//	Author:吉田　悠人
//
//=============================================================================
#ifndef _SCORE_BAR_H_
#define _SCORE_BAR_H_
//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "scene2d.h"

//=============================================================================
// クラス定義
//=============================================================================
class CScoreBar :public CScene2d
{
public:
	CScoreBar(int nPriorit= PRIORITY_SCENE);	//コンストラクタ

	static HRESULT			Load(void);
	static void				Unload(void);
	static CScoreBar*		Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

private:
	static TEXTURE_DATA	m_TextureData;	// テクスチャデータ
};
#endif
