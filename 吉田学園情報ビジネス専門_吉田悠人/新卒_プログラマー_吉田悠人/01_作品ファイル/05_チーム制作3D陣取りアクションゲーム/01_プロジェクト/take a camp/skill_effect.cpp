//=============================================================================
//
// スキルエフェクト定義 [skill_effect.cpp]
// Author : 齋藤大行
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "skill_circle.h"
#include "skill_effect.h"
#include "base_Cylinder.h"
#include "resource_texture.h"
#include "manager.h"
#include "renderer.h"
#include "skill_trump.h"
#include "skill_arrow_rain.h"
#include "particle.h"
#include "player.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define KNIGHT_POSSHIFT (D3DXVECTOR3(3.0f, 0.0f, 3.0f))
#define ARCHER_CREATE_POS (D3DXVECTOR3(0.0f, 25.0f, 0.0f))	//弓兵のエフェクト生成位置

//=============================================================================
//静的メンバー変数
//=============================================================================

//=============================================================================
// コンストラクタ
//=============================================================================
CSkill_effect::CSkill_effect()
{
	m_type = SKILLTYPE_KNIGHT;
}

//=============================================================================
// デストラクタ
//=============================================================================
CSkill_effect::~CSkill_effect()
{
}

//=============================================================================
// 生成処理
//=============================================================================
void CSkill_effect::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXCOLOR col1, const D3DXCOLOR col2, const D3DXCOLOR col3,const int nlife, const SKILLTYPE type ,CPlayer * pPlayer)
{
	//タイプごとに生成処理
	switch (type)
	{
	case SKILLTYPE_KNIGHT:
		CSkill_circle::Create(pos, size+ NORMAL_SKIIL_SIZESHIFT, col1, nlife, CSkill_circle::EFFECTTYPE_SKIIL, pPlayer);
		CSkill_circle::Create(pos, size , col3, nlife, CSkill_circle::EFFECTTYPE_SKIILMINI, pPlayer);
		break;

	case SKILLTYPE_ARCHER:
		CSkillArrowRain::Create(pos + ARCHER_CREATE_POS, col1 , pPlayer);
		break;

	case SKILLTYPE_WIZARD:
		CSkill_circle::Create(pos + EXPLOSION_SKIIL_METEOR_IMPACT_POS, size - EXPLOSION_SKIIL_METEOR_IMPACT_SIZE + EXPLOSION_SKIIL_METEOR_IMPACT_SIZESHIFT, col3, nlife, CSkill_circle::EFFECTTYPE_IMPACT, pPlayer);
		break;

	case SKILLTYPE_WIZARD_FINALATTACK:
		CSkill_circle::Create(pos, size - EXPLOSION_SKIIL_CENTER_SIZE + EXPLOSION_SKIIL_CENTER_SIZESHIFT, col3, nlife, CSkill_circle::EFFECTTYPE_METEOR_CENTER, pPlayer);
		CSkill_circle::Create(pos, size + EXPLOSION_SKIIL_IMPACT_SIZE - EXPLOSION_SKIIL_IMPACT_SIZESHIFT, col2, nlife, CSkill_circle::EFFECTTYPE_METEOR_IMPACT, pPlayer);
		CSkill_circle::Create(pos, size, col3, nlife, CSkill_circle::EFFECTTYPE_METEOR, pPlayer);
		break;

	case SKILLTYPE_LANCER:

		break;

	case SKILLTYPE_MAGICIAN:
		CSkillTrump::Create(D3DXVECTOR3(pos.x, pos.y + 5, pos.z), size, D3DXVECTOR3(0, D3DXToRadian(-45), D3DXToRadian(60)), col1);
		CSkillTrump::Create(D3DXVECTOR3(pos.x, pos.y + 5, pos.z), size, D3DXVECTOR3(0, D3DXToRadian(-45), D3DXToRadian(50)), col1);
		CSkillTrump::Create(D3DXVECTOR3(pos.x, pos.y + 5, pos.z), size, D3DXVECTOR3(0, D3DXToRadian(-45), D3DXToRadian(40)), col1);
		
		CSkillTrump::Create(D3DXVECTOR3(pos.x, pos.y + 5, pos.z), size, D3DXVECTOR3(0, D3DXToRadian(45), D3DXToRadian(60)), col1);
		CSkillTrump::Create(D3DXVECTOR3(pos.x, pos.y + 5, pos.z), size, D3DXVECTOR3(0, D3DXToRadian(45), D3DXToRadian(50)), col1);
		CSkillTrump::Create(D3DXVECTOR3(pos.x, pos.y + 5, pos.z), size, D3DXVECTOR3(0, D3DXToRadian(45), D3DXToRadian(40)), col1);

		CSkillTrump::Create(D3DXVECTOR3(pos.x, pos.y + 5, pos.z), size, D3DXVECTOR3(0, D3DXToRadian(135), D3DXToRadian(60)), col1);
		CSkillTrump::Create(D3DXVECTOR3(pos.x, pos.y + 5, pos.z), size, D3DXVECTOR3(0, D3DXToRadian(135), D3DXToRadian(50)), col1);
		CSkillTrump::Create(D3DXVECTOR3(pos.x, pos.y + 5, pos.z), size, D3DXVECTOR3(0, D3DXToRadian(135), D3DXToRadian(40)), col1);
	
		CSkillTrump::Create(D3DXVECTOR3(pos.x, pos.y + 5, pos.z), size, D3DXVECTOR3(0, D3DXToRadian(-135), D3DXToRadian(60)), col1);
		CSkillTrump::Create(D3DXVECTOR3(pos.x, pos.y + 5, pos.z), size, D3DXVECTOR3(0, D3DXToRadian(-135), D3DXToRadian(50)), col1);
		CSkillTrump::Create(D3DXVECTOR3(pos.x, pos.y + 5, pos.z), size, D3DXVECTOR3(0, D3DXToRadian(-135), D3DXToRadian(40)), col1);
		break;

	case SKILLTYPE_THIER:		
		CParticle::Create(pos + SLASH_SKIIL_POSSHIFT, SLASH_SKIIL_MOVE, size, nlife, col3, 0.05f, D3DXToDegree(pPlayer->GetRotDest().y), pPlayer ,CParticle::PARTICLE_SLASH);
		break;
	}
}
