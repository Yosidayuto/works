//=============================================================================
//
//  寿司　エビパーツ [ebi parts.cpp]
//	Author:吉田悠人
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "ebi parts.h"
#include "renderer.h"
#include "resource manager.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CEbiParts::CEbiParts()
{

}

//=============================================================================
// 生成処理関数
//=============================================================================
CEbiParts * CEbiParts::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, D3DXVECTOR3 Size, CScene3d * pParent)
{
	//メモリ確保
	CEbiParts* pEbiPrts = NULL;
	pEbiPrts = new CEbiParts;
	//リソース確保(リソースマネージャーから呼び出す)
	CResource* pResource = CManager::GetResource();
	LPDIRECT3DTEXTURE9 Texture = pResource->TextureLoad(pEbiPrts->m_nTexture);

	//NULLチェック
	if (pEbiPrts != NULL)
	{
		//位置設定
		pEbiPrts->SetPos(Pos);
		//向き設定
		pEbiPrts->SetRot(Rot);
		//サイズ設定
		pEbiPrts->SetSize(Size);
		//親パーツポインタ取得
		pEbiPrts->SetParent(pParent);
		//タイプ設定
		pEbiPrts->SetType(CFoodBase::TYPE_EBI);
		//テクスチャ設定
		pEbiPrts->BindTexture(Texture);
		//初期化処理
		pEbiPrts->Init();
	}

	return pEbiPrts;
}
