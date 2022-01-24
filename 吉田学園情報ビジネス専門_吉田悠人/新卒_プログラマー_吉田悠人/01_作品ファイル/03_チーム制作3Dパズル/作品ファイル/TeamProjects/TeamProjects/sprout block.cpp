//=============================================================================
//
// 芽ブロック [sprout block.cpp]
// Author : 吉田悠人
//
//=============================================================================

//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "sprout block.h"
#include "resource manager.h"
#include "manager.h"
#include "model.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CSproutBlock::CSproutBlock()
{
}
//=============================================================================
// デストラクタ
//=============================================================================
CSproutBlock::~CSproutBlock()
{
}

//=============================================================================
// 生成関数
//=============================================================================
CSproutBlock * CSproutBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	//メモリ確保
	CSproutBlock* pSproutBlock = NULL;
	pSproutBlock = new CSproutBlock;
	//リソース確保
	CResource* pResource = CManager::GetResource();
	CModel::MODELDATA Model = pResource->ModelLoad(pSproutBlock->m_nModel);

	//NULLチェック
	if (pSproutBlock != NULL)
	{
		//位置設定
		pSproutBlock->SetPosition(D3DXVECTOR3(pos.x, pos.y - BLOCK_HEIGHT, pos.z));
		//向き設定
		pSproutBlock->SetRotation(rot);
		//カラー設定
		pSproutBlock->SetScale(size);
		//モデル設定
		pSproutBlock->SetModelData(Model);
		//初期化処理
		pSproutBlock->Init();
	}

	return pSproutBlock;
}