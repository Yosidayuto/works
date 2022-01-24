//=============================================================================
//
//	セリフNo11 [talk No11.cpp]
//	Author:吉田 悠人
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "resource manager.h"
#include "inputkeyboard.h"
#include "inputcontroller.h"
#include "renderer.h"
#include "talk no11.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CTalkNo11::CTalkNo11(int nPriorit)
{
}

//=============================================================================
// 生成処理
//=============================================================================
CTalkNo11 * CTalkNo11::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//メモリ確保
	CTalkNo11* pTalkNo11 = nullptr;
	pTalkNo11 = new CTalkNo11;
	//リソース確保
	CResource* pResource = CManager::GetResource();
	LPDIRECT3DTEXTURE9 Texture = pResource->TextureLoad(pTalkNo11->m_nTexture);

	//NULLチェック
	if (pTalkNo11 != nullptr)
	{
		//位置設定
		pTalkNo11->SetPos(pos);
		//サイズ設定
		pTalkNo11->SetSize(size);
		//テクスチャ設定
		pTalkNo11->BindTexture(Texture);
		//初期化処理
		pTalkNo11->Init();
	}
	return pTalkNo11;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTalkNo11::Init(void)
{
	//出現している時間セット
	SetAppear(0);
	//フェード状況設定
	SetFade(FADE_IN);

	//初期化処理
	CTalkbase::Init();
	return S_OK;
}

//=============================================================================
// トーク処理
//=============================================================================
void CTalkNo11::Talk(void)
{
	//個数
	int nCountItem = 0;
	//オブジェクト取得用
	CObject* pTop[PRIORITY_MAX] = {};
	//次チェックするオブジェクトのポインタ
	CObject* pNext = NULL;
	//topのアドレスを取得
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		pTop[nCount] = *(CObject::GetTop() + nCount);
	}


	//オブジェクト探査
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		if (pTop[nCount] != NULL)
		{
			pNext = pTop[nCount];
			//その描画優先度のオブジェクトがなくなるまでループ
			while (pNext != NULL)
			{
				//オブジェクトのタイプがアイテムなら
				if (pNext->GetObjType() == OBJTYPE_ITEM)
				{
					nCountItem++;
				}

				//次のオブジェクトのポインタを更新
				pNext = pNext->GetNext();
			}
		}
	}

	//アイテムが一つの時
	if (nCountItem == 0)
	{
		//透過状況を設定
		m_Fade = FADE_OUT;
	}

}
