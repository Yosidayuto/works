//=============================================================================
//
// ステージ処理 [stage.cpp]
// Author : 吉田悠人
//
//=============================================================================
//=============================================================================
//インクルードファイル
//=============================================================================
#include "stage.h"
#include "scene.h"
#include "sound.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "result.h"
#include "warning.h"
#include "score.h"
#include<thread>
//=============================================================================
// 静的メンバー変数
//=============================================================================
char* CStage::pFileName[STAGE_TYPE_MAX] = {
"data/TEXT/stage1.csv", 
"data/TEXT/stage2.csv",
""};
STAGE_DATA CStage::m_Stage[STAGE_TYPE_MAX] = {};
//=============================================================================
// コンストラクト
//=============================================================================
CStage::CStage()
{
	m_nCountEnemy = 0;
}

//=============================================================================
// デストラクト
//=============================================================================
CStage::~CStage()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CStage::Init(void)
{

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CStage::Uninit(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void CStage::Update(void)
{
	//カウント
	EnemeyCreate();
}

//=============================================================================
// リザルト
//=============================================================================
void CStage::Result(STAGE_TYPE stage)
{
	//スコアセット
	CManager::SetScore(CGame::GetScore()->GetScore());
	//ステージセット
	CGame::SetStageType((STAGE_TYPE)(stage + 1));
	//リザルト表示
	CResult::Create(stage);

}

//=============================================================================
// エネミー出現までのカウント
//=============================================================================
void CStage::SetEnemyCount(int nConut)
{
	m_nCountEnemy = nConut;
}

//=============================================================================
// スコアポインタセッター
//=============================================================================
void CStage::SetScore(CScore * pScore)
{
	m_pScore = pScore;
}

//=============================================================================
// エネミー出現までのカウント
//=============================================================================
void CStage::EnemeyCreate(void)
{
	//ボスが出現しているか
	if (!BossSearch())
	{
		m_nCountEnemy--;
	}

	//カウントが0になったら
	if (m_nCountEnemy <= 0)
	{
		//ステージを進める
		StageMode();
	}

}

//=============================================================================
// ステージエネミーの情報ロード
//=============================================================================
void CStage::LoadEnemyData(void)
{
	//ファイルポインタ
	FILE*	pFile[STAGE_TYPE_MAX];
	//読み込み用のデータ
	char cFileString[256];
	//文字認識
	int nFile;
	//列
	int nCol = 1;
	//行
	int nRow = 0;
	//フェース数
	int nPhase = 0;
	//エネミー数
	int nEnemy = 0;

	memset(cFileString, 0, sizeof(cFileString));
	//テキストファイル読み込み
	for (int nStage = 0; nStage < STAGE_TYPE_MAX; nStage++)
	{
		//ファイル読み込み
		fopen_s(&pFile[nStage], pFileName[nStage], "r");
		//フェーズ数の初期化
		nPhase = 0;
		//エクセルのセル初期化
		nCol = 1;
		nRow = 0;
		//エネミー数の初期化
		nEnemy = 0;

		if (pFile[nStage] != NULL)
		{
			//ヘッダー読み飛ばし
			while(fgetc(pFile[nStage]) != '\n');

			while (1)
			{
				while (1) 
				{
					nFile = fgetc(pFile[nStage]);

					//末尾ならループを抜ける。
					if (nFile == EOF)
					{
						goto out;
					}
					//カンマか改行でなければ、文字としてつなげる
					if (nFile != ',' && nFile != '\n')
					{
						strcat_s(cFileString, (const char*)&nFile);
					}
					//カンマか改行ならループ抜ける。
					else
					{
						break;
					}
				}

				if (strcmp(cFileString, "PHASE_END") != 0)
				{
					//文字列読み込み
					switch (nCol)
					{
						//1列目は敵種類を表す。atoi関数で数値として代入。
					case 1: m_Stage[nStage].Phase[nPhase].EnemySpawn[nEnemy].EnemyType = (ENEMY_TYPE)atoi(cFileString); break;
						//2列目は行動パターン。	
					case 2: m_Stage[nStage].Phase[nPhase].EnemySpawn[nEnemy].EnemyMovePattern = (ENEMY_MOVE_PATTERN)atoi(cFileString); break;
						//3列目は攻撃パターン
					case 3: m_Stage[nStage].Phase[nPhase].EnemySpawn[nEnemy].EnemyAttack = (ENEMY_ATTACK_PATTERN)atoi(cFileString); break;
						//4列目は出撃までの時間
					case 4: m_Stage[nStage].Phase[nPhase].EnemySpawn[nEnemy].nSpwan = atoi(cFileString); break;
						//5列目はアクションまでのカウント
					case 5: m_Stage[nStage].Phase[nPhase].EnemySpawn[nEnemy].nActionTime = atoi(cFileString); break;
						//6列目は攻撃のカウント
					case 6: m_Stage[nStage].Phase[nPhase].EnemySpawn[nEnemy].nAttackTime = atoi(cFileString); break;
						//7列目は最初のXの出現位置
					case 7: m_Stage[nStage].Phase[nPhase].EnemySpawn[nEnemy].nReturnTime = atoi(cFileString); break;
						//8列目は最初のXの出現位置
					case 8: m_Stage[nStage].Phase[nPhase].EnemySpawn[nEnemy].pos.x = (float)atoi(cFileString) + STAGE_POS; break;
						//9列目は最初のYの出現位置
					case 9: m_Stage[nStage].Phase[nPhase].EnemySpawn[nEnemy].pos.y = (float)atoi(cFileString); break;
						//10列目はスピード
					case 10: m_Stage[nStage].Phase[nPhase].EnemySpawn[nEnemy].fSpeed =(float)atoi(cFileString); break;
						//11列目は体力+エネミー数のカウント
					case 11:
						m_Stage[nStage].Phase[nPhase].EnemySpawn[nEnemy].nLife = atoi(cFileString); 
						nEnemy++;
						break;
					}

				}
				else
				{

					//フェーズ移行のカウント取得
					fscanf_s(pFile[nStage], " %d", &m_Stage[nStage].Phase[nPhase].nPhaseCount);
					//エネミー数取得
					m_Stage[nStage].Phase[nPhase].nEnemyCount = nEnemy;
					//エネミー数の初期化
					nEnemy = 0;
					//フェーズのカウント
					nPhase++;
					
					//改行
					nRow++;
					nCol = 0;

				}
				//バッファの初期化
				memset(cFileString, 0, sizeof(cFileString));
				//列数を足す
				nCol++;

				//もし読み込んだ文字が改行だったら列数を初期化して行数を増やす
				if (nFile == '\n')
				{
					nCol = 1;
					nRow++;
				}

			}
			out:										//末尾ならここに跳ぶ
			m_Stage[nStage].nCountPhase = nPhase;		//最大フェーズを取得
			fclose(pFile[nStage]);						//ファイルを閉じる
		}
	}
}

//=============================================================================
// ステージ情報ゲッター
//=============================================================================
STAGE_DATA CStage::GetStageEnemy(STAGE_TYPE stage)
{
	return m_Stage[stage];
}

//=============================================================================
// ボスがいるか
//=============================================================================
bool CStage::BossSearch(void)
{
	//オブジェクト取得用
	CScene* pTop[PRIORITY_MAX] = {};
	//次チェックするオブジェクトのポインタ
	CScene* pNext = NULL;

	//topのアドレスを取得
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		pTop[nCount] = *(CScene::GetTop() + nCount);
	}

	//ボス索敵処理
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		if (pTop[nCount] != NULL)
		{
			pNext = pTop[nCount];
			//その描画優先度のオブジェクトがなくなるまでループ
			while (pNext != NULL)
			{
				//ボスがいた場合
				if (pNext->GetObjType() == CScene::OBJ_TYPE_BOSS)
				{

					return true;
				}
				
				//次のオブジェクトのポインタを更新
				pNext = pNext->GetNext();
			}
		}
	}
	//ボスがいない場合
	return false;
}


//=============================================================================
// ボス演出生成
//=============================================================================
void CStage::WarningCreate(void)
{
	//サウンドポインタ取得
	CSound *pSound = CManager::GetSound();

	//サウンドストップ
	pSound->Stop();
	//ワーニング生成
	CWarning::Create(D3DXVECTOR3(STAGE_POS, SCREEN_HEIGHT / 2, 0.0f));

}

