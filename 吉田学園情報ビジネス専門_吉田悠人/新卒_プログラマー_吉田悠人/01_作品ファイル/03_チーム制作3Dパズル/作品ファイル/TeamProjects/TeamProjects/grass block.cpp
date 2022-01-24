//=============================================================================
//
// 草ブロック処理 [grass block.cpp]
// Author : 吉田悠人
//
//=============================================================================

//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "grass block.h"
#include "manager.h"
#include "resource manager.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CGrassBlock::CGrassBlock()
{
}
//=============================================================================
// デストラクタ
//=============================================================================
CGrassBlock::~CGrassBlock()
{
}

//=============================================================================
// 生成関数
//=============================================================================
CGrassBlock * CGrassBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	//メモリ確保
	CGrassBlock* pTileBlock = NULL;
	pTileBlock = new CGrassBlock;
	//リソース確保
	CResource* pResource = CManager::GetResource();
	CModel::MODELDATA Model = pResource->ModelLoad(pTileBlock->m_nModel);

	//NULLチェック
	if (pTileBlock != NULL)
	{
		//位置設定
		pTileBlock->SetPosition(D3DXVECTOR3(pos.x, pos.y - BLOCK_HEIGHT, pos.z));
		//向き設定
		pTileBlock->SetRotation(rot);
		//カラー設定
		pTileBlock->SetScale(size);
		//モデル設定
		pTileBlock->SetModelData(Model);
		//初期化処理
		pTileBlock->Init();
	}

	return pTileBlock;
}