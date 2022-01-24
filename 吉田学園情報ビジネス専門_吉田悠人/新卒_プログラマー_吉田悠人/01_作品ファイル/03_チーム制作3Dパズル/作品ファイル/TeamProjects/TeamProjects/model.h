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
#include "main.h"
#include "object3d.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define MAX_MATERIAL (30)
//=============================================================================
//クラス定義
//=============================================================================
class CModel : public CObject3D
{
public:

	typedef struct
	{
		LPD3DXBUFFER pBuffMat;                        // マテリアル情報へのポインタ
		DWORD nNumMat;                                // マテリアル情報の数
		LPD3DXMESH pMesh;                             // メッシュ情報へのポインタ
		LPDIRECT3DTEXTURE9 pTexture[MAX_MATERIAL];    // テクスチャへのポインタ
		D3DXMATRIX mtxWorld;                          // アニメーション情報
	} MODELDATA;

    CModel();
    virtual ~CModel();
    virtual HRESULT Init(void);
    virtual void	Uninit(void);
    virtual void	Update(void);
    virtual void	Draw(void);
    
	MODELDATA	GetModelData(void);				//モデルデータゲッター
	void		SetModelData(MODELDATA Model);	//モデルデータセッター

private:
    MODELDATA m_ModelData;		//モデルデータ
    CObject* m_pParentObject;	//
};
#endif
