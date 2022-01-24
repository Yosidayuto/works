//=============================================================================
//
// ステージ_2 [stage2.h]
// Author : 吉田悠人
//
//=============================================================================
#ifndef _STAGE_2_H_
#define _STAGE_2_H_
//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "model.h"
#include "stage base.h"
#include "talk_stage2.h"

//=============================================================================
// クラス定義
//=============================================================================
class CStage2 :public CStageBase
{
public:
	typedef enum	//エネミーの出現モード
	{
		BLOCK_TYPE_NONE = 0,			//なし
		BLOCK_TYPE_START,				//スタート地点
		BLOCK_TYPE_GOAL,				//ゴール地点
		BLOCK_TYPE_TILE_SAMD,			//砂ブロック
		BLOCK_TYPE_TILE_SPROUT,			//芽ブロック
		BLOCK_TYPE_ITEM_SEEDS,			//種ブロック
		BLOCK_TYPE_ITEM_CUBE,			//箱ブロック
		BLOCK_TYPE_ITEM_SAMD_WALL,		//砂壁ブロック
	}BLOCK_TYPE;

	CStage2();
	~CStage2();
	static void	Load(void);
	HRESULT Init(void);
	void	Uninit(void);
	void	Draw(void);
	void	Update(void);
	void	MapCreate(void);	//マップの生成

	static CTalkStage2* GetTalkStage2(void);

private:
	static char*			m_pFileName;	// ファイルネーム
	static MAP_DATA			m_pMapData;
	static CTalkStage2*		m_pTalkStage2;
};
#endif