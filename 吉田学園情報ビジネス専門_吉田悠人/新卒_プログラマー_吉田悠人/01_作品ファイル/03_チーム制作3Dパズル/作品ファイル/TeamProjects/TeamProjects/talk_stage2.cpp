//=============================================================================
//
//	トークステージ2 [talk_stage2.h]
//	Author : 吉田 悠人
//
//=============================================================================
//=============================================================================
// インクルードファイル
//=============================================================================
#include "talk_stage2.h"
#include "manager.h"
#include "renderer.h"
#include "inputkeyboard.h"
#include "talk no6.h"
#include "talk no7.h"
#include "talk no8.h"
#include "player.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CTalkStage2::CTalkStage2(int nPriority) :CTalkStageBese(nPriority)
{
	pTalk = nullptr;
	TalkData = TALK_6;
}


//=============================================================================
// セリフの生成
//=============================================================================
CTalkStage2 * CTalkStage2::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// メモリの確保
	CTalkStage2 * pTalk = NULL;
	pTalk = new CTalkStage2;
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
void CTalkStage2::Update(void)
{
	//NULLチェック
	if (pTalk != nullptr)
	{
		//トークが終わっているか
		if (pTalk->GetTalkEnd())
		{
			pTalk->Uninit();
			pTalk = nullptr;
			//プレイヤーの制限を解除
			if (TalkData == TALK_6)
			{
				CPlayer::GetPlayer()->SetAction(false);
			}

			//トークデータを進める
			TalkData = (TALK_DATA)(1 + TalkData);
		}
		return;
	}

	//もしpTalkがnullptrだったら生成
	switch (TalkData)
	{
	case TALK_6:
		//プレイヤーの制限をかける
		CPlayer::GetPlayer()->SetAction(true);

		//トーク生成
		pTalk = CTalkNo6::Create(GetPos(), Getsize());
		break;
	case TALK_7:
		//トーク生成
		pTalk = CTalkNo7::Create(GetPos(), Getsize());
		break;
	case TALK_8:
		//トーク生成
		pTalk = CTalkNo8::Create(GetPos(), Getsize());
		break;
	}

}
