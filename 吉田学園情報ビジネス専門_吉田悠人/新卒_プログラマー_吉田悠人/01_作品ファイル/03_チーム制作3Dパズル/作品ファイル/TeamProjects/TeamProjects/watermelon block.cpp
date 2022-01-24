//=============================================================================
//
// スイカブロック [watermelon block.cpp]
// Author : 吉田悠人
//
//=============================================================================

//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "watermelon block.h"
#include "resource manager.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CWatermelonBlock::CWatermelonBlock()
{
}
//=============================================================================
// デストラクタ
//=============================================================================
CWatermelonBlock::~CWatermelonBlock()
{
}


//=============================================================================
// 生成関数
//=============================================================================
CWatermelonBlock * CWatermelonBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	//メモリ確保
	CWatermelonBlock* pWatermelonBlock = NULL;
	pWatermelonBlock = new CWatermelonBlock;
	//リソース確保
	CResource* pResource = CManager::GetResource();
	CModel::MODELDATA Model = pResource->ModelLoad(pWatermelonBlock->m_nModel);

	//NULLチェック
	if (pWatermelonBlock != NULL)
	{
		//位置設定
		pWatermelonBlock->SetPosition(D3DXVECTOR3(pos.x, pos.y + ITEM_HEIGHT+20, pos.z));
		//向き設定
		pWatermelonBlock->SetRotation(rot);
		//カラー設定
		pWatermelonBlock->SetScale(size);
		//モデル設定
		pWatermelonBlock->SetModelData(Model);
		//初期化処理
		pWatermelonBlock->Init();
	}

	return pWatermelonBlock;
}
