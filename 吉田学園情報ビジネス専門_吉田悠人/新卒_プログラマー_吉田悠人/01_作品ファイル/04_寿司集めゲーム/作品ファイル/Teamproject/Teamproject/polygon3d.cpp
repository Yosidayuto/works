//=============================================================================
//
// 3Dシーン管理処理 [scene3d.cpp]
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
#include "polygon3d.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CPolygon3d::CPolygon3d(int nPriority) :CScene3d(nPriority)
{
	m_pTexture = nullptr;							//テクスチャへのポインタ
	m_pVtxBuff = nullptr;							//頂点バッファへのポインタ

	m_aTex[0] = D3DXVECTOR2(0.0f, 0.0f);
	m_aTex[1] = D3DXVECTOR2(1.0f, 0.0f);
	m_aTex[2] = D3DXVECTOR2(0.0f, 1.0f);
	m_aTex[3] = D3DXVECTOR2(1.0f, 1.0f);//テクスチャ座標

	m_Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//頂点カラー
	m_fScale = 1.0f;								//縮尺
	m_fAngle = 0.0f;								//角度
	m_fLength = 0.0f;								//長さ
	memset(m_mtxWorld, NULL, sizeof(m_mtxWorld));
}

//=============================================================================
// デストラクタ
//=============================================================================
CPolygon3d::~CPolygon3d()
{
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CPolygon3d::Init(void)
{
	//レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();

	//デバイスにレンダラーのデバイスを代入
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	SetObjType(CScene::OBJTYPE_NONE);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	// 頂点情報を設定
	VERTEX_3D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//角度の設定
	m_fLength = sqrtf((float)(((GetSize().x / 2) * (GetSize().x / 2)) + ((GetSize().y / 2) * (GetSize().y / 2))));

	//長さの設定
	m_fAngle = atan2f((GetSize().y / 2), (GetSize().x / 2));

	//頂点座標の設定
	pVtx[0].pos.x = -cosf(m_fAngle) * m_fLength * m_fScale;
	pVtx[0].pos.y = -sinf(m_fAngle) * m_fLength * m_fScale;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = +cosf(m_fAngle) * m_fLength * m_fScale;
	pVtx[1].pos.y = -sinf(m_fAngle) * m_fLength * m_fScale;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = -cosf(m_fAngle) * m_fLength * m_fScale;
	pVtx[2].pos.y = +sinf(m_fAngle) * m_fLength * m_fScale;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = +cosf(m_fAngle) * m_fLength * m_fScale;
	pVtx[3].pos.y = +sinf(m_fAngle) * m_fLength * m_fScale;
	pVtx[3].pos.z = 0.0f;

	// ほうせんの設定
	pVtx[0].nor = D3DXVECTOR3(0, 1, 0);
	pVtx[1].nor = D3DXVECTOR3(0, 1, 0);
	pVtx[2].nor = D3DXVECTOR3(0, 1, 0);
	pVtx[3].nor = D3DXVECTOR3(0, 1, 0);

	// 頂点カラーの設定
	pVtx[0].col = m_Col;
	pVtx[1].col = m_Col;
	pVtx[2].col = m_Col;
	pVtx[3].col = m_Col;

	// テクスチャ座標の設定
	pVtx[0].tex = m_aTex[0];
	pVtx[1].tex = m_aTex[1];
	pVtx[2].tex = m_aTex[2];
	pVtx[3].tex = m_aTex[3];

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CPolygon3d::Uninit(void)
{
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
void CPolygon3d::Update(void)
{
	// 頂点情報を設定
	VERTEX_3D *pVtx;

	//角度の設定
	m_fLength = sqrtf((float)(((GetSize().x / 2) * (GetSize().x / 2)) + ((GetSize().y / 2) * (GetSize().y / 2))));

	//長さの設定
	m_fAngle = atan2f((GetSize().y / 2), (GetSize().x / 2));

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos.x = -cosf(m_fAngle) * m_fLength  * m_fScale;
	pVtx[0].pos.y = -sinf(m_fAngle) * m_fLength * m_fScale;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = +cosf(m_fAngle) * m_fLength * m_fScale;
	pVtx[1].pos.y = -sinf(m_fAngle) * m_fLength * m_fScale;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = -cosf(m_fAngle) * m_fLength * m_fScale;
	pVtx[2].pos.y = +sinf(m_fAngle) * m_fLength * m_fScale;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = +cosf(m_fAngle) * m_fLength * m_fScale;
	pVtx[3].pos.y = +sinf(m_fAngle) * m_fLength * m_fScale;
	pVtx[3].pos.z = 0.0f;

	// ほうせんの設定
	pVtx[0].nor = D3DXVECTOR3(0, 1, 0);
	pVtx[1].nor = D3DXVECTOR3(0, 1, 0);
	pVtx[2].nor = D3DXVECTOR3(0, 1, 0);
	pVtx[3].nor = D3DXVECTOR3(0, 1, 0);

	// 頂点カラーの設定
	pVtx[0].col = m_Col;
	pVtx[1].col = m_Col;
	pVtx[2].col = m_Col;
	pVtx[3].col = m_Col;

	// テクスチャ座標の設定
	pVtx[0].tex = m_aTex[0];
	pVtx[1].tex = m_aTex[1];
	pVtx[2].tex = m_aTex[2];
	pVtx[3].tex = m_aTex[3];

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CPolygon3d::Draw(void)
{
	//レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();

	//デバイスにレンダラーのデバイスを代入
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	D3DMATERIAL9 matDef;
	ZeroMemory(&matDef, sizeof(matDef));
	D3DXMATRIX mtxRot, mtxTrans;
	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixRotationYawPitchRoll(&mtxRot, GetRot().y, GetRot().x, GetRot().z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	D3DXMatrixTranslation(&mtxTrans, GetPos().x, GetPos().y, GetPos().z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	pDevice->SetTexture(0, m_pTexture);

	//色セット
	matDef.Ambient = m_Col;
	pDevice->SetMaterial(&matDef);
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	pDevice->SetFVF(FVF_VERTEX_3D);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	//保持していたマテリアルを元に戻す
	ZeroMemory(&matDef, sizeof(matDef));
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// テクスチャの割り当て関数
//=============================================================================
void CPolygon3d::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	//テクスチャの割り当て
	m_pTexture = pTexture;
}

//=============================================================================
// テクスチャのUV座標設定関数
//=============================================================================
void CPolygon3d::SetTexture(D3DXVECTOR2 aTex[NUM_VERTEX])
{
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		//テクスチャのUV座標の割り当て
		m_aTex[nCount] = aTex[nCount];
	}
}

//=============================================================================
// 頂点カラー設定関数
//=============================================================================
void CPolygon3d::SetColor(D3DXCOLOR Col)
{
	//カラーの割り当て
	m_Col = Col;
}

//=============================================================================
// 縮尺設定関数
//=============================================================================
void CPolygon3d::SetScale(float fScale)
{
	//縮尺の割り当て
	m_fScale = fScale;
}
