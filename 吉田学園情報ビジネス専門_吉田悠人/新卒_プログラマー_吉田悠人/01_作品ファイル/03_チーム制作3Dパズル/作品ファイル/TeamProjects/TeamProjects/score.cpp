//=============================================================================
//
// スコア処理 [score.cpp]
// Author : 吉田 悠人
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "score.h"		
#include "manager.h"	
#include "object2d.h"	
#include "renderer.h"	
#include "number.h"		
//=============================================================================
//マクロ定義
//=============================================================================
#define MAX_TEXTURE 10
#define NUMBER_SIZE_X (200.0f,20.0f)
#define NUMBER_SIZE_Y 45.0f

//=============================================================================
// コンストラクタ
//=============================================================================
CScore::CScore(int nPriorit) :CObject2D(nPriorit)
{
	//タイプ処理
	CObject2D::SetObjType(CObject2D::OBJTYPE_NONE);
	m_nScore = 0;
}

//=============================================================================
// 生成処理
//=============================================================================
CScore * CScore::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//メモリ確保
	CScore *pScore = NULL;
	pScore = new CScore();

	if (pScore != NULL)
	{
		//位置処理
		pScore->SetPos(pos);
		//サイズ処理
		pScore->SetSize(size);
		//初期化処理
		pScore->Init();
	}
	
	return pScore;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CScore::Init()
{
	//位置取得
	D3DXVECTOR3 pos = GetPos();
	//サイズ取得
	D3DXVECTOR3 size = GetSize();

	//ナンバー生成
	for (int nCount = 0; nCount < MAX_SCORE; nCount++)
	{
		m_apNumber[nCount] = CNumber::Create
		(D3DXVECTOR3(
			(nCount*size.x + size.x / 2) + pos.x,pos.y,0.0f),
			D3DXVECTOR3(size.x, size.y, 0.0f));
	}
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CScore::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_SCORE; nCount++)
	{
		if (m_apNumber[nCount] != NULL)
		{
			m_apNumber[nCount]->Uninit();
		}
	}

	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CScore::Update(void)
{
	//ナンバーの更新処理
	for (int nCount = 0; nCount < MAX_SCORE; nCount++)
	{
		if (m_apNumber[nCount] != NULL)
		{
			m_apNumber[nCount]->Update();
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CScore::Draw(void)
{
	//ナンバーの描画処理
	for (int nCount = 0; nCount < MAX_SCORE; nCount++)
	{
		if (m_apNumber[nCount] != NULL)
		{
			m_apNumber[nCount]->Draw();

		}
	}
}

//=============================================================================
// スコアセッター
//=============================================================================
void CScore::SetScore(int nScore)
{
	//現在のスコア
	m_nScore = nScore;
	//指数　(スコア表示用)
	float fIndex;			
	//基数　(スコア表示用)
	float fRadix = 10.0f;	

	for (fIndex = 0; fIndex < MAX_SCORE; fIndex++)
	{
		int nScore = (int)powf(fRadix, MAX_SCORE - fIndex);
		int nScore2 = (int)powf(fRadix, MAX_SCORE - fIndex - 1);
		int nAnswer = m_nScore % nScore / nScore2;
		m_apNumber[(int)fIndex]->SetNumber(nAnswer);
	}
}

//=============================================================================
// カラーチェンジ
//=============================================================================
void CScore::ColChange(D3DXCOLOR col)
{
	//ナンバーのカラーチェンジ
	for (int nCount = 0; nCount < MAX_SCORE; nCount++)
	{
		m_apNumber[nCount]->ColChange(col);
	}
}

//=============================================================================
// スコア加算
//=============================================================================
void CScore::AddScore(int nValue)
{
	//スコア加算
	m_nScore += nValue;
	//指数　(スコア表示用)
	float fIndex;			
	//基数　(スコア表示用)
	float fRadix = 10.0f;	

	for (fIndex = 0; fIndex < MAX_SCORE; fIndex++)
	{
		int nScore = (int)powf(fRadix, MAX_SCORE - fIndex);
		int nScore2 = (int)powf(fRadix, MAX_SCORE - fIndex - 1);
		int nAnswer = m_nScore % nScore / nScore2;
		m_apNumber[(int)fIndex]->SetNumber(nAnswer);
	}
}

//=============================================================================
// スコアゲッター
//=============================================================================
int CScore::GetScore(void)
{
	return m_nScore;
}
