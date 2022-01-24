//=============================================================================
//
// フェード処理 [fade.cpp]
// Author : 吉田悠人
//
//=============================================================================

#include"fade.h"
#include"manager.h"
#include"renderer.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CFade::CFade()
{
	m_pVtxBuff	= NULL;
	m_ModeNext	= GAME_MODE_TITLE;
	m_Fade		= FADE_NONE;
	m_Color		= D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

}

//=============================================================================
// デストラクタ
//=============================================================================
CFade::~CFade()
{
}

//=============================================================================
// 作成処理
//=============================================================================
CFade * CFade::Create(void)
{
	CFade *pFade = NULL;
	//インスタンス生成
	pFade = new CFade;

	//初期化処理
	if (pFade != NULL)
	{
		pFade->Init();
	}

	return pFade;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CFade::Init(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	//頂点バッファ生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);
	//頂点情報へのポインター
	VERTEX_2D *pVtx;
	
	m_Color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);//黒い画面（不透明）


	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標設定（右回りで設定する）
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	
	//rhwの設定（値は１，０で固定）
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点情報を設定
	pVtx[0].col = m_Color;
	pVtx[1].col = m_Color;
	pVtx[2].col = m_Color;
	pVtx[3].col = m_Color;
	
	//頂点データをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;


}

//=============================================================================
// 終了処理
//=============================================================================
void CFade::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CFade::Update(void)
{
	//頂点情報へのポインター
	VERTEX_2D *pVtx;

	//フェード処理中
	if (m_Fade != FADE_NONE)
	{
		//フェードイン処理
		if (m_Fade == FADE_IN)
		{
			m_Color.a -= FADE_RATE;//α値を減算して後ろの画面を浮き上がらせる

			if (m_Color.a <= 0.0f)
			{
				m_Color.a = 0.0f;
				//フェード処理終了
				m_Fade = FADE_NONE;
			}
		}
		//フェードアウト処理
		else if (m_Fade == FADE_OUT)
		{
			m_Color.a += FADE_RATE;//α値を加算して後ろの画面を消していく

			if (m_Color.a >= 1.0f)
			{
				m_Color.a = 1.0f;
				//フェードイン処理に切り替え
				m_Fade = FADE_IN;
				//モードを設定
				CManager::SetMode(m_ModeNext);
			}
		}
	}
	//頂点データの範囲をロックし、頂点バッファのポインタを習得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].col = m_Color;
	pVtx[1].col = m_Color;
	pVtx[2].col = m_Color;
	pVtx[3].col = m_Color;

	//頂点データをアンロック
	m_pVtxBuff->Unlock();
}

//=============================================================================
// 描画処理
//=============================================================================
void CFade::Draw(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	// テクスチャの設定
	pDevice->SetTexture(0, 0);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
// フェードの設定
//=============================================================================
void CFade::SetFade(GAME_MODE mode)
{
	m_Fade = FADE_OUT;
	m_ModeNext = mode;
}
