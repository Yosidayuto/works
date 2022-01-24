//=============================================================================
//
// チャイルド処理 [child.cpp]
// Author : 増澤 未来
//
//=============================================================================

//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "child.h"
#include "manager.h"
#include "inputcontroller.h"
#include "inputkeyboard.h"
#include "renderer.h"
#include "object.h"
#include "model.h"
#include "model object.h"
#include "game.h"
#include "player.h"
#include "item block base.h"
#include "stage1.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define OBJECT_FILE		("Data/Model/Player/player.x")	// ファイル名
#define OBJECT_HEIGHT   (50.0f)                             // 高さ 

//=============================================================================
// 静的メンバ変数初期化
//=============================================================================
CModel::MODELDATA CChild::m_modeldata = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CChild::CChild()
{
	//モデルデータの初期化
	SetObjType(OBJTYPE_PLAYER);
	m_model = NULL;
	m_modelPearent = NULL;
	m_bActive = false;
	m_bFlag = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CChild::~CChild()
{
}

//=============================================================================
// モデル読み込み関数
//=============================================================================
HRESULT CChild::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATERIAL *pMat = NULL;

	D3DXLoadMeshFromX(OBJECT_FILE, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_modeldata.pBuffMat, NULL, &m_modeldata.nNumMat, &m_modeldata.pMesh);

	if (m_modeldata.pBuffMat != NULL)
	{
		pMat = (D3DXMATERIAL *)m_modeldata.pBuffMat->GetBufferPointer();

		for (int nCountMat = 0; nCountMat < (int)m_modeldata.nNumMat; nCountMat++)
		{
			D3DXCreateTextureFromFile(pDevice, pMat[nCountMat].pTextureFilename, &m_modeldata.pTexture[nCountMat]);
		}
	}

	//ワールド変換行列の初期化
	D3DXMatrixIdentity(&m_modeldata.mtxWorld);

	return S_OK;
}

//=============================================================================
// モデル破棄関数
//=============================================================================
void CChild::Unload(void)
{
	if (m_modeldata.pBuffMat != NULL)
	{
		m_modeldata.pBuffMat->Release();
	}

	if (m_modeldata.pMesh != NULL)
	{
		m_modeldata.pMesh->Release();
	}

	for (int nCountTex = 0; nCountTex < MAX_MATERIAL; nCountTex++)
	{
		if (m_modeldata.pTexture[nCountTex] != NULL)
		{
			m_modeldata.pTexture[nCountTex]->Release();
		}
	}
}

//=============================================================================
// 生成関数
//=============================================================================
CChild * CChild::Create(CModel* modelPearent, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	//メモリ確保
	CChild* pChild = NULL;
	pChild = new CChild;

	//NULLチェック
	if (pChild != NULL)
	{
		//位置設定
		pChild->SetPosition(D3DXVECTOR3(0.0f,OBJECT_HEIGHT, 0.0f));
		//向き設定
		pChild->SetRotation(rot);
		//カラー設定
		pChild->SetScale(size);
		// 親モデルの登録
		pChild->m_modelPearent = modelPearent;
		//初期化処理
		pChild->Init();
	}

	return pChild;
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CChild::Init(void)
{
	// モデル生成
	m_model = new CModel;
	if (m_model != NULL)
	{
		m_model->SetPosition(GetPosition());
		m_model->SetRotation(GetRotation());
		m_model->SetScale(GetScale());
		m_model->Init();
	}

	SetPriority(PRIORITY_OBJECT_CHILD);
	m_model->SetPriority(PRIORITY_OBJECT_CHILD);

	m_bActive = false;

	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CChild::Uninit(void)
{
	//NULLチェック
	if (m_model != NULL)
	{
		m_model->Uninit();
	}

	Release();
}

//=============================================================================
// 更新関数
//=============================================================================
void CChild::Update(void)
{
	// アイテムとの当たり判定
	if (!m_bActive && !CPlayer::GetPlayer()->IsActiveMove()) CollisionItem();
}

//=============================================================================
// 描画関数
//=============================================================================
void CChild::Draw(void)
{
	if (m_modelPearent != NULL)
	{// 親モデルがNULLじゃないとき

		//デバイス情報の取得
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

		D3DXMATRIX mtxRot, mtxTrans, mtxScail;
		D3DMATERIAL9 matDef;	//現在のマテリアル保持用
		D3DXMATERIAL*pMat;	//マテリアルデータへのポインタ

		CModel::MODELDATA modelData = m_model->GetModelData();

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&modelData.mtxWorld);

		//サイズを反映
		D3DXMatrixScaling(&mtxScail, m_model->GetScale().x, m_model->GetScale().y, m_model->GetScale().z);
		D3DXMatrixMultiply(&modelData.mtxWorld, &modelData.mtxWorld, &mtxScail);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_model->GetRotation().y, m_model->GetRotation().x, m_model->GetRotation().z);
		D3DXMatrixMultiply(&modelData.mtxWorld, &modelData.mtxWorld, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, m_model->GetPosition().x, m_model->GetPosition().y, m_model->GetPosition().z);
		D3DXMatrixMultiply(&modelData.mtxWorld, &modelData.mtxWorld, &mtxTrans);

		CModel::MODELDATA modelDataPearent = m_modelPearent->GetModelData();
		// 親のワールドマトリックスをかける
		D3DXMatrixMultiply(&modelData.mtxWorld, &modelData.mtxWorld, &modelDataPearent.mtxWorld);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &modelData.mtxWorld);

		//現在のマテリアルを取得する
		pDevice->GetMaterial(&matDef);

		if (modelData.pBuffMat != NULL)
		{
			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)modelData.pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)modelData.nNumMat; nCntMat++)
			{
				//マテリアルのアンビエントにディフューズカラーを設定
				//pMat[nCntMat].MatD3D.Ambient = pMat[nCntMat].MatD3D.Diffuse;

				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				// テクスチャ
				pDevice->SetTexture(0, modelData.pTexture[nCntMat]);
				//モデルパーツの描画
				modelData.pMesh->DrawSubset(nCntMat);
			}
		}

		m_model->SetModelData(modelData);
	}
}

////=============================================================================
//// デバックこれで許して
////=============================================================================
//void CChild::FadeTalk(void)
//{
//	//if (CTalkbase::GetTalk() == CTalkbase::TALK_3)
//	//{
//	//	if (m_bFlag == true)
//	//	{
//	//		if (CStage1::GetTalkStage1() != nullptr)
//	//		{
//	//			CStage1::GetTalkStage1()->SetFlagTex(CTalkbase::TALK_4);
//	//		}
//	//	}
//	//}
//}



//=============================================================================
// アイテムとの当たり判定
//=============================================================================
void CChild::CollisionItem(void)
{
	// ワールド座標の取得
	CModel::MODELDATA modelData = m_model->GetModelData();
	D3DXVECTOR3 worldPos = D3DXVECTOR3(modelData.mtxWorld._41, modelData.mtxWorld._42, modelData.mtxWorld._43);

	CItemBlockBase * pItem = (CItemBlockBase*)(GetTop()[PRIORITY_OBJECT_ITEM]);

	while (pItem != NULL)
	{
		// アイテムの座標の取得
		D3DXVECTOR3 itemPos = pItem->GetPosition();
		// 距離の計算
		float fDitanse = sqrtf(powf(itemPos.x - worldPos.x, 2) + powf(itemPos.y - worldPos.y, 2) + powf(itemPos.z - worldPos.z, 2));
		// 球の当たり判定*半径ぴったりだとちょっとバグるので小さめに判定を取る(1.9f)
		if (fDitanse <= ITEM_HEIGHT *1.9f)
		{
			// 有効フラグを立てる
			m_bActive = true;
			// アイテムのモデルデータを自身のモデルデータに入れる
			m_model->SetModelData(pItem->GetModel()->GetModelData());
			// アイテムは消す
			pItem->Uninit();
			//アイテムタイプになる
			SetObjType(OBJTYPE_ITEM);
			// ループから抜ける
			break;
		}
		pItem  = (CItemBlockBase*)(pItem->GetNext());
	}
}

