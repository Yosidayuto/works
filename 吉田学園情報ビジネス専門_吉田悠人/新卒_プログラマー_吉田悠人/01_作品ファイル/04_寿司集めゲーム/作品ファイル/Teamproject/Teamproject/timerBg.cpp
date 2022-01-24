//=============================================================================
//
// 制限時間背景の処理 [item.cpp]
// Author : 齋藤大行
//
//=============================================================================

//=============================================================================
// ヘッダーファイル
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "resource manager.h"
#include "timerBg.h"
//=============================================================================
// マクロ定義
//=============================================================================



//=============================================================================
//静的メンバー変数宣言
//=============================================================================

//=============================================================================
// コンストラクタ
//=============================================================================
CtimerBg::CtimerBg(int nPriority) :CScene2d(nPriority)
{
	m_Alpha = 0;
	m_bUse = true;
}

//=============================================================================
// デストラクタ
//=============================================================================
CtimerBg::~CtimerBg()
{
}

//=============================================================================
// 生成関数
//=============================================================================
CtimerBg * CtimerBg::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR Col)
{
	CtimerBg *ptimerBg = NULL;

	ptimerBg = new CtimerBg;

	CResource* pResource = CManager::GetResource();
	LPDIRECT3DTEXTURE9 Texture = pResource->TextureLoad(ptimerBg->m_nTexture);

	if (ptimerBg != NULL)
	{
		ptimerBg->SetObjType(CScene::OBJTYPE_NONE);
		ptimerBg->SetPos(pos);
		ptimerBg->SetSize(size);
		ptimerBg->SetColor(Col);
		ptimerBg->BindTexture(Texture);
		ptimerBg->Init();

	}


	return ptimerBg;
}


//=============================================================================
// 更新処理関数
//=============================================================================
void CtimerBg::Update(void)
{
	CScene2d::Update();
}

//=============================================================================
// 終了処理
//=============================================================================
void CtimerBg::Uninit(void)
{
	CScene2d::Uninit();
}

//=============================================================================
// 描画処理
//=============================================================================
void CtimerBg::Draw(void)
{
	//描画処理
	CScene2d::Draw();
}
