//=============================================================================
//
// 攻撃範囲タイプ弓使い [attack_archer.cpp]
// Author : 吉田悠人
//
//=============================================================================

//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "attack_archer.h"
#include "tile.h"
#include "player.h"
#include "attack.h"
#include "skill_effect.h"
#include "skill_circle.h"
#include "color_manager.h"
#include "skill_arrow.h"
#include "sound.h"

//*****************************
//マクロ定義
//*****************************
#define ARROW_LIFE (60*3)

//=============================================================================
// コンストラクタ
//=============================================================================
CAttackArcher::CAttackArcher()
{
	m_pSkillArrow = nullptr;
}

//=============================================================================
// デストラクタ
//=============================================================================
CAttackArcher::~CAttackArcher()
{
}

//=============================================================================
// 生成処理
//=============================================================================
CAttackArcher * CAttackArcher::Create(CPlayer* pPlayer)
{
	//メモリ確保
	CAttackArcher* pAttackKnight = NULL;
	pAttackKnight = new CAttackArcher;

	if (pAttackKnight != NULL)
	{
		pAttackKnight->SetType(CResourceCharacter::CHARACTER_ARCHER);
		pAttackKnight->SetPlayer(pPlayer);	// プレイヤークラス取得
		pAttackKnight->Init();				// 初期化処理
	}
	return pAttackKnight;
}


//=============================================================================
// エフェクト生成
//=============================================================================
void CAttackArcher::CreateEffect(D3DXVECTOR3 pos, ATTACK_STATE state)
{
	//プレイヤーのポインタ
	CPlayer *pPlaryer = GetPlayer();
	if (GetState() == ATTACK_STATE_FINALATTACK)
	{
		//エフェクト生成
		CSkill_effect::Create(pPlaryer->GetPos() + pos + NORMAL_SKIIL_POS, NORMAL_SKIIL_SIZE, GET_COLORMANAGER->GetStepColor(pPlaryer->GetColorNumber(), 1),
			GET_COLORMANAGER->GetStepColor(pPlaryer->GetColorNumber(), 2),
			GET_COLORMANAGER->GetStepColor(pPlaryer->GetColorNumber(), 3), ARCHER_EFFECT_LIFE,CSkill_effect::SKILLTYPE_ARCHER, GetPlayer());

	}
}

//=============================================================================
// エフェクト(一回)生成
// Author:吉田悠人
//=============================================================================
void CAttackArcher::OnceEffect(D3DXVECTOR3 pos)
{
	//プレイヤーのポインタ
	CPlayer *pPlaryer = GetPlayer();

	if (GetState() == ATTACK_STATE_ATTACK)
	{
		D3DXVECTOR3 rot = pPlaryer->GetRotDest();
		float fAngle = D3DXToDegree(rot.y);
		//矢のエフェクト生成
		CSkillArrow::Create(pPlaryer->GetPos() + D3DXVECTOR3(0.0f, 10.0f, 0.0f), D3DXVECTOR3(cosf(rot.y + D3DXToRadian(90))*3.0f, 0.0f, -sinf(rot.y + D3DXToRadian(90))*3.0f), D3DXToDegree(rot.y), GetAttackSquare().nMaxHitRange,GET_COLORMANAGER->GetStepColor(pPlaryer->GetColorNumber(), pPlaryer->GetChargeTilelevel()));
	}
}


//=============================================================================
// SE再生
// Author:佐藤颯紀
//=============================================================================
void CAttackArcher::PlaySE(void)
{
	// サウンド情報の取得
	CSound *pSound = CManager::GetSound();

	// レベル情報の取得
	int nLevel = GetLevel();

	// 通常攻撃なら
	if (nLevel < MAX_LEVEL)
	{
		// SE再生
		pSound->Play(CSound::LABEL_SE_YUMI_ATTACK);
	}
	//　必殺なら
	else
	{
		// SE再生
		pSound->Play(CSound::LABEL_SE_YUMI_FINALATTACK);
	}

}

