//=============================================================================
//
//　円筒エフェクト処理 [effect_cylinder.h]
// Author : 林川紗梨夏
//
//=============================================================================
#ifndef _EFFECT_CYLINDER_H_
#define _EFFECT_CYLINDER_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene3d.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CEffectCylinder :public CScene3d
{
public:
	CEffectCylinder(int nPriority = 3);
	~CEffectCylinder();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);
	void SetColor(D3DXCOLOR Col);
	D3DXCOLOR GetColor(void) { return m_Col; };
private:
	D3DXMATRIX m_mtxWorld; //ワールドマトリクス
	LPDIRECT3DTEXTURE9		m_pTexture;				//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;				//頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;//インデックスバッファポインタ
	D3DXCOLOR	 			m_Col;		//頂点カラー
};
#endif