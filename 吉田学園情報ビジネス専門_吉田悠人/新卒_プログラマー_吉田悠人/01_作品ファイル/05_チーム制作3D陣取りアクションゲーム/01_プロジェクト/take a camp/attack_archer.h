//=============================================================================
//
// 攻撃範囲 タイプ弓使い[attack_archer.h]
// Author : 増澤 未来
//
//=============================================================================
#ifndef _ATTACK_ARCHER_H_
#define _ATTACK_ARCHER_H_

//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "attack.h"
#include "scene.h"
//*****************************
// 前方宣言
//*****************************
class CSkillArrow;

//=============================================================================
// クラス定義
//=============================================================================
class CAttackArcher : public CAttackBased
{
public:
	//関数定義
	CAttackArcher();
	~CAttackArcher();

	static CAttackArcher *Create(CPlayer* pPlayer);

	void PlaySE(void);

private:
	void CreateEffect(D3DXVECTOR3 pos,ATTACK_STATE state); // エフェクト生成
	void OnceEffect(D3DXVECTOR3 pos);// 一回だけのエフェクト

	CSkillArrow*	m_pSkillArrow;


};
#endif