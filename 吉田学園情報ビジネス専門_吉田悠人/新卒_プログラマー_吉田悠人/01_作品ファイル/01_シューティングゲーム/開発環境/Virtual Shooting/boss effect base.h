//=============================================================================
//
// ボスエフェクトベース処理 [boss effect base.h]
// Author : 吉田悠人
//
//=============================================================================
#ifndef _BOSS_EFFECT_H_
#define _BOSS_EFFECT_H_
//=============================================================================
//インクルードファイル
//=============================================================================
#include"main.h"
#include"scene2d.h"

//=============================================================================
// クラス定義
//=============================================================================
class CBossEffectBase :public CScene2d
{
public:
	CBossEffectBase(int nPriorit = PRIORITY_OBJECT_1);	//コンストラクタ

	static HRESULT Load(void);	//テクスチャ読み込み
	static void Unload(void);	//テクスチャの破棄

	HRESULT Init(void);			//初期化処理
	void	Update(void);		//更新処理

	void	SetMaxTexture(int nMaxTexture);		//テクスチャの最大コマ数セッター
	int		GetMaxTexture(void);				//テクスチャの最大コマ数ゲッター
	void	SetCountAnime(int nCountAnime);		//アニメーションカウントセッター
	int		GetCountAnime(void);				//アニメーションカウンタゲッター
	void	SetLoop(bool bLoop);				//ループゲッター
	bool	GetLoop(void);						//ループセッター
private:
	int		m_nMaxCount;			// テクスチャの最大コマ数
	int		m_nMaxCountAnime;		// アニメーション最大カウント
	int		m_nCounterAnim;			// アニメーションカウンター
	int		m_nPatternAnimX;		// アニメーションパターンNo

	bool	m_bLoop;				// ループするか

};
#endif