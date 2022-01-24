//=============================================================================
//
// ビルボード [billboard.h]
// Author : 吉田悠人
//
//=============================================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_
//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "model.h"
//=============================================================================
// マクロ定義
//=============================================================================

//=============================================================================
// 構造体定義
//=============================================================================

//=============================================================================
// クラス定義
//=============================================================================
class CBillboard :public CObject
{
public:
	CBillboard();
	~CBillboard();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPosition(D3DXVECTOR3 pos);									// 位置セッター
	void SetSize(D3DXVECTOR3 size);										// サイズセッター
	void SetRot(D3DXVECTOR3 rot);										// サイズセッター
	void SetColor(D3DXCOLOR col);										// カラーセッター
	void SetTex(float fTexX, float fTexY, float fTexX2, float fTexY2);	// テクスチャセッター
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);						// バインドテクスチャ

	D3DXVECTOR3 GetPosition(void) { return m_pos; }						//位置ゲッター
	D3DXVECTOR3 GetSize(void) { return m_size; }						//サイズゲッター
	D3DXVECTOR3 GetRot(void) { return m_rot; }						//サイズゲッター
	D3DXCOLOR GetColor(void) { return m_col; }							//カラーゲッター

private:
	LPDIRECT3DTEXTURE9		m_pTexture;	// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファへのポインタ
	D3DXMATRIX				m_mtxWorld;	//行列計算用
	
	D3DXVECTOR3 m_pos;	// 位置
	D3DXVECTOR3 m_size;	// サイズ
	D3DXVECTOR3 m_rot;		// 角度
	D3DXCOLOR	m_col;	// カラー
	float m_fTexX;		// テクスチャ位置X
	float m_fTexY;		// テクスチャ位置Y
	float m_fTexX2;		// テクスチャ位置X2
	float m_fTexY2;		// テクスチャ位置Y2
};
#endif