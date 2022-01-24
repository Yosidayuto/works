//=============================================================================
//
// 3Dポリゴン管理処理 [polygon3d.h]
// Author : 林川紗梨夏
//
//=============================================================================
#ifndef _POLYGON3D_H_
#define _POLYGON3D_H_

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
class CPolygon3d :public CScene3d
{
public:
	CPolygon3d(int nPriority = 3);
	~CPolygon3d();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);
	void SetTexture(D3DXVECTOR2 aTex[NUM_VERTEX]);
	void SetColor(D3DXCOLOR Col);
	void SetScale(float fScale);
	D3DXCOLOR GetColor(void) { return m_Col; };
	float GetScale(void) { return m_fScale; };
private:
	D3DXMATRIX m_mtxWorld; //ワールドマトリクス
	LPDIRECT3DTEXTURE9		m_pTexture;				//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;				//頂点バッファへのポインタ
	D3DXVECTOR2				m_aTex[NUM_VERTEX];		//テクスチャのUV座標
	D3DXCOLOR	 			m_Col;		//頂点カラー
	float					m_fScale;				//縮尺
	float					m_fAngle;				//角度
	float					m_fLength;				//長さ
};
#endif