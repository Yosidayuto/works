//=============================================================================
//
// 必殺スキルアローエフェクト 処理 [skill_arrow_rain.h]
// Author : 吉田悠人
//
//=============================================================================

//二重インクルード防止
#ifndef _SKILL_ARROW_RAIN_
#define _SKILL_ARROW_RAIN_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "scene.h"
#include "billboard.h"
//*****************************
// 前方宣言
//*****************************
class CSkillArrow;
class CPlayer;
//*****************************
//マクロ定義
//*****************************


//=============================================================================
// クラス定義
//=============================================================================
class CSkillArrowRain : public CScene
{
public:
	//============
	//メンバ関数
	//============
	CSkillArrowRain(int nPliority = OBJTYPE_PARTICLE);
	~CSkillArrowRain();
	static CSkillArrowRain *Create(const D3DXVECTOR3 pos, const D3DXCOLOR col ,CPlayer* pPlayer); // クラス生成
	HRESULT Init(void);		// 初期化
	void	Uninit(void);	// 終了
	void	Update(void);	// 更新
	void	Draw(void);		// 描画

private:
	void PosChange(void);	//位置の変化処理

	//============
	// メンバ変数
	//============
	CSkillArrow*	m_pSkillArrow;
	CPlayer *		m_pPlayer;
	D3DXVECTOR3		m_pos;			// 位置
	D3DXCOLOR		m_col;			// 色
	bool			m_bDeath;		// 死亡フラグ

};

#endif
