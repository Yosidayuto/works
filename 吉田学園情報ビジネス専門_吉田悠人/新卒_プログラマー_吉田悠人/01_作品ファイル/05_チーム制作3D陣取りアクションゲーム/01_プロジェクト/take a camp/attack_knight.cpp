//=============================================================================
//
// 攻撃範囲タイプ騎士 [attack_knight.cpp]
// Author : 齋藤大行
//
//=============================================================================

//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "attack_knight.h"
#include "player.h"
#include "color_manager.h"
#include "sound.h"
#include "skill_effect.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CAttackKnight::CAttackKnight()
{
	/*m_nAttackCount = 0;
	m_nType = 0;*/
}

//=============================================================================
// デストラクタ
//=============================================================================
CAttackKnight::~CAttackKnight()
{
}

//=============================================================================
// 生成処理
//=============================================================================
CAttackKnight * CAttackKnight::Create(CPlayer* pPlayer)
{
	//メモリ確保
	CAttackKnight* pAttackKnight = NULL;
	pAttackKnight = new CAttackKnight;

	if (pAttackKnight != NULL)
	{
		pAttackKnight->SetType(CResourceCharacter::CHARACTER_KNIGHT);
		pAttackKnight->SetPlayer(pPlayer);	// プレイヤークラス取得
		pAttackKnight->Init();				// 初期化処理
	}
	return pAttackKnight;
}

//=============================================================================
// エフェクト生成
//=============================================================================
void CAttackKnight::CreateEffect(D3DXVECTOR3 pos, ATTACK_STATE state)
{
	//プレイヤーのポインタ
	CPlayer *pPlaryer = GetPlayer();
	int nLevel = GetLevel();

	//エフェクト生成
	CSkill_effect::Create(pPlaryer->GetPos() + pos + KNIGHT_EFFECT_POS, KNIGHT_EFFECT_SIZE, GET_COLORMANAGER->GetStepColor(pPlaryer->GetColorNumber(), 0),
	GET_COLORMANAGER->GetStepColor(pPlaryer->GetColorNumber(), 1),
	GET_COLORMANAGER->GetStepColor(pPlaryer->GetColorNumber(), 2), KNIGHT_EFFECT_LIFE, CSkill_effect::SKILLTYPE_KNIGHT, GetPlayer());
}

//=============================================================================
// SE再生
// Author:佐藤颯紀
//=============================================================================
void CAttackKnight::PlaySE(void)
{
	// サウンド情報の取得
	CSound *pSound = CManager::GetSound();

	// レベル情報の取得
	int nLevel = GetLevel();

	// 通常攻撃なら
	if (nLevel < MAX_LEVEL)
	{
		// SE再生
		pSound->Play(CSound::LABEL_SE_KENSI_ATTACK);
	}
	//　必殺なら
	else
	{
		// SE再生
		pSound->Play(CSound::LABEL_SE_KENSI_FINALATTACK);
	}

}

