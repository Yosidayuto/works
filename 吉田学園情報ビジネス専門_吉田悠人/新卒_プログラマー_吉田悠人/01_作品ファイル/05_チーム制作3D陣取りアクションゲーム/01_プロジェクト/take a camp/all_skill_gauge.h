//=============================================================================
//
// all_skill_gaugeヘッダ [all_skill_gauge.h]
// Author : 伊藤陽梧
//
//=============================================================================

//二重インクルード防止
#ifndef _ALL_SKILL_GAUGE_H_
#define _ALL_SKILL_GAUGE_H_

//=============================================================================
// 前方宣言
//=============================================================================
class CSkillgauge;

//=============================================================================
// クラス定義
//=============================================================================

// スキルゲージクラス
class CAllskillgauge
{
public:
	//============
	// メンバ関数
	//============
	CAllskillgauge();
	~CAllskillgauge();
	static CAllskillgauge* Create(const int nPlayerNum);

	//============
	// ゲッター
	//============
	CSkillgauge * GetSkillgaugeIcon() { return m_pSkillgauge_Icon; }
	CSkillgauge * GetSkillgaugeStencil() { return m_pSkillgauge_Stencil; }
private:
	//============
	// メンバ変数
	//============
	CSkillgauge * m_pSkillgauge_Icon;		// スキルゲージのアイコン
	CSkillgauge * m_pSkillgauge_Stencil;	// スキルゲージのステンシル
};

#endif