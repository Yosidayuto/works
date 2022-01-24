//=============================================================================
//
// スキルアローラインエフェクト 処理 [skill_arrow_line.h]
// Author : 吉田悠人
//
//=============================================================================

//二重インクルード防止
#ifndef _SKILL_ARROW_LINE_
#define _SKILL_ARROW_LINE_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "billboard.h"
//*****************************
//マクロ定義
//*****************************


//=============================================================================
// クラス定義
//=============================================================================
class CSkillArrowLine : public CBillboard
{
public:
	//============
	//メンバ関数
	//============
	CSkillArrowLine(int nPliority = OBJTYPE_PARTICLE);
	~CSkillArrowLine();
	static CSkillArrowLine* Create(const D3DXVECTOR3 pos, const float fAngle, const D3DXCOLOR col); // クラス生成
	HRESULT Init(void);		// 初期化
	void	Update(void);	// 更新
	void	Draw(void);		// 描画

private:
	//============
	// メンバ変数
	//============
	int		m_nTile;		// ライフ
	bool	m_bDeath;		// 死亡フラグ
};

#endif
