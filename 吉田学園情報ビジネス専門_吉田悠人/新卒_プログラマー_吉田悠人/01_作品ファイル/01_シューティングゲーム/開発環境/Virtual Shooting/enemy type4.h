//=============================================================================
//
// エネミータイプ3処理 [enemy type4.h]
// Author : 吉田悠人
//
//=============================================================================

#ifndef _ENEMY_TYPE_4_H_
#define _ENEMY_TYPE_4_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "enemy base.h"
//=============================================================================
//前方宣言
//=============================================================================

//=============================================================================
// クラス定義
//=============================================================================
class CEnemyType4 :public CEnemyBase
{
public:
	CEnemyType4(int nPriorit = PRIORITY_OBJECT_1);	//コンストラクタ

	static HRESULT		Load(void);					// テクスチャ読み込み
	static void			Unload(void);				// テクスチャの破棄
	static CEnemyType4*	Create(ENEMY_MOVE_PATTERN MoveType,		// 行動パターン
								ENEMY_ATTACK_PATTERN AttackType,	// 攻撃パターン
								int nInTime,						// 出現タイム
								int nActionTime,					// アクションタイム
								int nAttacTime,						// アタックタイム
								int nReturnTime,					// リターンタイム
								D3DXVECTOR3 pos,					// 出現位置
								float fSpeed,						// スピード
								int nLife);							// ライフ


	void	Update(void);			// 更新処理

private:
	static TEXTURE_DATA	m_TextureData;					// テクスチャデータ

};
#endif