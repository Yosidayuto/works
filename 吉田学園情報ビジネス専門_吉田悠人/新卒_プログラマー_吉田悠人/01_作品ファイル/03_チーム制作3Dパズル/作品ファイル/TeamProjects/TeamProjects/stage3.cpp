//=============================================================================
//
// ステージ3 [stage3.cpp]
// Author : 吉田悠人
//
//=============================================================================
//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "stage3.h"
#include "inputkeyboard.h"
#include "fade.h"
#include "manager.h"
#include "game.h"
#include "player.h"
#include "grass block.h"
#include "small tree.h"
#include "big tree.h"
#include "apple block.h"
#include "oranges block.h"
#include "grapes block.h"
#include "watermelon block.h"
#include <stdio.h>
#include "talk_stage3.h"
#include "sound.h"
#include "luggage block.h"
#include "sea.h"
#include "camera.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define STAGENUMBER_POS_X 1100.0f
#define STAGENUMBER_POS_Y 80.0f
#define STAGENUMBER_SIZE_X 150.0f
#define STAGENUMBER_SIZE_Y 50.0f

//=============================================================================
// 静的メンバー変数
//=============================================================================
char* CStage3::m_pFileName = "Data/Text/stage_3.csv";
MAP_DATA CStage3::m_pMapData = {};
CTalkStage3* CStage3::m_pTalkStage3 = nullptr;

//=============================================================================
// コンストラクタ
//=============================================================================
CStage3::CStage3()
{

}
//=============================================================================
// デストラクタ
//=============================================================================
CStage3::~CStage3()
{

}

//=============================================================================
// ロード関数
//=============================================================================
void CStage3::Load(void)
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
				m_pMapData.BlockData[nRow].nBlockType[nCol] = BLOCK_TYPE_TILE_GRASS;
				break;
			case 4:
				//ブロックタイプ記憶
				m_pMapData.BlockData[nRow].nBlockType[nCol] = BLOCK_TYPE_HINDRANCE_BIG_TREE;
				break;
			case 5:
				//ブロックタイプ記憶
				m_pMapData.BlockData[nRow].nBlockType[nCol] = BLOCK_TYPE_HINDRANCE_SMALL_TREE;
				break;
			case 6:
				//ブロックタイプ記憶
				m_pMapData.BlockData[nRow].nBlockType[nCol] = BLOCK_TYPE_ITEM_APPLE;
				break;
			case 7:
				//ブロックタイプ記憶
				m_pMapData.BlockData[nRow].nBlockType[nCol] = BLOCK_TYPE_ITEM_ORANGES;
				break;
			case 8:
				//ブロックタイプ記憶
				m_pMapData.BlockData[nRow].nBlockType[nCol] = BLOCK_TYPE_ITEM_GRAPES;
				break;
			case 9:
				//ブロックタイプ記憶
				m_pMapData.BlockData[nRow].nBlockType[nCol] = BLOCK_TYPE_ITEM_WATERMELON;
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
HRESULT CStage3::Init(void)
{
	//カメラの注視位置
	CManager::GetCamera()->SetPos(D3DXVECTOR3(-275, 0.0f, 300.0f));

	// 海の生成
	CSea::Create(D3DXVECTOR3(0.0f, -70.0f, 0.0f), 0.002f, CSea::TYPE_EVENING);
	CSea::Create(D3DXVECTOR3(0.0f, -60.0f, 0.0f), 0.005f, CSea::TYPE_EVENING);
	CSea::Create(D3DXVECTOR3(0.0f, -50.0f, 0.0f), 0.008f, CSea::TYPE_EVENING);

	//マップ生成
	MapCreate();

	////ステージナンバー作成
	//CStageNumber::Create(D3DXVECTOR3(STAGENUMBER_POS_X, STAGENUMBER_POS_Y, 0.0f), D3DXVECTOR3(STAGENUMBER_SIZE_X, STAGENUMBER_SIZE_Y, 0.0f), CStageNumber::STAGE_NUM_3);

	//セリフの生成
	m_pTalkStage3 = CTalkStage3::Create(D3DXVECTOR3((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));

	//BGMの再生
	CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_BGM_STAGE_3);

	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CStage3::Uninit(void)
{
	//BGMの終了
	CManager::GetSound()->StopSound(CSound::SOUND_LABEL_BGM_STAGE_3);

	CObject::ReleaseAll();
}

//=============================================================================
// 描画関数
//=============================================================================
void CStage3::Draw(void)
{
}

//=============================================================================
// 更新関数
//=============================================================================
void CStage3::Update(void)
{
#ifdef _DEBUG

	//フェイド取得
	CFade*	pBlackout = CManager::GetFadeout();
	//キー入力取得
	CInputKeyboard* pInputKey = (CInputKeyboard*)CManager::GetInputKey();

	//スティック入力
	if (pInputKey->GetKeyTrigger(DIK_RETURN))
	{
		pBlackout->SetWhiteout(CGame::MAP_TYPE_1);
	}
#endif

}

//=============================================================================
// マップ生成関数
//=============================================================================
void CStage3::MapCreate(void)
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
				case BLOCK_TYPE_START:		//スタート地点
					CPlayer::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
					CGrassBlock::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
					break;
				case BLOCK_TYPE_GOAL:		//ゴール地点
					CLuggageBlock::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), CGame::MAP_TYPE_3);
					break;
				case BLOCK_TYPE_TILE_GRASS:	//草ブロック
					CGrassBlock::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
					break;
				case BLOCK_TYPE_HINDRANCE_BIG_TREE:		//針葉樹(大きい)
					CBigTree::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
					CGrassBlock::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
					break;

				case BLOCK_TYPE_HINDRANCE_SMALL_TREE:	//針葉樹(小さい)
					CSmallTree::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
					CGrassBlock::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
					break;
				case BLOCK_TYPE_ITEM_APPLE:				//リンゴブロック
					CAppleBlock::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
					CGrassBlock::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));

					break;
				case BLOCK_TYPE_ITEM_ORANGES:			//オレンジブロック
					COrangesBlock::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
					CGrassBlock::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));

					break;
				case BLOCK_TYPE_ITEM_GRAPES:			//ブドウブロック
					CGrapesBlock::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
					CGrassBlock::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));

					break;
				case BLOCK_TYPE_ITEM_WATERMELON:		//スイカブロック
					CWatermelonBlock::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
					CGrassBlock::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
					break;

				}

			}
		}

	}
}

//=============================================================================
// セリフポインタのゲッター処理
//=============================================================================
CTalkStage3 * CStage3::GetTalkStage3(void)
{
	return m_pTalkStage3;
}