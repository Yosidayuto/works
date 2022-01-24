//=============================================================================
//
// 寿司　サーモン [salmon.cpp]
// Author : 吉田悠人
//
//=============================================================================

//=============================================================================
// ヘッダーファイル
//=============================================================================
#include "salmon.h"
#include "resource manager.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define SALMON_SCORE (10)

//=============================================================================
// コンストラクタ
//=============================================================================
CSalmon::CSalmon(int nPriority) : CFoodBase(nPriority)
{

}

//=============================================================================
// 生成処理関数
//=============================================================================
CSalmon * CSalmon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//メモリの確保
	CSalmon *pSalmon;
	pSalmon = new CSalmon;

	//リソース確保(リソースマネージャーから呼び出す)
	CResource* pResource = CManager::GetResource();
	LPDIRECT3DTEXTURE9 Texture = pResource->TextureLoad(pSalmon->m_nTexture);

	//NULLチェック
	if (pSalmon != NULL)
	{
		pSalmon->SetPos(pos);				// 位置設定
		pSalmon->SetSize(size);				// サイズ設定
		pSalmon->SetPoint(SALMON_SCORE);	// スコア設定
		pSalmon->BindTexture(Texture);		// テクスチャ設定
		pSalmon->SetFoodType(TYPE_SALMON);	// タイプ設定
		pSalmon->Init();					// 初期化処理
	}

	return pSalmon;
}
