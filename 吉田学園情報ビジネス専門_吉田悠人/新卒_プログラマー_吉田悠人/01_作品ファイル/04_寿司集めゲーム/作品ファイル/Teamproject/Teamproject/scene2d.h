//=============================================================================
//
// 2Dシーン管理処理 [scene2d.h]
// Author : 林川紗梨夏
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CScene2d :public CScene
{
public:
	CScene2d(int nPriority = 3);
	~CScene2d();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);
	void SetPos(D3DXVECTOR3 Pos);
	void SetSize(D3DXVECTOR3 Size);
	void SetRot(D3DXVECTOR3 Rot);
	void SetTexture(D3DXVECTOR2 aTex[NUM_VERTEX]);
	void SetColor(D3DXCOLOR Col);
	void SetScale(float fScale);
	D3DXCOLOR GetColor(void) { return m_Col; };
	D3DXVECTOR3 GetPos(void) { return m_Pos; };
	D3DXVECTOR3 GetSize(void) { return m_Size; };
	D3DXVECTOR3 GetRot(void) { return m_Rot; };
	float GetScale(void) { return m_fScale; };
private:
	LPDIRECT3DTEXTURE9		m_pTexture;				//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;				//頂点バッファへのポインタ
	D3DXVECTOR3				m_Pos;					//座標
	D3DXVECTOR3				m_Size;					//サイズ
	D3DXVECTOR3				m_Rot;					//向き
	D3DXVECTOR2				m_aTex[NUM_VERTEX];		//テクスチャのUV座標
	D3DXCOLOR	 			m_Col;		//頂点カラー
	float					m_fScale;				//縮尺
	float					m_fAngle;				//角度
	float					m_fLength;				//長さ
};
#endif