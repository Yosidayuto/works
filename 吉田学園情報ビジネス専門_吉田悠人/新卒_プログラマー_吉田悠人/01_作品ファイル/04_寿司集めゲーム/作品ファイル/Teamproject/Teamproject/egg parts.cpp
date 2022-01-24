//=============================================================================
//
// 寿司　卵パーツ [egg parts.cpp]
//	Author:吉田悠人
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "egg parts.h"
#include "renderer.h"
#include "resource manager.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CEggParts::CEggParts()
{

}

//=============================================================================
// 生成処理関数
//=============================================================================
CEggParts * CEggParts::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, D3DXVECTOR3 Size, CScene3d * pParent)
{
	//メモリ確保
	CEggParts* pEggPrts = NULL;
	pEggPrts = new CEggParts;
	//リソース確保(リソースマネージャーから呼び出す)
	CResource* pResource = CManager::GetResource();
	LPDIRECT3DTEXTURE9 Texture = pResource->TextureLoad(pEggPrts->m_nTexture);

	//NULLチェック
	if (pEggPrts != NULL)
	{
		//位置設定
		pEggPrts->SetPos(Pos);
		//向き設定
		pEggPrts->SetRot(Rot);
		//サイズ設定
		pEggPrts->SetSize(Size);
		//親パーツポインタ取得
		pEggPrts->SetParent(pParent);
		//タイプ設定
		pEggPrts->SetType(CFoodBase::TYPE_EGG);
		//テクスチャ設定
		pEggPrts->BindTexture(Texture);
		//初期化処理
		pEggPrts->Init();
	}

	return pEggPrts;
}
