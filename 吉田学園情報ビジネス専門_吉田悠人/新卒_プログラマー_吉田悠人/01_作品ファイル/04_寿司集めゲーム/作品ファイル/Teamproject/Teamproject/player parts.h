//=============================================================================
//
// プレイヤーパーツ [player parts.h]
// Author : 吉田悠人
//
//=============================================================================
#ifndef _PLAYER_PARTS_H_
#define _PLAYER_PARTS_H_

//=============================================================================
// ヘッダーファイル
//=============================================================================
#include "scene3d.h"
#include "billboard.h"
#include "food base.h"

//=============================================================================
//クラス定義
//=============================================================================
class CPlayerParts : public CBillboard
{
public:
	CPlayerParts(int nPriority = 3);
	~CPlayerParts();
	void Update(void);
	void SetParent(CScene3d* pParent);											// 親データセッター
	CFoodBase::FOOD_TYPE GetType(void) { return m_Type; };						//タイプゲッター
	void				 SetType(CFoodBase::FOOD_TYPE Type) { m_Type = Type; };	//タイプセッター
private: 
	void Tracking(void);		// 追尾処理
	void Rot(void);				// 向き処理

	CFoodBase::FOOD_TYPE m_Type;	// パーツのタイプ
	CScene3d* 	m_pParent;			// 親パーツのポインタ
	D3DXVECTOR3 m_Move;				// 移動量
	const int	m_nModel = 1;		// テクスチャ番号
};
#endif // !_BLOCK_H_


