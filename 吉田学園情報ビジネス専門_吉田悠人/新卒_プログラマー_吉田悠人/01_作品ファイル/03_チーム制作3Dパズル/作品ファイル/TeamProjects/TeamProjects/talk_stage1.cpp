//=============================================================================
//
//	トークステージ1 [talk_stage1.h]
//	Author : 吉田 悠人
//
//=============================================================================
//=============================================================================
// インクルードファイル
//=============================================================================
#include "talk_stage1.h"
#include "manager.h"
#include "renderer.h"
#include "inputkeyboard.h"
#include "player.h"
#include "talk no1.h"
#include "talk no2.h"
#include "talk no3.h"
#include "talk no4.h"
#include "talk no5.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CTalkStage1::CTalkStage1(int nPriority):CTalkStageBese(nPriority)
{
	pTalk		= nullptr;
	TalkData	= TALK_1;
}

//=============================================================================
// 生成関数
//=============================================================================
CTalkStage1 * CTalkStage1::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// メモリの確保
	CTalkStage1 * pTalk = NULL;
	pTalk = new CTalkStage1;

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
void CTalkStage1::Update(void)
{
	//キーボード入力取得
	CInputKeyboard* pKeyInput = (CInputKeyboard*)CManager::GetInputKey();

	//NULLチェック
	if (pTalk != nullptr)
	{
		//トークが終わっているか
		if (pTalk->GetTalkEnd())
		{
			pTalk->Uninit();
			pTalk = nullptr;

			//プレイヤーの制限を解除
			if (TalkData == TALK_2)
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
	case TALK_1:
		//プレイヤーの制限をかける
		CPlayer::GetPlayer()->SetAction(true);
		//トーク生成
		pTalk = CTalkNo1::Create(GetPos(), Getsize());
		break;
	case TALK_2:
		//トーク生成
		pTalk = CTalkNo2::Create(GetPos(), Getsize());
		break;
	case TALK_3:
		//トーク生成
		pTalk = CTalkNo3::Create(GetPos(), Getsize());
		break;
	case TALK_4:
		//トーク生成
		pTalk = CTalkNo4::Create(GetPos(), Getsize());
		break;
	case TALK_5:
		//トーク生成
		pTalk = CTalkNo5::Create(GetPos(), Getsize());
		break;

	}
}

