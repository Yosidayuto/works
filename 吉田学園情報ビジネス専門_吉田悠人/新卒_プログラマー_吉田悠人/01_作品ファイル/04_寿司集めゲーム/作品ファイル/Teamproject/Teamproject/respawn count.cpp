//=============================================================================
//
// リスポーンカウントUI処理 [respawn count.cpp]
// Author : 吉田悠人
//
//=============================================================================
//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "respawn count.h"
#include "renderer.h"
#include "manager.h"
#include "number.h"
//=============================================================================
// コンストラクタ
//=============================================================================
CRespawnCount::CRespawnCount(int nPriority):CScene(nPriority)
{
	SetObjType(CScene::OBJTYPE_NONE);
	m_nControl = 0;
	memset(m_pNumber, 0, sizeof(m_pNumber));
}

//=============================================================================
// デストラクタ
//=============================================================================
CRespawnCount::~CRespawnCount()
{
}

//=============================================================================
// 生成処理関数
//=============================================================================
CRespawnCount * CRespawnCount::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size)
{
	//メモリ確保
	CRespawnCount *pRespawnCount = nullptr;
	pRespawnCount = new CRespawnCount;

	//NULLチェック
	if (pRespawnCount != nullptr)
	{
		pRespawnCount->m_Pos = Pos;		//位置設定
		pRespawnCount->m_Size = Size;	//サイズ設定
		pRespawnCount->Init();			//初期化処理
	}

	return pRespawnCount;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CRespawnCount::Init(void)
{
	//ナンバーの生成処理
	for (int nCntNum = 0; nCntNum < MAX_NUMBER; nCntNum++)
	{
		m_pNumber[nCntNum] = CNumber::Create(D3DXVECTOR3(m_Pos.x - (m_Size.x * nCntNum), m_Pos.y, 0.0f), m_Size.x, m_Size.y);
	}
	//数値のセット
	SetControl(m_nControl);
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CRespawnCount::Uninit(void)
{
	//ナンバーの終了処理
	for (int nCntNum = 0; nCntNum < MAX_NUMBER; nCntNum++)
	{
		m_pNumber[nCntNum]->Uninit();
		delete m_pNumber[nCntNum];
		m_pNumber[nCntNum] = NULL;
	}
	Release();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CRespawnCount::Update(void)
{
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CRespawnCount::Draw(void)
{
	//レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	//デバイスにレンダラーのデバイスを代入
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//アルファテストを有効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//アルファテスト基準値の設定
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	//アルファテストの比較方法の設定
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	//ナンバーの描画処理
	for (int nCntNum = 0; nCntNum < MAX_NUMBER; nCntNum++)
	{
		m_pNumber[nCntNum]->Draw();
	}

	//アルファテストを無効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=============================================================================
// カウントセット関数
//=============================================================================
void CRespawnCount::SetControl(int nControl)
{
	m_nControl = nControl;
	int integer = 0;//計算用変数
	int nCntNumber = 0;

	for (int nCntDigit = 1; nCntDigit <= MAX_NUMBER; nCntDigit++, nCntNumber++)
	{
		integer = int(m_nControl / pow(10, nCntDigit)); //1の位以下を切り捨てる
		integer = int(integer * pow(10, nCntDigit));
		m_pNumber[nCntNumber]->SetNumber(int((m_nControl - integer) / pow(10, nCntDigit - 1)));
	}
}
