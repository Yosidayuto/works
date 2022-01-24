//=============================================================================
//
// ワープエフェクト [warp_effect.h]
// Author : 吉田 悠人
//
//=============================================================================

//二重インクルード防止
#ifndef _WARP_EFFECT_H_
#define _WARP_EFFECT_H_

//*****************************
// インクルード
//*****************************
#include "scene.h"
//*****************************
//前方宣言
//*****************************

//*****************************
//マクロ定義
//*****************************

//*****************************
// クラス定義
//*****************************
class CWarpEffect : public CScene
{
public:
	//*****************************
	//メンバ関数
	//*****************************
	CWarpEffect();
	~CWarpEffect();

	static void Create(D3DXVECTOR3 pos, D3DXVECTOR3 GoalPos, D3DXCOLOR col);	//生成処理

	HRESULT Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);

private:

	void	CreateEffect(void);

	//*****************************
	// メンバ変数
	//*****************************
	D3DXVECTOR3 m_pos;		//位置
	D3DXVECTOR3 m_GoalPos;	//目的の位置
	D3DXVECTOR3 m_move;		//移動量
	D3DXCOLOR   m_col;		//色
	int nCreateCount;		//エフェクトを作るまでのカウント
};
#endif