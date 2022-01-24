//=============================================================================
//
// ボスエフェクト1処理 [boss effect1.h]
// Author : 吉田悠人
//
//=============================================================================

#ifndef _BOSS_EFFECT_1_H_
#define _BOSS_EFFECT_1_H_
//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "scene2d.h"
#include "boss effect base.h"

//=============================================================================
// クラス定義
//=============================================================================
class CBossEffectType1 :public CBossEffectBase
{
public:
	CBossEffectType1();								//コンストラクタ
		
	static HRESULT				Load(void);			//テクスチャ読み込み
	static void					Unload(void);		//テクスチャの破棄
	static CBossEffectType1*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	//生成処理


private:
	static TEXTURE_DATA		m_TextureData;	// テクスチャデータ

};
#endif