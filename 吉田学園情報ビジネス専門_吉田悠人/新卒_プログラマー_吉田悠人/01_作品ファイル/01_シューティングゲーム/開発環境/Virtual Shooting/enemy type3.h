//=============================================================================
//
// エネミータイプ3処理 [enemy type3.h]
// Author : 吉田悠人
//
//=============================================================================

#ifndef _ENEMY_TYPE_3_H_
#define _ENEMY_TYPE_3_H_

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
class CEnemyType3 :public CEnemyBase
{
public:
	CEnemyType3(int nPriorit = PRIORITY_OBJECT_1);	//コンストラクタ

	static HRESULT		Load(void);					// テクスチャ読み込み
	static void			Unload(void);				// テクスチャの破棄
	static CEnemyType3*	Create(ENEMY_MOVE_PATTERN MoveType,		// 行動パターン
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