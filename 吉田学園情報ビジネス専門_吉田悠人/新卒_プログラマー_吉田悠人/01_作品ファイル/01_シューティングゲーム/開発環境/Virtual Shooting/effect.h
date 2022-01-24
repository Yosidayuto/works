//=============================================================================
//
// エフェクト処理 [effect.h]
// Author : 吉田悠人
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_
//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "scene2d.h"

//=============================================================================
// クラス定義
//=============================================================================
class CEffect:public CScene2d
{
public:
	CEffect(int nPriorit = PRIORITY_OBJECT_1);
	typedef enum  //エフェクト種類
	{
		EFFECT_TYPE_BULLET = 0,
		EFFECT_TYPE_LASER,
		EFFECT_TYPE_MAX
	}EFFECT_TYPE;

	static CEffect*	Create(D3DXVECTOR3 Pos, D3DXCOLOR col, D3DXVECTOR3 size, EFFECT_TYPE type);	//生成処理
	static void		Unload(void);	//テクスチャの破棄
	static HRESULT	Load(void);		//テクスチャ読み込み

	HRESULT	Init(void);		// 初期化処理
	void	Update(void);	// 更新処理
	void	Draw(void);		// 描画処理
							   
	void	Effect(void);	// エフェクト処理
	void	LifeDown(void);	// エフェクト射程処理
private:
	static TEXTURE_DATA	m_TextureData[EFFECT_TYPE_MAX];	// テクスチャデータ
	EFFECT_TYPE			m_Type;							// タイプ
	int					m_nLife;						// エフェクトの射程距離

};

#endif