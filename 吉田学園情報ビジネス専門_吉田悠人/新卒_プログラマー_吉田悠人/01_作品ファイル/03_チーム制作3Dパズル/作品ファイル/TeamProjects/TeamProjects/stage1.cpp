//=============================================================================
//
// ステージ1 [stage1.cpp]
// Author : 吉田悠人
//
//=============================================================================
//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "stage1.h"
#include "manager.h"
#include "fade.h"
#include "inputkeyboard.h"
#include "game.h"
#include "player.h"
#include "red sand block.h"
#include "hole block.h"
#include "garbage block.h"
#include "luggage block.h"
#include "building block.h"
#include "building break block.h"
#include <stdio.h>
#include "talk_stage1.h"
#include "sound.h"
#include "sea.h"
#include "camera.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define STAGENUMBER_POS_X	(1100.0f)	//ステージナンバー用の位置
#define STAGENUMBER_POS_Y	(80.0f)		//ステージナンバー用の位置
#define STAGENUMBER_SIZE_X	(150.0f)	//ステージナンバー用のサイズ
#define STAGENUMBER_SIZE_Y	(50.0f)		//ステージナンバー用のサイズ

//=============================================================================
// 静的メンバー変数
//=============================================================================
char* CStage1::m_pFileName = "Data/Text/stage_1.csv";
MAP_DATA CStage1::m_pMapData = {};
CTalkStage1* CStage1::m_pTalkStage1 = nullptr;

//=============================================================================
// コンストラクタ
//=============================================================================
CStage1::CStage1()
{
}
//=============================================================================
// デストラクタ
//=============================================================================
CStage1::~CStage1()
{

}

//=============================================================================
// ロード関数
//=============================================================================
void CStage1::Load(void)
{
	//ファイルポインタ
	FILE*	pFile;
	//読み込み用データ
	char cFileString[258];
	//文字認識
	int nFileText;
	//列、行
	int nCol, nRow;
	//ブロック数
	int nBlock;
	//初期化
	pFile = NULL;
	nCol = 1;
	nRow = 0;
	nBlock = 0;
	memset(cFileString, 0, sizeof(cFileString));

	//ファイル読み込み
	fopen_s(&pFile, m_pFileName, "r");

	if (pFile != NULL)
	{
		//ヘッダー読み飛ばし
		while (fgetc(pFile) != '\n');

		while (1)
		{
			while (1)
			{
				nFileText = fgetc(pFile);

				//末尾ならループを抜ける。
				if (nFileText == EOF)
				{
					goto out;
				}
				//カンマか改行でなければ、文字としてつなげる
				if (nFileText != ',' && nFileText != '\n')
				{
					strcat_s(cFileString, (const char*)&nFileText);
				}
				//カンマか改行ならループ抜ける。
				else
				{
					break;
				}
			}
			//文字列読み込み
			switch (atoi(cFileString))
			{
			case 0:
				//ブロックタイプ記憶
				m_pMapData.BlockData[nRow].nBlockType[nCol] = BLOCK_TYPE_NONE;
				break;

			case 1:
				//ブロックタイプ記憶
				m_pMapData.BlockData[nRow].nBlockType[nCol] = BLOCK_TYPE_START;
				break;
			case 2:
				//ブロックタイプ記憶
				m_pMapData.BlockData[nRow].nBlockType[nCol] = BLOCK_TYPE_GOAL;
				break;
			case 3:
				//ブロックタイプ記憶
				m_pMapData.BlockData[nRow].nBlockType[nCol] = BLOCK_TYPE_TILE_RED_SAMD;
				break;
			case 4:
				//ブロックタイプ記憶
				m_pMapData.BlockData[nRow].nBlockType[nCol] = BLOCK_TYPE_HINDRANCE_BUILDING_1;
				break;
			case 5:
				//ブロックタイプ記憶
				m_pMapData.BlockData[nRow].nBlockType[nCol] = BLOCK_TYPE_HINDRANCE_BUILDING_2;
				break;
			case 6:
				//ブロックタイプ記憶
				m_pMapData.BlockData[nRow].nBlockType[nCol] = BLOCK_TYPE_ITEM_GARBAGE;
				break;
				
			}
			//バッファの初期化
			memset(cFileString, 0, sizeof(cFileString));
			//列数を足す
			nCol++;

			//もし読み込んだ文字が改行だったら列数を初期化して行数を増やす
			if (nFileText == '\n')
			{
				//行数保存
				m_pMapData.BlockData[nRow].nStageSizeX = nCol;
				//行数初期化
				nCol = 1;
				//列の進行
				nRow++;
			}

		}
		out:							//末尾ならここに跳ぶ
		m_pMapData.nStageSizeY = nRow;	//ブロック数を保存
		fclose(pFile);					//ファイルを閉じる
	}
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CStage1::Init(void)
{
	//カメラの注視位置
	CManager::GetCamera()->SetPos(D3DXVECTOR3(-275,0.0f,300.0f));
	// 海の生成
	CSea::Create(D3DXVECTOR3(0.0f, -70.0f, 0.0f), 0.002f,CSea::TYPE_DIRTY);
	CSea::Create(D3DXVECTOR3(0.0f, -60.0f, 0.0f), 0.005f,CSea::TYPE_DIRTY);
	CSea::Create(D3DXVECTOR3(0.0f, -50.0f, 0.0f), 0.008f,CSea::TYPE_DIRTY);
	
	//マップ生成
	MapCreate();

	//セリフを生成
	m_pTalkStage1 = CTalkStage1::Create(D3DXVECTOR3((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), 0.0f),
										D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));

	////ステージナンバー作成
	//CStageNumber::Create(D3DXVECTOR3(STAGENUMBER_POS_X, STAGENUMBER_POS_Y, 0.0f), 
	//	D3DXVECTOR3(STAGENUMBER_SIZE_X, STAGENUMBER_SIZE_Y, 0.0f),
	//	CStageNumber::STAGE_NUM_1);

	//BGMの再生
	CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_BGM_STAGE_1);

	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CStage1::Uninit(void)
{
	//BGMの終了
	CManager::GetSound()->StopSound();

	CObject::ReleaseAll();
}

//=============================================================================
// 描画関数
//=============================================================================
void CStage1::Draw(void)
{
}

//=============================================================================
// 更新関数
//=============================================================================
void CStage1::Update(void)
{
#ifdef _DEBUG

	//フェイド取得
	CFade*	pBlackout = CManager::GetFadeout();
	//キー入力取得
	CInputKeyboard* pInputKey = (CInputKeyboard*)CManager::GetInputKey();

	//スティック入力
	if (pInputKey->GetKeyTrigger(DIK_RETURN))
	{
		pBlackout->SetWhiteout(CGame::MAP_TYPE_2);
	}
#endif

}

//=============================================================================
// マップ生成関数
//=============================================================================
void CStage1::MapCreate(void)
{
	//マップデータがあるか
	if (&m_pMapData != NULL)
	{
		for (int nBlockY = 0; nBlockY < m_pMapData.nStageSizeY; nBlockY++)
		{
			for (int nBlockX = 0; nBlockX < m_pMapData.BlockData[nBlockY].nStageSizeX; nBlockX++)
			{
				//マス目のタイプ取得
				switch (m_pMapData.BlockData[nBlockY].nBlockType[nBlockX])
				{
				case BLOCK_TYPE_NONE:	//なし

					break;
				case BLOCK_TYPE_START:	//スタート地点
					CPlayer::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
					CRedSandBlock::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
					break;
				case BLOCK_TYPE_GOAL:	//ゴール地点
					CLuggageBlock::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), CGame::MAP_TYPE_1);
					break;
				case BLOCK_TYPE_TILE_RED_SAMD:			//赤砂
					CRedSandBlock::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
					break;
				case BLOCK_TYPE_HINDRANCE_BUILDING_1:	//ビル
					CBuildingBlock::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
					CRedSandBlock::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
					break;

				case BLOCK_TYPE_HINDRANCE_BUILDING_2:	//ビル（半壊）
					CBuildingBreakBlock::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
					CRedSandBlock::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
					break;
				case BLOCK_TYPE_ITEM_GARBAGE:			//ゴミブロック
					CGarbageBlock::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
					CRedSandBlock::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
					break;
				}

			}
		}
		
	}
}

//=============================================================================
// タイトル読み込み用マップ生成関数
//=============================================================================
void CStage1::TitleMapCreate(void)
{
	//マップデータがあるか
	if (&m_pMapData != NULL)
	{
		for (int nBlockY = 0; nBlockY < m_pMapData.nStageSizeY; nBlockY++)
		{
			for (int nBlockX = 0; nBlockX < m_pMapData.BlockData[nBlockY].nStageSizeX; nBlockX++)
			{
				//マス目のタイプ取得
				switch (m_pMapData.BlockData[nBlockY].nBlockType[nBlockX])
				{
				case BLOCK_TYPE_NONE:	//なし

					break;
				case BLOCK_TYPE_START:	//スタート地点
					CRedSandBlock::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
					break;
				case BLOCK_TYPE_GOAL:	//ゴール地点
					CLuggageBlock::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), CGame::MAP_TYPE_2);
					break;
				case BLOCK_TYPE_TILE_RED_SAMD:			//赤砂
					CRedSandBlock::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
					break;
				case BLOCK_TYPE_HINDRANCE_BUILDING_1:	//ビル
					CBuildingBlock::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
					CRedSandBlock::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));

					break;

				case BLOCK_TYPE_HINDRANCE_BUILDING_2:	//ビル（半壊）
					CBuildingBreakBlock::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
					CRedSandBlock::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));

					break;
				case BLOCK_TYPE_ITEM_GARBAGE:			//ゴミブロック
					CGarbageBlock::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
					CRedSandBlock::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));

					break;
				}

			}
		}

	}

}

//=============================================================================
// セリフポインタのゲッター処理
//=============================================================================
CTalkStage1 * CStage1::GetTalkStage1(void)
{
	return m_pTalkStage1;
}