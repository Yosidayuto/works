//=============================================================================
//
// 攻撃範囲 タイプ奇術師[attack_magician.h]
// Author : 増澤 未来
//
//=============================================================================
#ifndef _ATTACK_MAGICIAN_H_
#define _ATTACK_MAGICIAN_H_

//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "attack.h"
#include "scene.h"

//=============================================================================
// クラス定義
//=============================================================================
class CAttackMagician : public CAttackBased
{
public:
	//関数定義
	CAttackMagician();
	~CAttackMagician();

	static CAttackMagician *Create(CPlayer* pPlayer);

	void PlaySE(void);

private:
	void CreateEffect(D3DXVECTOR3 pos, ATTACK_STATE state); // エフェクト生成

};
#endif