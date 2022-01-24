//=============================================================================
//
// ビルボード [billboard.h]
// Author : 吉田悠人
//
//=============================================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_
//=============================================================================
// ヘッダーファイル
//=============================================================================
#include "model.h"
#include "scene3d.h"

//=============================================================================
// クラス定義
//=============================================================================
class CBillboard :public CScene3d
{
public:
	CBillboard(int nPriority);
	virtual ~CBillboard();

	virtual HRESULT Init(void);		// 初期化処理
	virtual void Update(void);		// 終了処理
	virtual void Uninit(void);		// 終了処理
	virtual void Draw(void);		// 描画処理

	void SetColor(D3DXCOLOR col);						// カラーセッター
	D3DXCOLOR GetColor(void) { return m_col; };			// カラーゲッター
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);		// テクスチャ設定
	D3DXMATRIX GetMtxWorld(void) { return m_mtxWorld; }	// ワールドマトリクスゲッター

private:
	LPDIRECT3DTEXTURE9		m_pTexture;		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ
	D3DXMATRIX				m_mtxWorld;		// 行列計算用
	D3DXCOLOR				m_col;			// カラー
};
#endif