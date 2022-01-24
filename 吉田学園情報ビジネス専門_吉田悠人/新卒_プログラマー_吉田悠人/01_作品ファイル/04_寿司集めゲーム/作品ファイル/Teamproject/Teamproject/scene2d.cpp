//=============================================================================
//
// 2Dシーン管理処理 [scene2d.cpp]
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
#include "scene2d.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CScene2d::CScene2d(int nPriority) :CScene(nPriority)
{
	m_pTexture = NULL;							//テクスチャへのポインタ
	m_pVtxBuff = NULL;							//頂点バッファへのポインタ
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//座標
	m_Size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//サイズ
	m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向き

	m_aTex[0] = D3DXVECTOR2(0.0f, 0.0f);		//テクスチャ座標
	m_aTex[1] = D3DXVECTOR2(1.0f, 0.0f);
	m_aTex[2] = D3DXVECTOR2(0.0f, 1.0f);
	m_aTex[3] = D3DXVECTOR2(1.0f, 1.0f);		

	m_Col = D3DCOLOR_RGBA(255, 255, 255, 255);	//頂点カラー
	m_fScale = 1.0f;								//縮尺
	m_fAngle = 0.0f;								//角度
	m_fLength = 0.0f;								//長さ
}

//=============================================================================
// デストラクタ
//=============================================================================
CScene2d::~CScene2d()
{
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CScene2d::Init(void)
{
	//レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();

	//デバイスにレンダラーのデバイスを代入
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	SetObjType(CScene::OBJTYPE_NONE);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	// 頂点情報を設定
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//角度の設定
	m_fLength = sqrtf((float)(((m_Size.x / 2) * (m_Size.x / 2)) + ((m_Size.y / 2) * (m_Size.y / 2))));

	//長さの設定
	m_fAngle = atan2f((m_Size.y / 2), (m_Size.x / 2));

	//頂点座標の設定
	pVtx[0].pos.x = m_Pos.x - cosf(m_fAngle - m_Rot.z) * m_fLength * m_fScale;
	pVtx[0].pos.y = m_Pos.y - sinf(m_fAngle - m_Rot.z) * m_fLength * m_fScale;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_Pos.x + cosf(m_fAngle + m_Rot.z) * m_fLength * m_fScale;
	pVtx[1].pos.y = m_Pos.y - sinf(m_fAngle + m_Rot.z) * m_fLength * m_fScale;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_Pos.x - cosf(m_fAngle + m_Rot.z) * m_fLength * m_fScale;
	pVtx[2].pos.y = m_Pos.y + sinf(m_fAngle + m_Rot.z) * m_fLength * m_fScale;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_Pos.x + cosf(m_fAngle - m_Rot.z) * m_fLength * m_fScale;
	pVtx[3].pos.y = m_Pos.y + sinf(m_fAngle - m_Rot.z) * m_fLength * m_fScale;
	pVtx[3].pos.z = 0.0f;

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

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
void CScene2d::Uninit(void)
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
void CScene2d::Update(void)
{
	// 頂点情報を設定
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//角度の設定
	m_fLength = sqrtf((float)(((m_Size.x / 2) * (m_Size.x / 2)) + ((m_Size.y / 2) * (m_Size.y / 2))));
	//長さの設定
	m_fAngle = atan2f((m_Size.y / 2), (m_Size.x / 2));

	//頂点座標の設定
	pVtx[0].pos.x = m_Pos.x - cosf(m_fAngle - m_Rot.z) * m_fLength * m_fScale;
	pVtx[0].pos.y = m_Pos.y - sinf(m_fAngle - m_Rot.z) * m_fLength * m_fScale;

	pVtx[1].pos.x = m_Pos.x + cosf(m_fAngle + m_Rot.z) * m_fLength * m_fScale;
	pVtx[1].pos.y = m_Pos.y - sinf(m_fAngle + m_Rot.z) * m_fLength * m_fScale;

	pVtx[2].pos.x = m_Pos.x - cosf(m_fAngle + m_Rot.z) * m_fLength * m_fScale;
	pVtx[2].pos.y = m_Pos.y + sinf(m_fAngle + m_Rot.z) * m_fLength * m_fScale;

	pVtx[3].pos.x = m_Pos.x + cosf(m_fAngle - m_Rot.z) * m_fLength * m_fScale;
	pVtx[3].pos.y = m_Pos.y + sinf(m_fAngle - m_Rot.z) * m_fLength * m_fScale;

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
void CScene2d::Draw(void)
{
	//レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();

	//デバイスにレンダラーのデバイスを代入
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//アルファテストの設定
	pDevice->SetRenderState(D3DRS_ALPHAREF, (DWORD)0x00000001);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);


}

//=============================================================================
// テクスチャの割り当て関数
//=============================================================================
void CScene2d::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	//テクスチャの割り当て
	m_pTexture = pTexture;
}

//=============================================================================
// 座標設定関数
//=============================================================================
void CScene2d::SetPos(D3DXVECTOR3 Pos)
{
	//座標の割り当て
	m_Pos = Pos;
}

//=============================================================================
// サイズ設定関数
//=============================================================================
void CScene2d::SetSize(D3DXVECTOR3 Size)
{
	//サイズの割り当て
	m_Size = Size;
}

//=============================================================================
// 向き設定関数
//=============================================================================
void CScene2d::SetRot(D3DXVECTOR3 Rot)
{
	//向きの割り当て
	m_Rot = Rot;
}

//=============================================================================
// テクスチャのUV座標設定関数
//=============================================================================
void CScene2d::SetTexture(D3DXVECTOR2 aTex[NUM_VERTEX])
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
void CScene2d::SetColor(D3DXCOLOR Col)
{
	//カラーの割り当て
	m_Col = Col;
}

//=============================================================================
// 縮尺設定関数
//=============================================================================
void CScene2d::SetScale(float fScale)
{
	//縮尺の割り当て
	m_fScale = fScale;
}
