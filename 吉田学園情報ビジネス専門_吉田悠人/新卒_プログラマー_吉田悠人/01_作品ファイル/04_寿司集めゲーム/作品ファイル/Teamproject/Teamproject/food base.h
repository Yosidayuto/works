//=============================================================================
//
// 食べ物ベース [food base.h]
// Author : 吉田悠人
//
//=============================================================================
#ifndef _BAIT_H_
#define _BAIT_H_
//=============================================================================
// ヘッダーファイル
//=============================================================================
#include "model.h"
#include "billboard.h"

//=============================================================================
// クラス定義
//=============================================================================
class CFoodBase :public CBillboard
{
public:
	CFoodBase(int nPriority=3);
	~CFoodBase();
	typedef enum		//フードタイプ
	{
		TYPE_EBI,		//エビ
		TYPE_EGG,		//卵
		TYPE_IKURA,		//イクラ
		TYPE_SALMON,	//サーモン
		TYPE_TUNA,		//マグロ
		TYPE_MAX		
	}FOOD_TYPE;

	void	Update(void);
		
	void		Collision(void);											// 当たり判定関数
	void		SetPoint(int nPoint);										// ポイントセッター
	int			GetPoint(void) { return m_nPoint; }							// ポイントゲッター
	void		SetFoodType(FOOD_TYPE FoodType) { m_FoodType = FoodType; }	// フードタイプセッター
	FOOD_TYPE	GetFoodType(void) { return m_FoodType; }					// フードタイプゲッター
private:
	int			m_nPoint;		// ポイント数値
	FOOD_TYPE	m_FoodType;		// フードタイプ
};

#endif