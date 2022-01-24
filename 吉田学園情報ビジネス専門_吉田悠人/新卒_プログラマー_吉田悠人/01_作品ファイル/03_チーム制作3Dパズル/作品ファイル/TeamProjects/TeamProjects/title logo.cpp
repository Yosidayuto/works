//=============================================================================
//
//	タイトルロゴ[title logo.cpp]
//	Author:吉田　悠人
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "title logo.h"
#include "resource manager.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CTitleLoge::CTitleLoge(int nPriority) :CUi(nPriority)
{

}

//=============================================================================
// 生成処理
//=============================================================================
CTitleLoge * CTitleLoge::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//メモリ確保
	CTitleLoge *pTitleLoge = NULL;
	pTitleLoge = new CTitleLoge;
	//リソース確保
	CResource* pResource = CManager::GetResource();
	LPDIRECT3DTEXTURE9 Texture = pResource->TextureLoad(pTitleLoge->m_nTexture);

	//NULLチェック
	if (pTitleLoge != NULL)
	{
		//位置設定
		pTitleLoge->SetPos(D3DXVECTOR3(pos.x, pos.y, pos.z));
		//サイズ設定
		pTitleLoge->SetSize(D3DXVECTOR3(size.x, size.y, size.z));
		//テクスチャ設定
		pTitleLoge->BindTexture(Texture);
		//初期化処理
		pTitleLoge->Init();
	}
	return pTitleLoge;
}
