//=============================================================================
//
// 攻撃範囲タイプ盗賊 [attack_knight.cpp]
// Author : 増澤 未来
//
//=============================================================================

//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "attack_thief.h"
#include "tile.h"
#include "player.h"
#include "attack.h"
#include "skill_effect.h"
#include "skill_circle.h"
#include "color_manager.h"
#include "sound.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CAttackThief::CAttackThief()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CAttackThief::~CAttackThief()
{
	
	
}

//=============================================================================
// 生成処理
//=============================================================================
CAttackThief * CAttackThief::Create(CPlayer* pPlayer)
{
	//メモリ確保
	CAttackThief* pAttackKnight = NULL;
	pAttackKnight = new CAttackThief;

	if (pAttackKnight != NULL)
	{
		pAttackKnight->SetType(CResourceCharacter::CHARACTER_THIEF);
		pAttackKnight->SetPlayer(pPlayer);	// プレイヤークラス取得
		pAttackKnight->Init();				// 初期化処理
	}
	return pAttackKnight;
}

//=============================================================================
// エフェクト生成
//=============================================================================
void CAttackThief::CreateEffect(D3DXVECTOR3 pos, ATTACK_STATE state)
{
	//プレイヤーのポインタ
	CPlayer *pPlaryer = GetPlayer();
	//エフェクト生成
	CSkill_effect::Create(pPlaryer->GetPos() + pos + THIEF_EFFECT_POS, THIEF_EFFECT_SIZE, GET_COLORMANAGER->GetStepColor(pPlaryer->GetColorNumber(), 0),
		GET_COLORMANAGER->GetStepColor(pPlaryer->GetColorNumber(),1),
		GET_COLORMANAGER->GetStepColor(pPlaryer->GetColorNumber(),2), THIER_EFFECT_LIFE, CSkill_effect::SKILLTYPE_THIER, GetPlayer());
}

//=============================================================================
// SE再生
// Author:佐藤颯紀
//=============================================================================
void CAttackThief::PlaySE(void)
{
	// サウンド情報の取得
	CSound *pSound = CManager::GetSound();

	// レベル情報の取得
	int nLevel = GetLevel();

	// 通常攻撃なら
	if (nLevel < MAX_LEVEL)
	{
		// SE再生
		pSound->Play(CSound::LABEL_SE_TOZOKU_ATTACK);
	}
	//　必殺なら
	else
	{
		// SE再生
		pSound->Play(CSound::LABEL_SE_TOZOKU_FINALATTACK);
	}
}