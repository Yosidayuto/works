//=============================================================================
//
// ビルボード [billboard.cpp]
// Author : 吉田悠人
//
//=============================================================================

//=============================================================================
// ヘッダーファイル
//=============================================================================
#include "billboard.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CBillboard::CBillboard(int nPriority) : CScene3d(nPriority)
{
	m_pTexture	= NULL;
	m_pVtxBuff	= NULL;
	m_col		= D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
}

//=============================================================================
// デストラクタ
//=============================================================================
CBillboard::~CBillboard()
{

}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CBillboard::Init(void)
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	
	// 頂点情報
	VERTEX_3D *pVtx = NULL;

	//大きさ取得
	D3DXVECTOR3 size = GetSize();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);
	
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(-size.x / 2, size.y / 2, +size.z / 2);
	pVtx[1].pos = D3DXVECTOR3(size.x / 2, size.y / 2, +size.z / 2);
	pVtx[2].pos = D3DXVECTOR3(-size.x / 2, -size.y / 2, +size.z / 2);
	pVtx[3].pos = D3DXVECTOR3(size.x / 2, -size.y / 2, +size.z / 2);

	pVtx[0].nor = D3DXVECTOR3(0, 0, -1);
	pVtx[1].nor = D3DXVECTOR3(0, 0, -1);
	pVtx[2].nor = D3DXVECTOR3(0, 0, -1);
	pVtx[3].nor = D3DXVECTOR3(0, 0, -1);

	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CBillboard::Update(void)
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点情報
	VERTEX_3D *pVtx = NULL;

	//大きさ取得
	D3DXVECTOR3 size = GetSize();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(-size.x / 2, size.y / 2, +size.z / 2);
	pVtx[1].pos = D3DXVECTOR3(size.x / 2, size.y / 2, +size.z / 2);
	pVtx[2].pos = D3DXVECTOR3(-size.x / 2, -size.y / 2, +size.z / 2);
	pVtx[3].pos = D3DXVECTOR3(size.x / 2, -size.y / 2, +size.z / 2);

	pVtx[0].nor = D3DXVECTOR3(0, 0, -1);
	pVtx[1].nor = D3DXVECTOR3(0, 0, -1);
	pVtx[2].nor = D3DXVECTOR3(0, 0, -1);
	pVtx[3].nor = D3DXVECTOR3(0, 0, -1);

	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	m_pVtxBuff->Unlock();

}

//=============================================================================
// 終了処理関数
//=============================================================================
void CBillboard::Uninit(void)
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
// 描画処理関数
//=============================================================================
void CBillboard::Draw(void)
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX	 mtxRot, mtxTrans;	// 行列計算用のマトリクス
	D3DMATERIAL9 matDef;			// マテリアル用
	D3DXVECTOR3  pos = GetPos();	// 位置取得
	
	//テクスチャセット
	pDevice->SetTexture(0, m_pTexture);
	//アルファテスト有効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//アルファテスト基準値の設定
	pDevice->SetRenderState(D3DRS_ALPHAREF, 100);
	//アルファテストの比較方法の設定（GREATERは基準値より大きい場合）
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//ワールドマトリクスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//回転の逆行列
	pDevice->GetTransform(D3DTS_VIEW, &mtxRot);
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxRot);
	m_mtxWorld._41 = 0;
	m_mtxWorld._42 = 0;
	m_mtxWorld._43 = 0;

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//マテリアル情報
	ZeroMemory(&matDef, sizeof(matDef));
	matDef.Ambient.r = m_col.r;
	matDef.Ambient.g = m_col.g;
	matDef.Ambient.b = m_col.b;
	matDef.Ambient.a = m_col.a;	//マテリアルセット
	pDevice->SetMaterial(&matDef);

	//ポリゴン描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);   //数値
	pDevice->SetTexture(0, NULL);

	//アルファテスト無効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_AMBIENT, 0x44444444);
	ZeroMemory(&matDef, sizeof(matDef));
	pDevice->SetMaterial(&matDef);


}

//=============================================================================
// カラーセッター関数
//=============================================================================
void CBillboard::SetColor(D3DXCOLOR col)
{
	m_col = col;
}

//=============================================================================
// テクスチャ設定関数
//=============================================================================
void CBillboard::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}
