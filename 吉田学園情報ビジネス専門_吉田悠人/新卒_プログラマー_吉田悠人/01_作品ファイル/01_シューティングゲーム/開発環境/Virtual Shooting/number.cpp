//=============================================================================
//ヘッダーファイル
//=============================================================================
#include "number.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
//=============================================================================
//静的メンバー変数
//=============================================================================
LPDIRECT3DTEXTURE9 CNumber::m_pTexture = NULL;

//=============================================================================
//コンストラクタ
//=============================================================================
CNumber::CNumber()
{
	m_pVtxBuff = NULL;
}

//=============================================================================
//デストラクタ
//=============================================================================
CNumber::~CNumber()
{
}
//=============================================================================
//テクスチャ読み込み
//=============================================================================
HRESULT CNumber::Load(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/number000.png", &m_pTexture);
	return S_OK;
}

//=============================================================================
//テクスチャの破棄
//=============================================================================
void CNumber::Unload(void)
{
	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
//生成処理
//=============================================================================
CNumber * CNumber::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//メモリ確保
	CNumber *pNumber=NULL;
	pNumber = new CNumber;
	
	//NULLチェック
	if (pNumber != NULL)
	{
		//位置設定
		pNumber->pos = pos;
		//サイズ設定
		pNumber->size = size;
		//初期化処理
		pNumber->Init();

	}
	return pNumber;
}

//=============================================================================
//初期化処理
//=============================================================================
HRESULT CNumber::Init(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,//バッファサイズ
		D3DUSAGE_WRITEONLY,//(固定)
		FVF_VERTEX_2D,//頂点フォーマット
		D3DPOOL_MANAGED,//（固定）
		&m_pVtxBuff,//変数名が変わると変更が必要
		NULL);
	VERTEX_2D *pVtx;//頂点情報へのポインター

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点バッファの生成
	pVtx[0].pos = D3DXVECTOR3(-size.x / 2 + pos.x, -size.y / 2 + pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(size.x / 2 + pos.x, -size.y / 2 + pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-size.x / 2 + pos.x, size.y / 2 + pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(size.x / 2 + pos.x, size.y / 2 + pos.y, 0.0f);

	// 頂点情報を設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//rhwの設定（値は１，０で固定）
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点データをアンロックする
	m_pVtxBuff->Unlock();
	CNumber::SetNumber(0);

	return S_OK;

}

//=============================================================================
//終了処理
//=============================================================================
void CNumber::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//=============================================================================
//更新処理
//=============================================================================
void CNumber::Update(void)
{
}

//=============================================================================
//描画処理
//=============================================================================
void CNumber::Draw(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}

//=============================================================================
//セット処理
//=============================================================================
void CNumber::SetNumber(int nNumber)
{
	VERTEX_2D *pVtx;//頂点情報へのポインター

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);	//頂点データをロック

	pVtx[0].tex = D3DXVECTOR2(0.0f+(0.1f* nNumber), 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f+(0.1f* nNumber), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f+(0.1f* nNumber), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f+(0.1f* nNumber), 1.0f);

	m_pVtxBuff->Unlock();						//頂点データをアンロックする

}

//=============================================================================
// カラーチェンジ処理
//=============================================================================
void CNumber::ColChange(D3DXCOLOR col)
{
	VERTEX_2D *pVtx;//頂点情報へのポインター

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);	//頂点データをロック

	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	m_pVtxBuff->Unlock();						//頂点データをアンロックする
}
