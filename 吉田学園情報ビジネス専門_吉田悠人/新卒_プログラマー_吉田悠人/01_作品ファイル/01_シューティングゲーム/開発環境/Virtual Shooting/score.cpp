//=============================================================================
//ヘッダーファイル
//=============================================================================
#include "score.h"		
#include "manager.h"	
#include "scene2d.h"	
#include "renderer.h"	
#include "number.h"		
#include "score bar.h"
//=============================================================================
//マクロ定義
//=============================================================================
#define MAX_TEXTURE 10
#define NUMBER_SIZE_X (200.0f,20.0f)
#define NUMBER_SIZE_Y 45.0f

//=============================================================================
//コンストラクタ
//=============================================================================
CScore::CScore(int nPriorit) :CScene(nPriorit)
{
	//タイプ処理
	CScene::SetObjType(CScene::OBJ_TYPE_NONE);
	m_pScoreBar = NULL;
	UiSwitch = false;
}

//=============================================================================
//デストラクタ
//=============================================================================
CScore::~CScore()
{

}
//=============================================================================
//生成処理
//=============================================================================
CScore * CScore::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, bool UI, PRIORITY priority)
{
	//メモリ確保
	CScore* pScore = NULL;
	pScore = new CScore(priority);
	
	//NULLチェック
	if (pScore != NULL)
	{
		pScore->m_pos = pos;
		pScore->m_size = size;
		pScore->UiSwitch = UI;
		pScore->Init();

	}
	return pScore;
}

//=============================================================================
//初期化処理
//=============================================================================
HRESULT CScore::Init()
{

	m_nScore = 0;
	for (int nCount = 0; nCount < MAX_SCORE; nCount++)
	{
		m_apNumber[nCount] = CNumber::Create
		(D3DXVECTOR3(
			(nCount*m_size.x + m_size.x / 2) + m_pos.x,
			(m_pos.y + m_size.y /1.5f),
			0.0f),
			D3DXVECTOR3(m_size.x, m_size.y, 0.0f));
	}
	if (UiSwitch == true)
	{
		m_pScoreBar = CScoreBar::Create
		(D3DXVECTOR3(m_pos.x + (m_size.x*(float)(MAX_SCORE) / 2.0f), m_pos.y + (m_size.y / 2.0f), 0.0f),
			D3DXVECTOR3(m_size.x*((float)(MAX_SCORE)*1.5f), m_size.y*1.5f, 0.0f));
	}

	return S_OK;
}

//=============================================================================
//終了処理
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
//更新処理
//=============================================================================
void CScore::Update(void)
{
	for (int nCount = 0; nCount < MAX_SCORE; nCount++)
	{
		if (m_apNumber[nCount] != NULL)
		{
			m_apNumber[nCount]->Update();
		}
	}

}

//=============================================================================
//描画処理
//=============================================================================
void CScore::Draw(void)
{

	for (int nCount = 0; nCount < MAX_SCORE; nCount++)
	{
		if (m_apNumber[nCount] != NULL)
		{
			m_apNumber[nCount]->Draw();

		}
	}


}

//=============================================================================
// スコアセット処理
//=============================================================================
void CScore::SetScore(int nScore)
{
	m_nScore = nScore;
	float fIndex;			//指数　(スコア表示用)
	float fRadix = 10.0f;	//基数　(スコア表示用)
	int nCount = 0;
	for (fIndex = 0; fIndex < MAX_SCORE; fIndex++)
	{
		int nScore = (int)powf(fRadix, MAX_SCORE - fIndex);
		int nScore2 = (int)powf(fRadix, MAX_SCORE - fIndex - 1);
		int nAnswer = m_nScore % nScore / nScore2;

		m_apNumber[(int)fIndex]->SetNumber(nAnswer);
	}
}

//=============================================================================
// スコアカラー変更処理
//=============================================================================
void CScore::ColChange(D3DXCOLOR col)
{
	for (int nCount = 0; nCount < MAX_SCORE; nCount++)
	{
		m_apNumber[nCount]->ColChange(col);
	}
}

//=============================================================================
// スコア加算処理
//=============================================================================
void CScore::AddScore(int nValue)
{
	m_nScore += nValue;
	float fIndex;			//指数　(スコア表示用)
	float fRadix = 10.0f;	//基数　(スコア表示用)
	int nCount = 0;
	for (fIndex = 0; fIndex < MAX_SCORE; fIndex++)
	{
		int nScore = (int)powf(fRadix, MAX_SCORE - fIndex);
		int nScore2 = (int)powf(fRadix, MAX_SCORE - fIndex - 1);
		int nAnswer = m_nScore % nScore / nScore2;

		m_apNumber[(int)fIndex]->SetNumber(nAnswer);
	}
}

//=============================================================================
// スコアゲッター処理
//=============================================================================
int CScore::GetScore(void)
{
	return m_nScore;
}
