//=============================================================================
//
// トラップ [trap.h]
// Author : 吉田悠人
//
//=============================================================================
#ifndef _TRAP_H_
#define _TRAP_H_
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "model.h"
#include "meshfield_cylinder.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CModel;
class CMesh_Cylinder;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CTrap :public CMeshCylinder
{
public:
	CTrap();

	static CTrap* Create(D3DXVECTOR3 Startpos,D3DXVECTOR3 Endpos);

	void Update(void);

	BOOL Search(CModel::MODELDATA modeldata, float &fDistanve);
private:

	LPDIRECT3DTEXTURE9		m_pTexture;		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;		//インデックスバッファへのポイント
	D3DXMATRIX m_mtxWorld;					//行列計算用
	CMesh_Cylinder *m_pMeshCylinder;		//メッシュフィールド円柱のポイント
	D3DXVECTOR3 m_Startpos;					//スタートのpos
	D3DXVECTOR3 m_Endpos;					//終わりのpos
};
#endif