//=============================================================================
//
// スキルアローエフェクト 処理 [skill_arrow.h]
// Author : 吉田悠人
//
//=============================================================================

//二重インクルード防止
#ifndef _SKILL_ARROW_
#define _SKILL_ARROW_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "billboard.h"
//*****************************
// 前方宣言
//*****************************

//*****************************
//マクロ定義
//*****************************


//=============================================================================
// クラス定義
//=============================================================================
class CSkillArrow : public CBillboard
{
public:
	//============
	//メンバ関数
	//============
	CSkillArrow(int nPliority = OBJTYPE_PARTICLE);
	~CSkillArrow();
	static CSkillArrow *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const float fAngle, int nTile,const D3DXCOLOR col); // クラス生成
	HRESULT Init(void);		// 初期化
	void	Update(void);	// 更新

	void	SetDeath(void) { m_bDeath = true; }		
	void	SetLife(int nLife) { m_nTile = nLife; }		// ライフセッター
	void	AddLife(int nLife) { m_nTile += nLife; }	// ライフ加算
	int 	GetLife(void) { return m_nTile; }			// ライフゲッター

private:
	void	PosChange(void);// 位置更新

	//============
	// メンバ変数
	//============
	D3DXVECTOR3 m_StartPos;	// スタート位置
	D3DXVECTOR3	m_move;		// 移動量
	bool		m_bDeath;	// 死亡フラグ
	int			m_nTile;	// ライフ
};

#endif
