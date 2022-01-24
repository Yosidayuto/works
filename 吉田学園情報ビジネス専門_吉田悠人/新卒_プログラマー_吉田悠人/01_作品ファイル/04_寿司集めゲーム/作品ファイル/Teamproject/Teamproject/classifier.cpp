//=============================================================================
//
// スコア助数詞(マイ)のUI [classifier.cpp]
// Author : 吉田悠人
//
//=============================================================================

//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "classifier.h"
#include "resource manager.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CClassifier::CClassifier()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CClassifier::~CClassifier()
{
}

//=============================================================================
// 生成処理
//=============================================================================
CClassifier * CClassifier::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//メモリ確保
	CClassifier *pClassifier;
	pClassifier = new CClassifier;
	//リソース確保(リソースマネージャーから呼び出す)
	CResource* pResource = CManager::GetResource();
	LPDIRECT3DTEXTURE9 Texture = pResource->TextureLoad(pClassifier->nClassifierTexture);

	//NULLチェック
	if (pClassifier != nullptr)
	{
		pClassifier->BindTexture(Texture);
		pClassifier->SetPos(pos);
		pClassifier->SetSize(size);
		pClassifier->Init();
	}
	return pClassifier;
}
