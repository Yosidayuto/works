//=============================================================================
//
// 赤砂ブロック [red sand block.cpp]
// Author : 吉田悠人
//
//=============================================================================

//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "red sand block.h"
#include "resource manager.h"
#include "manager.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CRedSandBlock::CRedSandBlock()
{
}
//=============================================================================
// デストラクタ
//=============================================================================
CRedSandBlock::~CRedSandBlock()
{
}

//=============================================================================
// 生成関数
//=============================================================================
CRedSandBlock * CRedSandBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	//メモリ確保
	CRedSandBlock* pRedSandBlock = NULL;
	pRedSandBlock = new CRedSandBlock;
	//リソース確保
	CResource* pResource = CManager::GetResource();
	CModel::MODELDATA Model = pResource->ModelLoad(pRedSandBlock->m_nModel);

	//NULLチェック
	if (pRedSandBlock != NULL)
	{
		
		//位置設定
		pRedSandBlock->SetPosition(D3DXVECTOR3(pos.x, pos.y - BLOCK_HEIGHT, pos.z));
		//向き設定
		pRedSandBlock->SetRotation(rot);
		//カラー設定
		pRedSandBlock->SetScale(size);
		//モデル設定
		pRedSandBlock->SetModelData(Model);
		//初期化処理
		pRedSandBlock->Init();
	}

	return pRedSandBlock;
}

