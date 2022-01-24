//=============================================================================
//
//	トークステージ1 [talk_stage1.h]
//	Author : 吉田 悠人
//
//=============================================================================

//二重インクルード防止
#ifndef _TALK_STAGE1_H_
#define _TALK_STAGE1_H_

//====================================
//インクルード
//====================================
#include "main.h"
#include "talk_stage_base.h"

//====================================
//前方宣言
//====================================
class CTalkbase;
//====================================
// クラス定義
//====================================
class CTalkStage1:public CTalkStageBese
{
public:
	// 会話UIの種類
	typedef enum
	{
		TALK_NONE = -1,
		TALK_1,
		TALK_2,
		TALK_3,
		TALK_4,
		TALK_5,
		TALK_MAX
	}TALK_DATA;

	CTalkStage1(int nPriorit = PRIORITY_UI_0);
	static CTalkStage1 *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void	Update(void);

private:
	CTalkbase* pTalk;	//トーク1のポインタ
	TALK_DATA TalkData;	//トークデータ
};
#endif // !_UI_H_
