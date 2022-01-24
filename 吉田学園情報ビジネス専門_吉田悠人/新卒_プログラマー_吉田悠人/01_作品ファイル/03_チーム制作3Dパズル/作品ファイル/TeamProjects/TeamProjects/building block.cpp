//=============================================================================
//
// ビルブロック [building block.cpp]
// Author : 吉田悠人
//
//=============================================================================

//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "building block.h"
#include "resource manager.h"
#include "manager.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CBuildingBlock::CBuildingBlock()
{
}
//=============================================================================
// デストラクタ
//=============================================================================
CBuildingBlock::~CBuildingBlock()
{
}

//=============================================================================
// 生成関数
//=============================================================================
CBuildingBlock * CBuildingBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	//メモリ確保
	CBuildingBlock* pBuildingBlock = NULL;
	pBuildingBlock = new CBuildingBlock;
	//リソース確保
	CResource* pResource = CManager::GetResource();
	CModel::MODELDATA Model = pResource->ModelLoad(pBuildingBlock->m_nModel);

	//NULLチェック
	if (pBuildingBlock != NULL)
	{
		//位置設定
		pBuildingBlock->SetPosition(D3DXVECTOR3(pos.x, pos.y + HINDRANCE_HEIGHT, pos.z));
		//向き設定
		pBuildingBlock->SetRotation(rot);
		//カラー設定
		pBuildingBlock->SetScale(size);
		//モデル設定
		pBuildingBlock->SetModelData(Model);
		//初期化処理
		pBuildingBlock->Init();
	}

	return pBuildingBlock;
}
