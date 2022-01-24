//=============================================================================
//
// 針葉樹（高い） [big tree.cpp]
// Author : 吉田悠人
//
//=============================================================================

//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "big tree.h"
#include "resource manager.h"
#include "manager.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CBigTree::CBigTree()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CBigTree::~CBigTree()
{
}

//=============================================================================
// 生成関数
//=============================================================================
CBigTree * CBigTree::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	//メモリ確保
	CBigTree* pBigTree = NULL;
	pBigTree = new CBigTree;
	//リソース確保
	CResource* pResource = CManager::GetResource();
	CModel::MODELDATA Model = pResource->ModelLoad(pBigTree->m_nModel);

	//NULLチェック
	if (pBigTree != NULL)
	{
		//位置設定
		pBigTree->SetPosition(D3DXVECTOR3(pos.x, pos.y + HINDRANCE_HEIGHT, pos.z));
		//向き設定
		pBigTree->SetRotation(rot);
		//カラー設定
		pBigTree->SetScale(size);
		//モデル設定
		pBigTree->SetModelData(Model);
		//初期化処理
		pBigTree->Init();
	}

	return pBigTree;
}

