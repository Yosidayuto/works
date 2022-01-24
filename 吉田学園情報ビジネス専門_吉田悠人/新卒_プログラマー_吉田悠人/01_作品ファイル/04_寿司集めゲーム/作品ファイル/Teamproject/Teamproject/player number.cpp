//=============================================================================
//
// プレイヤーの番号UI [player number.h]
// Author : 吉田悠人
//
//=============================================================================

//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "player number.h"
#include "resource manager.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CPlayerNumber::CPlayerNumber()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CPlayerNumber::~CPlayerNumber()
{
}

//=============================================================================
// 生成処理
//=============================================================================
CPlayerNumber * CPlayerNumber::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nNumber)
{
	//メモリ確保
	CPlayerNumber *pPlayerNumber;
	pPlayerNumber = new CPlayerNumber;
	//リソース確保(リソースマネージャーから呼び出す)
	CResource* pResource = CManager::GetResource();
	LPDIRECT3DTEXTURE9 Texture = pResource->TextureLoad(pPlayerNumber->nPlayerNumberTexture[nNumber]);

	//NULLチェック
	if (pPlayerNumber != nullptr)
	{
		pPlayerNumber->BindTexture(Texture);
		pPlayerNumber->SetPos(pos);
		pPlayerNumber->SetSize(size);
		pPlayerNumber->Init();
	}
	return pPlayerNumber;
}
