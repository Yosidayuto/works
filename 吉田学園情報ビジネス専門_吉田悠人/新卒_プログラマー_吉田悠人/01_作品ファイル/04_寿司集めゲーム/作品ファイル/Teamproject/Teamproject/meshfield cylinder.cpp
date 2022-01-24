//=============================================================================
//
// 円筒エフェクト処理 [effect_cylinder.cpp]
// Author : 林川紗梨夏
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "meshfield cylinder.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CYLINDER_Y_COUNT (4)
#define CYLINDER_X_COUNT (10)
#define CYLINDER_NUM_VERTEX ((CYLINDER_X_COUNT + 1) * (CYLINDER_Y_COUNT + 1))//頂点数
#define CYLINDER_NUM_INDEX (((CYLINDER_X_COUNT + 1)*2)*CYLINDER_Y_COUNT + (CYLINDER_Y_COUNT - 1)*2)//インデックス数
#define CYLINDER_NUM_PRIMITIVE (CYLINDER_X_COUNT*CYLINDER_Y_COUNT * 2)+((CYLINDER_Y_COUNT-1) * 4)	
//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CEffectCylinder::CEffectCylinder(int nPriority) : CScene3d(nPriority)
{
	m_pTexture = NULL;							//テクスチャへのポインタ
	m_pVtxBuff = NULL;							//頂点バッファへのポインタ
	m_Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//頂点カラー							//縮尺
	memset(m_mtxWorld, NULL, sizeof(m_mtxWorld));
}

//=============================================================================
// デストラクタ
//=============================================================================
CEffectCylinder::~CEffectCylinder()
{
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CEffectCylinder::Init(void)
{
	SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	D3DXVECTOR3 nor;//ほう
	
	//レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();

	//デバイスにレンダラーのデバイスを代入
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	SetObjType(CScene::OBJTYPE_NONE);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*CYLINDER_NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	// 頂点情報を設定
	VERTEX_3D *pVtx;

	WORD * pIdx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	int nIndex = 0;
	int nTexIndex = 0;
	for (int vIndex = 0; vIndex < CYLINDER_Y_COUNT + 1; vIndex++)
	{
		nTexIndex = 0;
		for (int hIndex = 0; hIndex < CYLINDER_X_COUNT + 1; hIndex++)
		{
			float fAngle = (float)hIndex * 360.0f / (float)CYLINDER_X_COUNT;
			pVtx[nIndex].pos = D3DXVECTOR3(sinf(D3DXToRadian(-fAngle))*(GetSize().x / 2),
				(-vIndex * (GetSize().y / CYLINDER_Y_COUNT)) + (GetSize().y / 2),
				cosf(D3DXToRadian(fAngle))*(GetSize().z / 2));
			//法線正規化
			D3DXVec3Normalize(&nor, &GetRot());
			// 法線の設定
			pVtx[nIndex].nor = -GetRot();
			// 頂点カラーの設定
			pVtx[nIndex].col = m_Col;
			// テクスチャ座標の設定
			pVtx[nIndex].tex = D3DXVECTOR2((float)nTexIndex, (float)vIndex);
			nIndex++;
			nTexIndex++;
		}
	}

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();

	// インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(VERTEX_3D)*CYLINDER_NUM_INDEX, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pIdxBuff, NULL);
	// インデックスバッファをロックし、頂点情報へのポインタを取得
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);
	nIndex = 0;
	for (int vIndex = 0; vIndex < CYLINDER_Y_COUNT + 1; vIndex++)
	{
		for (int hIndex = 0; hIndex < CYLINDER_X_COUNT + 1; hIndex++)
		{
			pIdx[nIndex] = (CYLINDER_X_COUNT + 1) + (nIndex / 2) - vIndex;
			pIdx[nIndex + 1] = (nIndex / 2) - vIndex;
			nIndex += 2;
		}
	}

	//頂点バッファのアンロック
	m_pIdxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CEffectCylinder::Uninit(void)
{
	//CScene3d::Uninit();
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	Release();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CEffectCylinder::Update(void)
{
	// 頂点情報を設定
	VERTEX_3D *pVtx;

	WORD * pIdx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	int nIndex = 0;
	int nTexIndex = 0;
	for (int vIndex = 0; vIndex < CYLINDER_Y_COUNT + 1; vIndex++)
	{
		float fAngleY = vIndex * 180.0f / CYLINDER_Y_COUNT;
		nTexIndex = 0;
		for (int hIndex = 0; hIndex < CYLINDER_X_COUNT + 1; hIndex++)
		{
			float fAngle = hIndex * 360.0f / CYLINDER_X_COUNT;
			pVtx[nIndex].pos = D3DXVECTOR3(cosf(D3DXToRadian(fAngleY))* (GetSize().y / 2)*sinf(D3DXToRadian(fAngle)),
				sinf(D3DXToRadian(fAngleY)) * (GetSize().y / 2),
				cosf(D3DXToRadian(fAngleY)) * (GetSize().y / 2)*cosf(D3DXToRadian(fAngle)));
			//法線正規化
			D3DXVec3Normalize(&pVtx[nIndex].nor, &GetRot());
			// 法線の設定
			pVtx[nIndex].nor = -GetRot();
			// 頂点カラーの設定
			pVtx[nIndex].col = m_Col;
			// テクスチャ座標の設定
			pVtx[nIndex].tex = D3DXVECTOR2(nTexIndex, (float)vIndex);
			nIndex++;
			nTexIndex++;
		}
	}

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();

	// インデックスバッファをロックし、頂点情報へのポインタを取得
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);
	nIndex = 0;
	for (int vIndex = 0; vIndex < CYLINDER_Y_COUNT + 1; vIndex++)
	{
		for (int hIndex = 0; hIndex < CYLINDER_X_COUNT + 1; hIndex++)
		{
			pIdx[nIndex] = (CYLINDER_X_COUNT + 1) + (nIndex / 2) - vIndex;
			pIdx[nIndex + 1] = (nIndex / 2) - vIndex;
			nIndex += 2;
		}
	}

	//頂点バッファのアンロック
	m_pIdxBuff->Unlock();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CEffectCylinder::Draw(void)
{
	//レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	//デバイスにレンダラーのデバイスを代入
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	//アルファテストを有効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//アルファテスト基準値の設定
	pDevice->SetRenderState(D3DRS_ALPHAREF, 100);
	//アルファテストの比較方法の設定（GREATERは基準値より大きい場合)
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;
	ZeroMemory(&matDef, sizeof(matDef));
	//ワールドマトリクス初期化
	D3DXMatrixIdentity(&m_mtxWorld);
	//向き反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, D3DXToRadian(GetRot().y), D3DXToRadian(GetRot().x), D3DXToRadian(GetRot().z));
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	//位置反映
	D3DXMatrixTranslation(&mtxTrans, GetPos().x, GetPos().y, GetPos().z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
	//ワールドマトリクス
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(m_pIdxBuff);
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	//色セット
	matDef.Ambient = m_Col;
	pDevice->SetMaterial(&matDef);
	//頂点フォーマット設定
	pDevice->SetFVF(FVF_VERTEX_3D);
	//テクスチャセット
	pDevice->SetTexture(0, m_pTexture);
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, CYLINDER_NUM_VERTEX, 0, CYLINDER_NUM_PRIMITIVE);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	//保持していたマテリアルを元に戻す
	ZeroMemory(&matDef, sizeof(matDef));
	pDevice->SetMaterial(&matDef);
	//アルファテストを無効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=============================================================================
// テクスチャの割り当て関数
//=============================================================================
void CEffectCylinder::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	//テクスチャの割り当て
	m_pTexture = pTexture;
}

//=============================================================================
// 頂点カラー設定関数
//=============================================================================
void CEffectCylinder::SetColor(D3DXCOLOR Col)
{
	//カラーの割り当て
	m_Col = Col;
}
