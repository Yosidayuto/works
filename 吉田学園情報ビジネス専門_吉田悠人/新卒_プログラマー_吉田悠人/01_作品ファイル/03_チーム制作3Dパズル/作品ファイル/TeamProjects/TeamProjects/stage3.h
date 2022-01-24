//=============================================================================
//
// ステージ_3 [stage3.h]
// Author : 吉田悠人
//
//=============================================================================
#ifndef _STAGE_3_H_
#define _STAGE_3_H_
//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "model.h"
#include "stage base.h"
#include "talk_stage3.h"

//=============================================================================
// クラス定義
//=============================================================================
class CStage3 :public CStageBase
{
public:
	typedef enum	//エネミーの出現モード
	{
		BLOCK_TYPE_NONE = 0,				//なし
		BLOCK_TYPE_START,					//スタート地点
		BLOCK_TYPE_GOAL,					//ゴール地点
		BLOCK_TYPE_TILE_GRASS,				//草ブロック
		BLOCK_TYPE_HINDRANCE_BIG_TREE,		//針葉樹(大きい)
		BLOCK_TYPE_HINDRANCE_SMALL_TREE,	//針葉樹(小さい)
		BLOCK_TYPE_ITEM_APPLE,				//リンゴブロック
		BLOCK_TYPE_ITEM_ORANGES,			//オレンジブロック
		BLOCK_TYPE_ITEM_GRAPES,				//ブドウブロック
		BLOCK_TYPE_ITEM_WATERMELON,			//スイカブロック
	}BLOCK_TYPE;

	CStage3();
	~CStage3();
	static void	Load(void);
	HRESULT Init(void);
	void	Uninit(void);
	void	Draw(void);
	void	Update(void);
	void	MapCreate(void);	//マップの生成

	static CTalkStage3* GetTalkStage3(void);

private:
	static char*			m_pFileName;	// ファイルネーム
	static MAP_DATA			m_pMapData;
	static CTalkStage3*		m_pTalkStage3;
};
#endif