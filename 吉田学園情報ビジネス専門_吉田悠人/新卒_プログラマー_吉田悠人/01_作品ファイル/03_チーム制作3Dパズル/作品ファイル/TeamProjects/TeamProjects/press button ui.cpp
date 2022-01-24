//=============================================================================
//
//	プレスボタンUI[press button.cpp]
//	Author:吉田　悠人
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "press button ui.h"
#include "resource manager.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CPressUi::CPressUi(int nPriorit) :CUi(nPriorit)
{

}

//=============================================================================
// 生成処理
//=============================================================================
CPressUi * CPressUi::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//メモリ確保
	CPressUi *pPressUi = NULL;
	pPressUi = new CPressUi;
	//リソース確保
	CResource* pResource = CManager::GetResource();
	LPDIRECT3DTEXTURE9 Texture = pResource->TextureLoad(pPressUi->m_nTexture);

	//NULLチェック
	if (pPressUi != NULL)
	{
		//位置設定
		pPressUi->SetPos(D3DXVECTOR3(pos.x, pos.y, pos.z));
		//サイズ設定
		pPressUi->SetSize(D3DXVECTOR3(size.x, size.y, size.z));
		//テクスチャ設定
		pPressUi->BindTexture(Texture);
		//初期化処理
		pPressUi->Init();
	}
	return pPressUi;
}