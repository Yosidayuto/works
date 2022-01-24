//=============================================================================
//
// スキルトランプエフェクト 処理 [skill_trump.h]
// Author : 吉田悠人
//
//=============================================================================

//二重インクルード防止
#ifndef _SKILL_TRUMP_
#define _SKILL_TRUMP_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "scene.h"
#include "billboard.h"
//*****************************
// 前方宣言
//*****************************
class CBillboard;
//*****************************
//マクロ定義
//*****************************


//=============================================================================
// クラス定義
//=============================================================================
class CSkillTrump : public CBillboard
{
public:
	//============
	//列挙型
	//============
	typedef enum
	{
		NONE_ANGLE = 0,
		RIGHT_ANGLE,
		LEFT_ANGLE,
		MAX_ANGLE,
	}ANGLE_PATTERN;
	//============
	//メンバ関数
	//============
	CSkillTrump(int nPliority = OBJTYPE_PARTICLE);
	~CSkillTrump();

	static CSkillTrump *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size,const D3DXVECTOR3 MoveAngle, const D3DXCOLOR col); // クラス生成

	HRESULT Init(void); // 初期化
	void Update(void);  // 更新

private:
	void AngleChange(void);	//向きの変化処理
	void PosChange(void);	//位置の変化処理

	
	//============
	// メンバ変数
	//============
	ANGLE_PATTERN	AnglePattern;	// 回る角度
	D3DXVECTOR3		m_move;			// 移動量
	bool			m_bDeath;		// 死亡フラグ
	D3DXVECTOR3		m_MoveAngle;	// 移動する角度
	int	 			m_ColCount;		// カラー変化カウント
};

#endif
