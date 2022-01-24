//=============================================================================
//
//	トークステージ2 [talk_stage2.h]
//	Author : 吉田 悠人
//
//=============================================================================

//二重インクルード防止
#ifndef _TALK_STAGE2_H_
#define _TALK_STAGE2_H_

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
class CTalkStage2 :public CTalkStageBese
{
public:
	// 会話UIの種類
	typedef enum
	{
		TALK_NONE = -1,
		TALK_6,
		TALK_7,
		TALK_8,
		TALK_MAX
	}TALK_DATA;

	CTalkStage2(int nPriorit = PRIORITY_UI_0);
	static CTalkStage2 *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void	Update(void);

private:
	CTalkbase* pTalk;	//トークのポインタ
	TALK_DATA TalkData;	//トークデータ
};
#endif // !_UI_H_
