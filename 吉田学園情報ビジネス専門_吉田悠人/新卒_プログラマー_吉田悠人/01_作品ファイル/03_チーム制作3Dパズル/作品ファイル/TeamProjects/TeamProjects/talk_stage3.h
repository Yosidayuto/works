//=============================================================================
//
//	トークステージ3 [talk_stage3.h]
//	Author : 吉田 悠人
//
//=============================================================================

//二重インクルード防止
#ifndef _TALK_STAGE3_H_
#define _TALK_STAGE3_H_

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
class CTalkStage3 :public CTalkStageBese
{
public:
	// 会話UIの種類
	typedef enum
	{
		TALK_NONE = -1,
		TALK_9,
		TALK_10,
		TALK_11,
		TALK_12,
		TALK_MAX
	}TALK_DATA;

	CTalkStage3(int nPriorit = PRIORITY_UI_0);
	static CTalkStage3 *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void	Update(void);

private:
	CTalkbase* pTalk;	//トークのポインタ
	TALK_DATA TalkData;	//トークデータ
};
#endif // !_UI_H_
