//=============================================================================
//
//  寿司　イクラパーツ [ikura parts.cpp]
//	Author:吉田悠人
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "ikura parts.h"
#include "renderer.h"
#include "resource manager.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CIkuraParts::CIkuraParts()
{

}

//=============================================================================
// 生成処理関数
//=============================================================================
CIkuraParts * CIkuraParts::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, D3DXVECTOR3 Size, CScene3d * pParent)
{
	//メモリ確保
	CIkuraParts* pIkuraPrts = NULL;
	pIkuraPrts = new CIkuraParts;
	//リソース確保(リソースマネージャーから呼び出す)
	CResource* pResource = CManager::GetResource();
	LPDIRECT3DTEXTURE9 Texture = pResource->TextureLoad(pIkuraPrts->m_nTexture);

	//NULLチェック
	if (pIkuraPrts != NULL)
	{
		//位置設定
		pIkuraPrts->SetPos(Pos);
		//向き設定
		pIkuraPrts->SetRot(Rot);
		//サイズ設定
		pIkuraPrts->SetSize(Size);
		//親パーツポインタ取得
		pIkuraPrts->SetParent(pParent);
		//タイプ設定
		pIkuraPrts->SetType(CFoodBase::TYPE_IKURA);
		//テクスチャ設定
		pIkuraPrts->BindTexture(Texture);
		//初期化処理
		pIkuraPrts->Init();
	}

	return pIkuraPrts;
}
