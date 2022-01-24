//=============================================================================
//
// スコア管理処理 [score.cpp]
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
#include "score.h"
#include <cmath>

//=============================================================================
// コンストラクタ
//=============================================================================
CScore::CScore(int nPriority) : CScene(nPriority)
{
	memset(m_apNumber, 0, sizeof(m_apNumber));
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	m_nScore = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CScore::~CScore()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CScore::Init(void)
{
	SetObjType(CScene::OBJTYPE_NONE);
	for (int nCntNum = 0; nCntNum < MAX_DIGITS; nCntNum++)
	{
		m_apNumber[nCntNum] = CNumber::Create(D3DXVECTOR3(m_Pos.x - (m_Size.x * nCntNum), m_Pos.y, 0.0f), m_Size.x, m_Size.y);
	}
	SetScore(m_nScore);
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CScore::Uninit(void)
{
	for (int nCntNum = 0; nCntNum < MAX_DIGITS; nCntNum++)
	{
		m_apNumber[nCntNum]->Uninit();
		delete m_apNumber[nCntNum];
		m_apNumber[nCntNum] = NULL;
	}
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CScore::Update(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void CScore::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	for (int nCntNum = 0; nCntNum < MAX_DIGITS; nCntNum++)
	{
		m_apNumber[nCntNum]->Draw();
	}
}

//=============================================================================
// 生成処理
//=============================================================================
CScore * CScore::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size)
{
	CScore *pScore = NULL;

	if (pScore == NULL)
	{
		pScore = new CScore;
		pScore->m_Pos = Pos;
		pScore->m_Size = Size;
		pScore->Init();
	}

	return pScore;
}

//=============================================================================
// スコアセット
//=============================================================================
void CScore::SetScore(int nScore)
{
	m_nScore = nScore;
	int integer = 0;//計算用変数
	int nCntNumber = 0;

	for (int nCntDigit = 1; nCntDigit <= MAX_DIGITS; nCntDigit++, nCntNumber++)
	{
		integer = int(m_nScore / pow(10, nCntDigit)); //1の位以下を切り捨てる
		integer = int(integer * pow(10, nCntDigit));
		m_apNumber[nCntNumber]->SetNumber(int((m_nScore - integer) / pow(10, nCntDigit - 1)));
	}
}

//=============================================================================
// スコア加算
//=============================================================================
void CScore::AddScore(int nValue)
{
	m_nScore += nValue;
	SetScore(m_nScore);
}
