//=============================================================================
//
// 荷物ブロック [luggage block.cpp]
// Author : 吉田悠人
//
//=============================================================================

//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "luggage block.h"
#include "resource manager.h"
#include "object.h"
#include "model.h"
#include "model object.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define LUGGAGE_HEIGHT (-25.0f)	//高さ調整

//=============================================================================
// コンストラクタ
//=============================================================================
CLuggageBlock::CLuggageBlock()
{
	bGoal = false;
}
//=============================================================================
// デストラクタ
//=============================================================================
CLuggageBlock::~CLuggageBlock()
{
}

//=============================================================================
// 生成関数
//=============================================================================
CLuggageBlock * CLuggageBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, CGame::MAP_TYPE MapType, bool Goal)
{
	//メモリ確保
	CLuggageBlock* pLuggageBlock = NULL;
	pLuggageBlock = new CLuggageBlock;
	//リソース確保
	CResource* pResource = CManager::GetResource();
	CModel::MODELDATA Model = pResource->ModelLoad(pLuggageBlock->m_nModel);

	//NULLチェック
	if (pLuggageBlock != NULL)
	{
		//位置設定
		pLuggageBlock->SetPosition(D3DXVECTOR3(pos.x, pos.y + LUGGAGE_HEIGHT, pos.z));
		//向き設定
		pLuggageBlock->SetRotation(rot);
		//カラー設定
		pLuggageBlock->SetScale(size);
		//マップ設定
		pLuggageBlock->SetMapType(MapType);
		//モデル設定
		pLuggageBlock->SetModelData(Model);
		//ゴール機能設定
		pLuggageBlock->SetGoal(Goal);
		//初期化処理
		pLuggageBlock->Init();
	}

	return pLuggageBlock;
}
