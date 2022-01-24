//=============================================================================
//
//	モデルデータ処理[model.cpp]
//	Author:吉田悠人
//
//=============================================================================

//=============================================================================
// ヘッダーファイル
//=============================================================================
#include "model.h"
#include "main.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
//コンストラクタ
//=============================================================================
CModel::CModel(int nPriority):CScene3d(nPriority)
{
    //モデルデータの初期化
    ZeroMemory(&m_ModelData, sizeof(m_ModelData));
	SetObjType(OBJTYPE_MODEL);
	m_fAlphaValue = 1.0f;	//カラー
}

//=============================================================================
//デストラクタ
//=============================================================================
CModel::~CModel()
{

}


//=============================================================================
//描画処理
//=============================================================================
void CModel::Draw(void)
{
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
    D3DMATERIAL9 matDef;
    D3DXMATERIAL* pMat;
	
	//行列計算用
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;
	//ワールド変換行列の初期化
	D3DXMatrixIdentity(&m_ModelData.mtxWorld);

	//拡大縮小行列の生成と計算
	D3DXMatrixScaling(&mtxScale, GetSize().x, GetSize().y, GetSize().z);
	D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxScale);

	//回転行列の生成と計算
	D3DXMatrixRotationYawPitchRoll(&mtxRot, GetRot().y, GetRot().x, GetRot().z);
	D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxRot);

	//平行移動行列の生成と計算
	D3DXMatrixTranslation(&mtxTrans, GetPos().x, GetPos().y, GetPos().z);
	D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxTrans);

	//計算結果を適用
	pDevice->SetTransform(D3DTS_WORLD, &m_ModelData.mtxWorld);


    //マテリアル情報の取得
    pDevice->GetMaterial(&matDef);

    if(m_ModelData.pBuffMat != NULL)
    {
        pMat = (D3DXMATERIAL*)m_ModelData.pBuffMat->GetBufferPointer();
    }

    //マテリアル情報の設定とマテリアルごとに描画
    for(int nCntMat = 0; nCntMat < (int)m_ModelData.nNumMat; nCntMat++)
    {
		//アルファ値設定
		pMat[nCntMat].MatD3D.Diffuse.a = m_fAlphaValue;
		//マテリアルの設定
        pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		// テクスチャ
        pDevice->SetTexture(0, m_ModelData.pTexture[nCntMat]);
		//モデルパーツの描画
        m_ModelData.pMesh->DrawSubset(nCntMat);
    }

    //マテリアル情報のリセット
    pDevice->SetMaterial(&matDef);
}

//=============================================================================
// モデルデータゲッター
//=============================================================================
CModel::MODELDATA CModel::GetModelData(void)
{
    return m_ModelData;
}

//=============================================================================
// モデルデータセッター
//=============================================================================
void CModel::SetModelData(MODELDATA Model)
{
	m_ModelData = Model;
}

//=============================================================================
// モデルカラーゲッター
//=============================================================================
float CModel::GetAlphaValue(void)
{
	return m_fAlphaValue;
}

//=============================================================================
// モデルカラーセッター
//=============================================================================
void CModel::SetAlphaValue(float fAlphaValue)
{
	m_fAlphaValue = fAlphaValue;
}
