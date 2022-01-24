//=============================================================================
//
// ステージ_1 [stage1.h]
// Author : 吉田悠人
//
//=============================================================================
#ifndef _STAGE_1_H_
#define _STAGE_1_H_
//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "model.h"
#include "stage base.h"
#include "talk_stage1.h"

//=============================================================================
// クラス定義
//=============================================================================
class CStage1 :public CStageBase
{
public:
	typedef enum	//エネミーの出現モード
	{
		BLOCK_TYPE_NONE = 0,				//なし
		BLOCK_TYPE_START,					//スタート地点
		BLOCK_TYPE_GOAL,					//ゴール地点
		BLOCK_TYPE_TILE_RED_SAMD,			//赤砂ブロック
		BLOCK_TYPE_HINDRANCE_BUILDING_1,	//ビル
		BLOCK_TYPE_HINDRANCE_BUILDING_2,	//ビル(半壊)
		BLOCK_TYPE_ITEM_GARBAGE,			//ゴミブロック
	}BLOCK_TYPE;

	CStage1();
	~CStage1();
	static void	Load(void);
	HRESULT Init(void);
	void	Uninit(void);
	void	Draw(void);
	void	Update(void);
	void	MapCreate(void);		//マップの生成
	void	TitleMapCreate(void);	//タイトル表示用マップの生成

	static CTalkStage1* GetTalkStage1(void);

private:
	static char*		m_pFileName;	// ファイルネーム
	static MAP_DATA		m_pMapData;		
	static CTalkStage1*	m_pTalkStage1;
};
#endif