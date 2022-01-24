//=============================================================================
//
// リンゴブロック [apple block.cpp]
// Author : 吉田悠人
//
//=============================================================================

//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "apple block.h"
#include "resource manager.h"
#include "manager.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CAppleBlock::CAppleBlock()
{
}
//=============================================================================
// デストラクタ
//=============================================================================
CAppleBlock::~CAppleBlock()
{
}

//=============================================================================
// 生成関数
//=============================================================================
CAppleBlock * CAppleBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	//メモリ確保
	CAppleBlock* pAppleBlock = NULL;
	pAppleBlock = new CAppleBlock;
	//リソース確保
	CResource* pResource = CManager::GetResource();
	CModel::MODELDATA Model = pResource->ModelLoad(pAppleBlock->m_nModel);

	//NULLチェック
	if (pAppleBlock != NULL)
	{
		//位置設定
		pAppleBlock->SetPosition(D3DXVECTOR3(pos.x, pos.y + ITEM_HEIGHT, pos.z));
		//向き設定
		pAppleBlock->SetRotation(rot);
		//カラー設定
		pAppleBlock->SetScale(size);
		//モデル設定
		pAppleBlock->SetModelData(Model);
		//初期化処理
		pAppleBlock->Init();
	}

	return pAppleBlock;
}
