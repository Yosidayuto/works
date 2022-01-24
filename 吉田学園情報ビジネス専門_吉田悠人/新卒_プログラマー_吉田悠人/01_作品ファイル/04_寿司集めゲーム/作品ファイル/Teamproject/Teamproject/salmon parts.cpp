//=============================================================================
//
//  寿司　サーモンパーツ [salmon parts.cpp]
//	Author:吉田悠人
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "salmon parts.h"
#include "renderer.h"
#include "resource manager.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CSalmonParts::CSalmonParts()
{

}

//=============================================================================
// 生成処理関数
//=============================================================================
CSalmonParts * CSalmonParts::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, D3DXVECTOR3 Size, CScene3d * pParent)
{
	//メモリ確保
	CSalmonParts* pSalmonPrts = NULL;
	pSalmonPrts = new CSalmonParts;
	//リソース確保(リソースマネージャーから呼び出す)
	CResource* pResource = CManager::GetResource();
	LPDIRECT3DTEXTURE9 Texture = pResource->TextureLoad(pSalmonPrts->m_nTexture);

	//NULLチェック
	if (pSalmonPrts != NULL)
	{
		//位置設定
		pSalmonPrts->SetPos(Pos);
		//向き設定
		pSalmonPrts->SetRot(Rot);
		//サイズ設定
		pSalmonPrts->SetSize(Size);
		//親パーツポインタ取得
		pSalmonPrts->SetParent(pParent);
		//タイプ設定
		pSalmonPrts->SetType(CFoodBase::TYPE_SALMON);
		//テクスチャ設定
		pSalmonPrts->BindTexture(Texture);
		//初期化処理
		pSalmonPrts->Init();
	}

	return pSalmonPrts;
}
