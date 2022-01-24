//=============================================================================
//
//	ライフボタン[life button.h]
//	Author:吉田　悠人
//
//=============================================================================

#ifndef _LIFE_BUTTON_H_
#define _LIFE_BUTTON_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "button.h"
#include "player.h"

//=============================================================================
//前方宣言
//=============================================================================
class CNumber;

//=============================================================================
// クラス定義
//=============================================================================
class CLifeButton :public CButton
{
public:

	CLifeButton(int nPriorit = PRIORITY_UI_1);	//コンストラクタ
	static HRESULT			Load(void);
	static void				Unload(void);
	static CLifeButton*		Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);


	HRESULT		Init(void);		// 初期化処理
	void		MouseOver(void);// マウスオーバー判定
	void		Push(void);		// プッシュ判定処理
	bool		LifeUp(void);	// ライフアップ処理
	bool		LifeDown(void);	// ライフダウン処理
private:
	static TEXTURE_DATA	m_TextureData;	// テクスチャデータ
	static int	m_nScoreCount[PLAYER_LIFE_UP];			// スコアの消費量
	int			m_LifeCount;			// ライフ強化回数	
};
#endif
