//===================================================
//
// all_skill_gauge処理[all_skill_gauge.cpp]
// Author:伊藤陽梧
//
//====================================================

//**********************************
// インクルード
//**********************************
#include "all_skill_gauge.h"
#include "skill_gauge.h"
#include "color_manager.h"

//==================================
// マクロ定義
//==================================
#define SKILLGAUGE_SIZE (D3DXVECTOR3(20.0f, 20.0f, 0.0f))		// スキルゲージの大きさ
#define DEFAULT_COLOR	(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))		// 色の初期値

//==================================
// コンストラクタ
//==================================
CAllskillgauge::CAllskillgauge()
{
	// 初期化
	m_pSkillgauge_Icon = nullptr;
	m_pSkillgauge_Stencil = nullptr;
}

//==================================
// デストラクタ
//==================================
CAllskillgauge::~CAllskillgauge()
{
	// 初期化
	m_pSkillgauge_Icon = nullptr;
	m_pSkillgauge_Stencil = nullptr;
}

//==================================
// スキルゲージすべてのクリエイト
// nPlayerNum：プレイヤーの番号
//==================================
CAllskillgauge* CAllskillgauge::Create(const int nPlayerNum)
{
	// メモリの確保
	CAllskillgauge * pAllskillgauge = new CAllskillgauge;

	// アイコンとステンシル
	pAllskillgauge->m_pSkillgauge_Icon = CSkillgauge::Create(SKILLGAUGE_SIZE, DEFAULT_COLOR, nPlayerNum, CSkillgauge::SKILLGAUGE_ICON);
	pAllskillgauge->m_pSkillgauge_Stencil = CSkillgauge::Create(SKILLGAUGE_SIZE, GET_COLORMANAGER->GetIconColor(nPlayerNum), nPlayerNum, CSkillgauge::SKILLGAUGE_STENCIL);

	return pAllskillgauge;
}