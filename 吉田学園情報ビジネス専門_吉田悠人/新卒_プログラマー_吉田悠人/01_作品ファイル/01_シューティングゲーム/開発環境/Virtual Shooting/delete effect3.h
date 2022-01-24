//=============================================================================
//
// ボスデリートエフェクト3処理 [delete effect3.h]
// Author : 吉田悠人
//
//=============================================================================

#ifndef _DELETE_EFFECT_3_H_
#define _DELETE_EFFECT_3_H_
//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "scene2d.h"
#include "boss effect base.h"

//=============================================================================
// クラス定義
//=============================================================================
class CDeleteEffect3 :public CBossEffectBase
{
public:
	CDeleteEffect3();						// コンストラクタ

	static HRESULT			Load(void);		// テクスチャ読み込み
	static void				Unload(void);	// テクスチャの破棄
	static CDeleteEffect3*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// 生成処理

private:
	static TEXTURE_DATA		m_TextureData;	// テクスチャデータ

};
#endif