//=============================================================================
//
// 攻撃範囲タイプ騎士 [attack_knight.cpp]
// Author : 齋藤大行
//
//=============================================================================

//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "attack_lancer.h"
#include "tile.h"
#include "player.h"
#include "attack.h"
#include "skill_effect.h"
#include "skill_circle.h"
#include "color_manager.h"
#include "sound.h"
#include "particle.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CAttackLancer::CAttackLancer()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CAttackLancer::~CAttackLancer()
{
}

//=============================================================================
// 生成処理
//=============================================================================
CAttackLancer * CAttackLancer::Create(CPlayer* pPlayer)
{
    //メモリ確保
    CAttackLancer* pAttackLancer = NULL;
    pAttackLancer = new CAttackLancer;

    if (pAttackLancer != NULL)
    {
        pAttackLancer->SetType(CResourceCharacter::CHARACTER_LANCER);
        pAttackLancer->SetPlayer(pPlayer);	// プレイヤークラス取得
        pAttackLancer->Init();				// 初期化処理
    }
    return pAttackLancer;
}

//=============================================================================
// エフェクト生成
//=============================================================================
void CAttackLancer::CreateEffect(D3DXVECTOR3 pos, ATTACK_STATE state)
{
	CPlayer *pPlayer = GetPlayer();
	//エフェクト生成

	D3DXVECTOR3 rot = pPlayer->GetRotDest();
	float fAngle = D3DXToDegree(rot.y);
	if ((int)fAngle / 90 % 2 == 0)
	{
		CParticle::Create(pPlayer->GetPos() + pos + LANCER_EFFECT_POS, THUKI_SKIIL_MOVE, LANCER_EFFECT_SIZE, LANCER_EFFECT_LIFE, GET_COLORMANAGER->GetStepColor(pPlayer->GetColorNumber(), 1), 0.05f, D3DXToDegree(rot.y), pPlayer, CParticle::PARTICLE_THUKI);
	}
	else if ((int)fAngle / 90 % 2 == 1 || (int)fAngle / 90 % 2 == -1)
	{
		CParticle::Create(pPlayer->GetPos() + pos + LANCER_EFFECT_POS, THUKI_SKIIL_MOVE, LANCER_EFFECT_SIZE, LANCER_EFFECT_LIFE, GET_COLORMANAGER->GetStepColor(pPlayer->GetColorNumber(), 1), 0.05f, D3DXToDegree(rot.y) + 180.0f, pPlayer, CParticle::PARTICLE_THUKI);
	}
	else
	{
		CParticle::Create(pPlayer->GetPos() + pos + LANCER_EFFECT_POS, THUKI_SKIIL_MOVE, LANCER_EFFECT_SIZE, LANCER_EFFECT_LIFE, GET_COLORMANAGER->GetStepColor(pPlayer->GetColorNumber(), 1), 0.05f, D3DXToDegree(rot.y), pPlayer, CParticle::PARTICLE_THUKI);
	}

}

//=============================================================================
// SE再生
// Author:佐藤颯紀
//=============================================================================
void CAttackLancer::PlaySE(void)
{
    // サウンド情報の取得
    CSound *pSound = CManager::GetSound();

    // レベル情報の取得
    int nLevel = GetLevel();

    // 通常攻撃なら
    if (nLevel < MAX_LEVEL)
    {
        // SE再生
        pSound->Play(CSound::LABEL_SE_YARI_ATTACK);
    }
    //　必殺なら
    else
    {
        // SE再生
        pSound->Play(CSound::LABEL_SE_YARI_FINALATTACK);
    }
}