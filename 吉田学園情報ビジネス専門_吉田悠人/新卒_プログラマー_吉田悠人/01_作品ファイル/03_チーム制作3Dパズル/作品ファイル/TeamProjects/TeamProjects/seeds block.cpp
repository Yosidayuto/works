//=============================================================================
//
// 種ブロック [seeds block.cpp]
// Author : 吉田悠人
//
//=============================================================================

//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "seeds block.h"
#include "resource manager.h"
#include "manager.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CSeedsBlock::CSeedsBlock()
{
}
//=============================================================================
// デストラクタ
//=============================================================================
CSeedsBlock::~CSeedsBlock()
{
}

//=============================================================================
// 生成関数
//=============================================================================
CSeedsBlock * CSeedsBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	//メモリ確保
	CSeedsBlock* pSeedsBlock = NULL;
	pSeedsBlock = new CSeedsBlock;
	//リソース確保
	CResource* pResource = CManager::GetResource();
	CModel::MODELDATA Model = pResource->ModelLoad(pSeedsBlock->m_nModel);

	//NULLチェック
	if (pSeedsBlock != NULL)
	{
		//位置設定
		pSeedsBlock->SetPosition(D3DXVECTOR3(pos.x, pos.y + ITEM_HEIGHT, pos.z));
		//向き設定
		pSeedsBlock->SetRotation(rot);
		//カラー設定
		pSeedsBlock->SetScale(size);
		//モデル設定
		pSeedsBlock->SetModelData(Model);
		//初期化処理
		pSeedsBlock->Init();
	}

	return pSeedsBlock;
}
