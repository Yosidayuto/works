//=============================================================================
//
//	スピードボタン[speed button.h]
//	Author:吉田　悠人
//
//=============================================================================

#ifndef _SPEED_BUTTON_H_
#define _SPEED_BUTTON_H_

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
class CSpeedButton :public CButton
{
public:

	CSpeedButton(int nPriorit = PRIORITY_UI_1);	//コンストラクタ
	static HRESULT			Load(void);
	static void				Unload(void);
	static CSpeedButton*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);


	HRESULT			Init(void);		// 初期化処理
	void			MouseOver(void);// マウスオーバー判定
	void			Push(void);		// プッシュ判定処理
	bool			SpeedUp(void);	// スピードアップ処理
	bool			SpeedDown(void);// スピードダウン処理
private:
	static TEXTURE_DATA	m_TextureData;			// テクスチャデータ
	static int	m_nScoreCount[PLAYER_LIFE_UP];	// スコアの消費量
	int			m_SpeedCount;					// ライフ強化回数	
};
#endif
