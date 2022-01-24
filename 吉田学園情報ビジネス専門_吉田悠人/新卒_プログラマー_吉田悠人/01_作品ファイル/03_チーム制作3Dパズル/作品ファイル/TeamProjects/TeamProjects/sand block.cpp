//=============================================================================
//
// 砂ブロック [sand block.cpp]
// Author : 吉田悠人
//
//=============================================================================

//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "sand block.h"
#include "resource manager.h"
#include "manager.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CSandBlock::CSandBlock()
{
}
//=============================================================================
// デストラクタ
//=============================================================================
CSandBlock::~CSandBlock()
{
}

//=============================================================================
// 生成関数
//=============================================================================
CSandBlock * CSandBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	//メモリ確保
	CSandBlock* pSandBlock = NULL;
	pSandBlock = new CSandBlock;
	//リソース確保
	CResource* pResource = CManager::GetResource();
	CModel::MODELDATA Model = pResource->ModelLoad(pSandBlock->m_nModel);

	//NULLチェック
	if (pSandBlock != NULL)
	{
		//位置設定
		pSandBlock->SetPosition(D3DXVECTOR3(pos.x, pos.y - BLOCK_HEIGHT, pos.z));
		//向き設定
		pSandBlock->SetRotation(rot);
		//カラー設定
		pSandBlock->SetScale(size);
		//モデル設定
		pSandBlock->SetModelData(Model);
		//初期化処理
		pSandBlock->Init();
	}

	return pSandBlock;
}