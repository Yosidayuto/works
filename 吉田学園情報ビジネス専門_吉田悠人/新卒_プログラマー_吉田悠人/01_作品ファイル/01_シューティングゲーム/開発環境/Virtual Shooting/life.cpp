//=============================================================================
//
//	ライフ表示[life.h]
//	Author:吉田　悠人
//
//=============================================================================

//=============================================================================
//ヘッダファイル
//=============================================================================
#include "life.h"		
#include "scene2d.h"	
#include "manager.h"	
#include "renderer.h"	
#include "life ui.h"
#include "life tank.h"
//=============================================================================
//マクロ定義
//=============================================================================
#define LIFE_SIZE_X (200.0f,20.0f)
#define LIFE_SIZE_Y (30.0f)

//=============================================================================
//静的メンバー変数
//=============================================================================
LPDIRECT3DTEXTURE9 CLife::m_apTexture = NULL;

//=============================================================================
//コンストラクタ
//=============================================================================
CLife::CLife(int nPriorit) :CScene(nPriorit)
{
	//タイプ処理
	CScene::SetObjType(CScene::OBJ_TYPE_NONE);
	nLife = 0;
	m_LifeTank = NULL;
	memset(m_LifeUi,NULL,sizeof(m_LifeUi));
	
}

//=============================================================================
//デストラクタ
//=============================================================================
CLife::~CLife()
{
}

//=============================================================================
//生成処理
//=============================================================================
CLife * CLife::Create(D3DXVECTOR3 pos)
{
	//メモリ確保
	CLife *pLife = NULL;
	pLife = new CLife;

	//NULLチェック
	if (pLife!=NULL)
	{
		//位置設定
		pLife->SetPos(pos);
		//初期化処理
		pLife->Init();
	}
	return pLife;
}

//=============================================================================
//初期化処理
//=============================================================================
HRESULT CLife::Init(void)
{
	m_LifeTank = CLifeTank::Create(D3DXVECTOR3((float)(LIFE_SIZE_X*(MAX_LIFE / 2) + pos.x), (float)(pos.y - LIFE_SIZE_Y / 2), 0.0f), D3DXVECTOR3((float)(LIFE_SIZE_X*(MAX_LIFE*1.5f)), LIFE_SIZE_Y*1.5, 0.0f));

	for (int nCount = 0; nCount < MAX_LIFE; nCount++)
	{
		m_LifeUi[nCount] = CLifeUi::Create(D3DXVECTOR3((nCount*LIFE_SIZE_X + LIFE_SIZE_X / 2) + pos.x, (pos.y - LIFE_SIZE_Y / 2), 0.0f), D3DXVECTOR3(LIFE_SIZE_X, LIFE_SIZE_Y, 0.0f));
	}
	return S_OK;

}

//=============================================================================
//終了処理
//=============================================================================
void CLife::Uninit(void)
{
	Release();
}

//=============================================================================
//更新処理
//=============================================================================
void CLife::Update(void)
{
	//ライフのカラー処理
	for (int nCount = 0; nCount < MAX_LIFE; nCount++)
	{
		//現在のライフ数値以外のゲージを消す
		if (nCount>=nLife)
		{
			m_LifeUi[nCount]->SetCol(D3DXCOLOR(0.0f,0.0f,0.0f,0.0f));
		}
		else
		{
			m_LifeUi[nCount]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		}
	}
}

//=============================================================================
//描画処理
//=============================================================================
void CLife::Draw(void)
{

}

//=============================================================================
// ライフセッター
//=============================================================================
void CLife::SetLife(int nLifeNumber)
{
	nLife = nLifeNumber;
}

//=============================================================================
// 位置セッター
//=============================================================================
void CLife::SetPos(D3DXVECTOR3 Lifepos)
{
	pos = Lifepos;
}

//=============================================================================
// ライフダウン処理
//=============================================================================
void CLife::DownLife(int nLifeDown)
{
	nLife -= nLifeDown;
}
