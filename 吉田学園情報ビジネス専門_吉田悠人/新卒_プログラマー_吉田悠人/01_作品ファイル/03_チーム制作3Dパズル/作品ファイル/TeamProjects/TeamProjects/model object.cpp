//=============================================================================
//
//	モデルオブジェクト[model object.cpp]
//	Author:吉田悠人
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "model object.h"
#include "main.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CModelObject::CModelObject()
{
	//モデルデータの初期化
	SetObjType(OBJTYPE_NONE);
	ZeroMemory(&m_ModelData, sizeof(m_ModelData));

}

//=============================================================================
// デストラクタ
//=============================================================================
CModelObject::~CModelObject()
{

}

//=============================================================================
// 生成処理
//=============================================================================
CModelObject * CModelObject::Create(MODELDATA Data, CObject * pParentObject, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	// メモリの確保
	CModelObject* pModelObje = NULL;
	pModelObje = new CModelObject;

	if (pModelObje != NULL)
	{
		//各種情報の設定
		pModelObje->SetPosition(pos);
		pModelObje->SetRotation(rot);
		pModelObje->SetScale(size);
		pModelObje->m_ModelData = Data;
		// 初期化処理
		pModelObje->Init();
	}

	return pModelObje;
}

//=============================================================================
//初期化処理
//=============================================================================
HRESULT CModelObject::Init(void)
{
	CModel::Init();
	return S_OK;
}

//=============================================================================
//終了処理
//=============================================================================
void CModelObject::Uninit(void)
{
	CModel::Uninit();
	Release();
}

//=============================================================================
//更新処理
//=============================================================================
void CModelObject::Update(void)
{
}

//=============================================================================
//描画処理
//=============================================================================
void CModelObject::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//行列計算用
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;
	//ワールド変換行列の初期化
	D3DXMatrixIdentity(&m_ModelData.mtxWorld);

	//拡大縮小行列の生成と計算
	D3DXMatrixScaling(&mtxScale, GetScale().x, GetScale().y, GetScale().z);
	D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxScale);

	//回転行列の生成と計算
	D3DXMatrixRotationYawPitchRoll(&mtxRot, GetRotation().y, GetRotation().x, GetRotation().z);
	D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxRot);

	//平行移動行列の生成と計算
	D3DXMatrixTranslation(&mtxTrans, GetPosition().x, GetPosition().y, GetPosition().z);
	D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxTrans);
	
	//計算結果を適用
	pDevice->SetTransform(D3DTS_WORLD, &m_ModelData.mtxWorld);

	SetModelData(m_ModelData);

	//描画処理
	CModel::Draw();
}
