//----------------------------------------------
//ヘッダーファイル
//----------------------------------------------
#include "result.h"
#include "result bg.h"
#include "inputmouse.h"
#include "fade.h"
#include "score.h"
#include "ui count.h"
#include "sound.h"
#include "manager.h"
#include<thread>
//----------------------------------
//静的メンバー変数
//----------------------------------
char * CResult::pTexture[STAGE_TYPE_MAX]=
{
	"data/TEXT/ranking1.txt",
	"data/TEXT/ranking2.txt",
	"data/TEXT/ranking3.txt",
};
//---------------------------------
//コンストラクタ
//---------------------------------
CResult::CResult(int nPriorit) :CScene(nPriorit)
{
	for (int nCount = 0; nCount < MAX_RANKING; nCount++)
	{
		nScoreData[nCount]=NULL;
		m_Score[nCount] = NULL;
		m_pUiCount[nCount] = NULL;
	}
	nScore = 0;
}

//---------------------------------
//デストラクタ
//---------------------------------
CResult::~CResult()
{
}

//---------------------------------
//生成処理
//---------------------------------
CResult * CResult::Create(STAGE_TYPE stage)
{
	//メモリ確保
	CResult *pResult = NULL;
	pResult = new CResult;

	//NULLチェック
	if (pResult != NULL)
	{
		pResult->m_Stage = stage;

		//初期化処理
		pResult->Init();

	}
	return pResult;
}

//---------------------------------
//初期化処理
//---------------------------------
HRESULT CResult::Init(void)
{
	//サウンドクラス受け取り
	CSound *pSound = CManager::GetSound();
	//サウンドの停止
	pSound->Stop();

	//サウンドの再生
	pSound->Play(CSound::LABEL_BGM_RANKING);


	//スコアを受け取る
	nScore = CManager::GetScore();
	//データ読み込み
	ReadFile(m_Stage);
	//データ追加
	int nRanking = SetRanking(nScore, m_Stage);
	//クリエイト処理

	//背景
	CResultBg::Create();
	//スコア生成
	for (int nCount = 0; nCount < MAX_RANKING; nCount++)
	{
		if (nCount<=4)
		{
			m_pUiCount[nCount] = CUiCount::Create(D3DXVECTOR3(180.0f, 235.0f + ((float)(nCount) * 100.0f), 0.0f), D3DXVECTOR3(40.0f, 80.0f, 0.0f), PRIORITY_RESULT);
			m_Score[nCount] = CScore::Create(D3DXVECTOR3(220.0f,200.0f+((float)(nCount)*100.0f),0.0f), D3DXVECTOR3(40.0f,80.0f,0.0f), false, PRIORITY_RESULT);
		}
		else
		{
			m_pUiCount[nCount] = CUiCount::Create(D3DXVECTOR3(700.0f, 235.0f + (((float)(nCount)-5.0f) * 100.0f), 0.0f), D3DXVECTOR3(40.0f, 80.0f, 0.0f), PRIORITY_RESULT);
			m_Score[nCount] = CScore::Create(D3DXVECTOR3(740.0f, 200.0f + (((float)(nCount)-5.0f) * 100.0f), 0.0f), D3DXVECTOR3(40.0f, 80.0f, 0.0f), false, PRIORITY_RESULT);
		}

		//スコアセット
		m_Score[nCount]->SetScore(nScoreData[nCount]);
		//ランキング順位セット
		m_pUiCount[nCount]->SetCount(nCount + 1);
		
		//ランクインしたら
		if (nCount== (nRanking - 1))
		{
			//赤くする
			m_Score[(nRanking - 1)]->ColChange(D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
			m_pUiCount[(nRanking - 1)]->SetCol(D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));

		}
	}
	return S_OK;
}

//---------------------------------
//終了処理
//---------------------------------
void CResult::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_RANKING; nCount++)
	{
		m_pUiCount[nCount]->Uninit();
	}
	//シーン破棄
	Release();
}

//---------------------------------
//更新処理
//---------------------------------
void CResult::Update(void)
{
	CInihMouse*	pMouse	= CManager::GetMouse();		//マウス取得
	CFade*		pFade	= CManager::GetFade();		//フェード取得	
	
	if (pMouse->GetClickTrigger(CLICK_LEFT) == true  )
	{
		if(m_Stage == STAGE_TYPE_3)
		{
			pFade->SetFade(GAME_MODE_CLEAR);
		}
		else	
		{
			pFade->SetFade(GAME_MODE_SELECT);
		}

	}
}

//---------------------------------
//描画処理
//---------------------------------
void CResult::Draw(void)
{
	for (int nCount = 0; nCount < MAX_RANKING; nCount++)
	{
		m_pUiCount[nCount]->Draw();
	}
}

//---------------------------------
//ランキングデータ読み込み関数
//---------------------------------
void CResult::ReadFile(STAGE_TYPE Stage)
{
	FILE *pFile;

	fopen_s(&pFile, pTexture[Stage], "r");	//テキストファイル読み込み
	if (pFile != NULL)
	{
		for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
		{
			fscanf_s(pFile, "%d", &nScoreData[nCount]);
		}
		fclose(pFile);
	}


}

//---------------------------------
//ランキングデータ書き込み関数
//---------------------------------
void CResult::WriteFile(STAGE_TYPE Stage)
{
	FILE *pFile;

	fopen_s(&pFile, pTexture[Stage], "w");	//テキストファイル書き込み

	if (pFile != NULL)
	{
		for (int nCount = 0; nCount < MAX_RANKING; nCount++)
		{
			fprintf(pFile, "%d\n", nScoreData[nCount]);
		}
		fclose(pFile);

	}


}

//---------------------------------
//ランキングデータの追加
//---------------------------------
int CResult::SetRanking(int nScore, STAGE_TYPE Stage)
{
	for (int nCount = 0; nCount < MAX_RANKING; nCount++)
	{
		if (nScoreData[nCount] < nScore)
		{
			//以前のランキングデータを後ろに移動
			for (int nCntMove = MAX_RANKING - 1; nCntMove > nCount; nCntMove--)
			{
				//ずらす
				nScoreData[nCntMove] = nScoreData[nCntMove - 1];
			}
			//そこに入れる
			nScoreData[nCount] = nScore;
			WriteFile(Stage);
			return nCount + 1;
		}
	}
	return 11;
}
