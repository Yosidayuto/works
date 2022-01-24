//=============================================================================
//
// ゲーム [game.h]
// Author : 吉田悠人
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_
//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "main.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define SQUARE_SIZE (50)	//１マス縦横のサイズ

//=============================================================================
//  前方宣言
//=============================================================================
class CCamera;
class CPlayer;
class CTalk;
class CStageNumber;
class CStageBase;
//=============================================================================
// クラス定義
//=============================================================================
class CGame
{
public:
	typedef enum	//マップ種類
	{
		MAP_TYPE_1 = 0,
		MAP_TYPE_2,
		MAP_TYPE_3,
		MAP_TYPE_MAX
	}MAP_TYPE;

	CGame();
	~CGame();

	HRESULT Init(void);
	void	Update(void);
	void	Draw(void);
	void	Uninit(void);

	static void	SetMapMode(MAP_TYPE MapMode);	//マップモードセッター
	static MAP_TYPE GetMapMode(void);			//マップモードゲッターz

private:
	CCamera*		m_pCamera;			// カメポインタ
	CTalk*			m_pTalk;			// 会話UI
	CStageNumber*	m_pStageNumber;		// ステージナンバーUI
	static MAP_TYPE	m_MapMode;			// マップデータ
	static CStageBase*	m_pStage_1;		// ステージ1ポインタ
	static CStageBase*	m_pStage_2;		// ステージ2ポインタ
	static CStageBase*	m_pStage_3;		// ステージ3ポインタ

};
#endif
