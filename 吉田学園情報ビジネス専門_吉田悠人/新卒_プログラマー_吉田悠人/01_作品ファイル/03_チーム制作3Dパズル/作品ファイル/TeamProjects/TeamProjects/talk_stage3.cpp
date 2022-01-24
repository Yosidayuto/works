//=============================================================================
//
//	トークステージ3 [talk_stage3.cpp]
//	Author : 吉田 悠人
//
//=============================================================================
//=============================================================================
// インクルードファイル
//=============================================================================
#include "talk_stage3.h"
#include "manager.h"
#include "renderer.h"
#include "inputkeyboard.h"
#include "talk no9.h"
#include "talk no10.h"
#include "talk no11.h"
#include "talk no12.h"
#include "fade.h"
#include "player.h"
//=============================================================================
// コンストラクタ
//=============================================================================
CTalkStage3::CTalkStage3(int nPriority) :CTalkStageBese(nPriority)
{
	pTalk = nullptr;
	TalkData = TALK_9;
}

//=============================================================================
// セリフの生成
//=============================================================================
CTalkStage3 * CTalkStage3::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// メモリの確保
	CTalkStage3 * pTalk = NULL;
	pTalk = new CTalkStage3;
	if (pTalk != NULL)
	{
		// 座標をset
		pTalk->SetPos(pos);
		// サイズをset
		pTalk->SetSize(size);
		// 初期化処理
		pTalk->Init();
	}

	return pTalk;
}

//=============================================================================
// 更新処理
//=============================================================================
void CTalkStage3::Update(void)
{
	//フェード取得
	CFade* pFade = CManager::GetFadeout();


	//NULLチェック
	if (pTalk != nullptr)
	{
		//トークが終わっているか
		if (pTalk->GetTalkEnd())
		{
			pTalk->Uninit();
			pTalk = nullptr;
			//プレイヤーの制限を解除
			if (TalkData == TALK_9)
			{
				CPlayer::GetPlayer()->SetAction(false);
			}

			//トークデータを進める
			TalkData = (TALK_DATA)(1 + TalkData);
		}
		return;
	}
	switch (TalkData)
	{
	case TALK_9:
		//プレイヤーの制限をかける
		CPlayer::GetPlayer()->SetAction(true);
		
		//トーク生成
		pTalk = CTalkNo9::Create(GetPos(), Getsize());
		break;

	case TALK_10:
		//トーク生成
		pTalk = CTalkNo10::Create(GetPos(), Getsize());
		break;

	case TALK_11:
		//トーク生成
		pTalk = CTalkNo11::Create(GetPos(), Getsize());
		break;

	case TALK_12:
		//トーク生成
		pTalk = CTalkNo12::Create(GetPos(), Getsize());
		break;

	case TALK_MAX:
		//トーク生成
		pFade->SetBlackout(CManager::MODE_TITLE);
		break;

	}

}
