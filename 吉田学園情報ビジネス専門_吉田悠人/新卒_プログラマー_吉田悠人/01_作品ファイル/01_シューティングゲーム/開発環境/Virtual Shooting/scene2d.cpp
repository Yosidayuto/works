//=============================================================================
//
//	2Dシーン[scene2d.h]
//	Author:吉田　悠人
//
//=============================================================================

#include"scene2d.h"
#include"manager.h"
#include"input.h"
#include"renderer.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CScene2d::CScene2d(int nPriorit):CScene(nPriorit)
{
	m_Texture	= NULL;					// テクスチャへのポインタ
	m_pVtxBuff	= NULL;					// 頂点バッファへのポインタ
	m_pos		= D3DXVECTOR3(0, 0, 0); // ポリゴンの位置
	m_fRot		= 0.0f;					// ポリゴンの向き
	m_col		= D3DCOLOR_RGBA(255, 255, 255, 255);
}

//=============================================================================
// デストラクタ
//=============================================================================
CScene2d::~CScene2d()
{

}

//=============================================================================
// 生成処理
//=============================================================================
CScene2d *CScene2d::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float frot, LPDIRECT3DTEXTURE9 pTexture, int nPriority)
{
	CScene2d *pScene2d=NULL;
	pScene2d = new CScene2d(nPriority);
	
	//NULLチェック
	if (pScene2d != NULL)
	{
		//位置設定
		pScene2d->SetPos(pos);
		//大きさ設定
		pScene2d->SetSize(size);
		//向き設定
		pScene2d->SetRot(frot);
		//テクスチャの設定
		pScene2d->BindTexture(pTexture);
		//初期化処理
		pScene2d->Init();

		return pScene2d;
	}
	return NULL;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CScene2d::Init(void)
{
	//頂点情報へのポインター
	VERTEX_2D *pVtx;
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,			//バッファサイズ
		D3DUSAGE_WRITEONLY,				//(固定)
		FVF_VERTEX_2D,					//頂点フォーマット
		D3DPOOL_MANAGED,				//（固定）
		&m_pVtxBuff,					//変数名が変わると変更が必要
		NULL);

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点情報を設定
	pVtx[0].pos = m_pos + D3DXVECTOR3((float)-m_size.x / 2, (float)-m_size.y / 2, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3((float)m_size.x / 2, (float)-m_size.y / 2, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3((float)-m_size.x / 2, (float)m_size.y / 2, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3((float)m_size.x / 2, (float)m_size.y / 2, 0.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0, 0);
	pVtx[1].tex = D3DXVECTOR2(1, 0);
	pVtx[2].tex = D3DXVECTOR2(0, 1);
	pVtx[3].tex = D3DXVECTOR2(1, 1);

	//rhwの設定（値は１，０で固定）
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	
	// 頂点情報を設定
	pVtx[0].col = m_col;    //aは透明度
	pVtx[1].col = m_col;    //aは透明度
	pVtx[2].col = m_col;    //aは透明度
	pVtx[3].col = m_col;    //aは透明度

	//頂点データをアンロックする
	m_pVtxBuff->Unlock();


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CScene2d::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	//オブジェクトの破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CScene2d::Update(void)
{
	D3DXMATRIX posMatrix;       // 頂点行列
	D3DXMATRIX rotateMatrix;    // 回転行列
	VERTEX_2D* pVtx;

	//行列の初期化（単位行列生成）
	D3DXMatrixIdentity(&posMatrix);
	D3DXMatrixIdentity(&rotateMatrix);

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標更新
	pVtx[0].pos = D3DXVECTOR3((float)-m_size.x / 2, (float)-m_size.y / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3((float)m_size.x / 2, (float)-m_size.y / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3((float)-m_size.x / 2, (float)m_size.y / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3((float)m_size.x / 2, (float)m_size.y / 2, 0.0f);

	//頂点カラー更新
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	m_pVtxBuff->Unlock();

	//回転行列生成
	D3DXMatrixRotationZ(&rotateMatrix, D3DXToRadian(m_fRot));

	for (int nCount = 0; nCount < 4; nCount++)
	{
		//頂点座標を行列に変換
		D3DXMatrixTranslation(&posMatrix, pVtx[nCount].pos.x, pVtx[nCount].pos.y, pVtx[nCount].pos.z);
		//回転行列を行列にかける
		posMatrix *= rotateMatrix;
		//回転後の座標を頂点座標に入れる
		pVtx[nCount].pos.x = posMatrix._41;
		pVtx[nCount].pos.y = posMatrix._42;
		pVtx[nCount].pos.z = posMatrix._43;
		//m_pos分移動させる
		pVtx[nCount].pos += m_pos;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CScene2d::Draw(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_Texture);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
// 位置セッター関数
//=============================================================================
void CScene2d::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// 向きセッター関数
//=============================================================================
void CScene2d::SetRot(float frot)
{
	m_fRot = frot;
}

//=============================================================================
// サイズセッター関数
//=============================================================================
void CScene2d::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

//=============================================================================
// カラーセッター関数
//=============================================================================
void CScene2d::SetCol(D3DXCOLOR col)
{
	m_col = col;
}

//=============================================================================
// 位置ゲッター関数
//=============================================================================
D3DXVECTOR3 CScene2d::GetPos(void)
{
	return m_pos;
}

//=============================================================================
// サイズゲッター関数
//=============================================================================
D3DXVECTOR3 CScene2d::GetSize(void)
{
	return m_size;
}

//=============================================================================
// 向きゲッター関数
//=============================================================================
float CScene2d::GetRot(void)
{
	return m_fRot;
}

//=============================================================================
// カラーゲッター関数
//=============================================================================
D3DXCOLOR CScene2d::GetCol(void)
{
	return m_col;
}

//=============================================================================
//テクスチャのセット関数
//=============================================================================
void CScene2d::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	//テクスチャの割り当て
	m_Texture = pTexture;
}

//=============================================================================
// テクスチャアニメーション関数
//=============================================================================
void CScene2d::TextureAnim(D3DXVECTOR2 *Texture)//sizeは１/テクスチャの分割数
{
	VERTEX_2D *pVtx;//頂点情報へのポインター

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);	//頂点データをロック

	pVtx[0].tex = Texture[0];
	pVtx[1].tex = Texture[1];
	pVtx[2].tex = Texture[2];
	pVtx[3].tex = Texture[3];

	m_pVtxBuff->Unlock();						//頂点データをアンロックする
}
