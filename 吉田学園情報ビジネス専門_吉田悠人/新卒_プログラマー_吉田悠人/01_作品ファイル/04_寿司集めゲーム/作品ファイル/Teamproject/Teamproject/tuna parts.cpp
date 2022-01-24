//=============================================================================
//
// 寿司　マグロパーツ [tuna parts.cpp]
//	Author:吉田悠人
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "tuna parts.h"
#include "renderer.h"
#include "resource manager.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CTunaParts::CTunaParts()
{

}

//=============================================================================
// 生成処理関数
//=============================================================================
CTunaParts * CTunaParts::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, D3DXVECTOR3 Size, CScene3d * pParent)
{
	//メモリ確保
	CTunaParts* pTunaPrts = NULL;
	pTunaPrts = new CTunaParts;
	//リソース確保(リソースマネージャーから呼び出す)
	CResource* pResource = CManager::GetResource();
	LPDIRECT3DTEXTURE9 Texture = pResource->TextureLoad(pTunaPrts->m_nTexture);

	//NULLチェック
	if (pTunaPrts != NULL)
	{
		//位置設定
		pTunaPrts->SetPos(Pos);
		//向き設定
		pTunaPrts->SetRot(Rot);
		//サイズ設定
		pTunaPrts->SetSize(Size);
		//親パーツポインタ取得
		pTunaPrts->SetParent(pParent);
		//タイプ設定
		pTunaPrts->SetType(CFoodBase::TYPE_TUNA);
		//テクスチャ設定
		pTunaPrts->BindTexture(Texture);
		//初期化処理
		pTunaPrts->Init();
	}

	return pTunaPrts;
}
