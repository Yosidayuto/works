//=============================================================================
//
// エクスプロージョン処理 [explosion.h]
// Author : 吉田悠人
//
//=============================================================================

#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_
//=============================================================================
//インクルードファイル
//=============================================================================
#include"main.h"
#include"scene2d.h"

//=============================================================================
// クラス定義
//=============================================================================
class CExplosion :public CScene2d
{
public:
	CExplosion(int nPriorit= PRIORITY_OBJECT_1);	// コンストラクタ
													   
	static HRESULT		Load(void);					// テクスチャ読み込み
	static void			Unload(void);				// テクスチャの破棄
	static CExplosion*	Create(D3DXVECTOR3 Pos);	// 生成処理
	void				Update(void);				// 更新処理
	HRESULT				Init(void);					// 初期化処理

private:
	static TEXTURE_DATA	m_TextureData;		// テクスチャデータ
	int					m_nCounterAnim;		// アニメーションカウンター
	int					m_nPatternAnimX;	// アニメーションパターンNo
	int					m_nPatternAnimY;	// アニメーションパターンNo

};
#endif