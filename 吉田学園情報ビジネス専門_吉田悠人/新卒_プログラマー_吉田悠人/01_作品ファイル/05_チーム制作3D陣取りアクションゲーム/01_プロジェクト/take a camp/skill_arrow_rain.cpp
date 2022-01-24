//=============================================================================
//
// 必殺スキルアローエフェクト 処理 [skill_arrow_rain.cpp]
// Author : 吉田悠人
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "skill_arrow_rain.h"
#include "skill_circle.h"
#include "skill_arrow.h"
#include "resource_texture.h"
#include "player.h" 
#include "skill_effect.h"

//*****************************
//マクロ定義
//*****************************
#define ARROW_CIRCLE		(D3DXVECTOR3(1.0f,1.5f,1.0f))
#define ARROW_RAIN_SPEED	(2.0f)							// エフェクトのスピード
#define ARROW_LIFE			(2)								// ライフ

//=============================================================================
//コンストラクタ
//=============================================================================
CSkillArrowRain::CSkillArrowRain(int nPliority)
{
	m_pSkillArrow = nullptr;
	m_bDeath = false;
}

//===================================
// デストラクタ
//===================================
CSkillArrowRain::~CSkillArrowRain()
{
}

//===================================
// 生成処理関数
//===================================
CSkillArrowRain * CSkillArrowRain::Create(const D3DXVECTOR3 pos, const D3DXCOLOR col, CPlayer* pPlayer)
{
	//メモリ確保
	CSkillArrowRain* pSkillArrowRain = nullptr;
	pSkillArrowRain = new CSkillArrowRain;

	//NULLチェック
	if (pSkillArrowRain != nullptr)
	{
		//位置設定
		pSkillArrowRain->m_pos = pos;
		//カラー設定
		pSkillArrowRain->m_col = col;
		pSkillArrowRain->m_pPlayer = pPlayer;
		//初期化処理
		pSkillArrowRain->Init();

	}
	return pSkillArrowRain;
}

//===================================
// 初期化処理
//===================================
HRESULT CSkillArrowRain::Init(void)
{
	//矢のエフェクト生成
	m_pSkillArrow = CSkillArrow::Create(m_pos, D3DXVECTOR3(0.0f,-ARROW_RAIN_SPEED,0.0f),0.0f, ARROW_LIFE,m_col);

	return S_OK;
}

//===================================
// 終了処理
//===================================
void CSkillArrowRain::Uninit(void)
{
	Release();
}

//===================================
// 更新処理
//===================================
void CSkillArrowRain::Update(void)
{
	//位置更新処理
	PosChange();

	//死亡フラグが立っているか
	if (m_bDeath)
	{
		//終了処理
		Uninit();
	}
}

//===================================
// 描画処理
//===================================
void CSkillArrowRain::Draw(void)
{
}

//===================================
// 位置の変化処理
//===================================
void CSkillArrowRain::PosChange(void)
{
	D3DXVECTOR3 pos = m_pSkillArrow->GetPos();


	//一定の位置に来ると
	if (pos.y <= 0.0f)
	{
		//衝撃波を出す
		CSkill_circle::Create(D3DXVECTOR3(pos.x, ARROW_CIRCLE.y, pos.z), ARROW_CIRCLE, m_col, ARCHER_EFFECT_LIFE, CSkill_circle::EFFECTTYPE_SKIIL,m_pPlayer);
		//死亡フラグを立てる
		m_pSkillArrow->SetDeath();
		//死亡フラグを立てる
		m_bDeath = true;
	}
}
