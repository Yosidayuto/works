//=============================================================================
//
//	モデルデータ処理[model.h]
//	Author:吉田悠人
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "scene3d.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define MAX_MATERIAL (20)
//=============================================================================
//クラス定義
//=============================================================================
class CModel : public CScene3d
{
public:

	typedef struct
	{
		LPD3DXBUFFER pBuffMat;                        // マテリアル情報へのポインタ
		DWORD nNumMat;                                // マテリアル情報の数
		LPD3DXMESH pMesh;                             // メッシュ情報へのポインタ
		LPDIRECT3DTEXTURE9 pTexture[MAX_MATERIAL];    // テクスチャへのポインタ
		D3DXMATRIX mtxWorld;                          // ワールド情報
	} MODELDATA;

	CModel(int nPriority = 3);
	virtual ~CModel();
    virtual void	Draw(void);
    
	MODELDATA	GetModelData(void);					// モデルデータゲッター
	void		SetModelData(MODELDATA Model);		// モデルデータセッター
	float		GetAlphaValue(void);				// モデルカラーゲッター
	void		SetAlphaValue(float fAlphaValue);	// モデルカラーセッター

private:
    MODELDATA	m_ModelData;		// モデルデータ
	float		m_fAlphaValue;		// アルファ値
};
#endif
