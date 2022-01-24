//=============================================================================
//
// 攻撃範囲タイプ魔法使い [attack_wizard.cpp]
// Author : 齋藤大行
//
//=============================================================================

//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "attack_wizard.h"
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
CAttackWizard::CAttackWizard()
{
	/*m_nAttackCount = 0;
	m_nType = 0;*/
}

//=============================================================================
// デストラクタ
//=============================================================================
CAttackWizard::~CAttackWizard()
{
}

//=============================================================================
// 生成処理
//=============================================================================
CAttackWizard * CAttackWizard::Create(CPlayer* pPlayer)
{

	//メモリ確保
	CAttackWizard* pAttackWizard = NULL;
	pAttackWizard = new CAttackWizard;

	if (pAttackWizard != NULL)
	{
		pAttackWizard->SetType(CResourceCharacter::CHARACTER_WIZARD);
		pAttackWizard->SetPlayer(pPlayer);	// プレイヤークラス取得
		pAttackWizard->Init();				// 初期化処理
	}
	return pAttackWizard;
}

//=============================================================================
// エフェクト生成
//=============================================================================

void CAttackWizard::CreateEffect(D3DXVECTOR3 pos, ATTACK_STATE state)
{

	if (state == CAttackBased::ATTACK_STATE_FINALATTACK)
	{
		CPlayer *pPlaryer = GetPlayer();
		//エフェクト生成
		CSkill_effect::Create(pPlaryer->GetPos() + pos + WIZARD_EFFECT_POS, WIZARD_EFFECT_SIZE, GET_COLORMANAGER->GetStepColor(pPlaryer->GetColorNumber(), 0),
			GET_COLORMANAGER->GetStepColor(pPlaryer->GetColorNumber(), 1),
			GET_COLORMANAGER->GetStepColor(pPlaryer->GetColorNumber(), 2), WIZARD_EFFECT_LIFE, CSkill_effect::SKILLTYPE_WIZARD_FINALATTACK, GetPlayer());
	}
	if (state == CAttackBased::ATTACK_STATE_ATTACK)
	{
		CPlayer *pPlaryer = GetPlayer();
		//エフェクト生成
		CSkill_effect::Create(pPlaryer->GetPos() + pos + WIZARD_EFFECT_POS, WIZARD_EFFECT_SIZE, GET_COLORMANAGER->GetStepColor(pPlaryer->GetColorNumber(), 0),
			GET_COLORMANAGER->GetStepColor(pPlaryer->GetColorNumber(), 1),
			GET_COLORMANAGER->GetStepColor(pPlaryer->GetColorNumber(), 2), WIZARD_EFFECT_LIFE, CSkill_effect::SKILLTYPE_WIZARD, GetPlayer());
	}

}
//=============================================================================
// SE再生
// Author:佐藤颯紀
//=============================================================================
void CAttackWizard::PlaySE(void)
{
	// サウンド情報の取得
	CSound *pSound = CManager::GetSound();

	// レベル情報の取得
	int nLevel = GetLevel();

	// 通常攻撃なら
	if (nLevel < MAX_LEVEL)
	{
		// SE再生
		pSound->Play(CSound::LABEL_SE_MAHOU_ATTACK);
	}
	//　必殺なら
	else
	{
		// SE再生
		pSound->Play(CSound::LABEL_SE_MAHOU_FINALATTACK);
	}
}
