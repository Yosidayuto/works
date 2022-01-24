//=============================================================================
//
// 制限時間通知の処理 [gameend ui.cpp]
// Author : 林川紗梨夏
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "gameend ui.h"
#include "resource manager.h"

//*****************************************************************************
// 静的メンバ変数初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CGameEndUi::CGameEndUi(int nPriority) : CScene2d(nPriority)
{
	m_nPatternAnim = 1;
	m_nCountAnim = 0;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// デストラクタ
//=============================================================================
CGameEndUi::~CGameEndUi()
{

}

//=============================================================================
// 生成処理
//=============================================================================
CGameEndUi * CGameEndUi::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size)
{
	CGameEndUi *pMap = nullptr;

	pMap = new CGameEndUi;
	if (pMap != nullptr)
	{
		//リソース確保(リソースマネージャーから呼び出す)
		CResource* pResource = CManager::GetResource();
		LPDIRECT3DTEXTURE9 Texture = pResource->TextureLoad(pMap->m_nTexture);
		pMap->BindTexture(Texture);
		pMap->SetPos(Pos);
		pMap->SetSize(Size);
		pMap->Init();
	}
	return pMap;
}

CGameEndUi * CGameEndUi::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Move, D3DXVECTOR3 Size)
{
	CGameEndUi *pMap = nullptr;

	pMap = new CGameEndUi;
	if (pMap != nullptr)
	{
		//リソース確保(リソースマネージャーから呼び出す)
		CResource* pResource = CManager::GetResource();
		LPDIRECT3DTEXTURE9 Texture = pResource->TextureLoad(59);
		pMap->BindTexture(Texture);
		pMap->SetPos(Pos);
		pMap->SetSize(Size);
		pMap->m_move = Move;
		pMap->Init();
	}
	return pMap;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CGameEndUi::Init(void)
{
	SetObjType(CScene::OBJTYPE_NONE);

	CScene2d::Init();

	//テクスチャセット
	D3DXVECTOR2 Tex[NUM_VERTEX];
	Tex[0] = D3DXVECTOR2(0.0f, 0.0f);
	Tex[1] = D3DXVECTOR2(1.0f, 0.0f);
	Tex[2] = D3DXVECTOR2(0.0f, 1.0f);
	Tex[3] = D3DXVECTOR2(1.0f, 1.0f);
	SetTexture(Tex);

	//頂点カラーセット
	SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CGameEndUi::Uninit(void)
{
	CScene2d::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CGameEndUi::Update(void)
{
	CScene2d::Update();

	//テクスチャセット
	D3DXVECTOR2 Tex[NUM_VERTEX];
	Tex[0] = D3DXVECTOR2(0.0f, 0.0f);
	Tex[1] = D3DXVECTOR2(1.0f, 0.0f);
	Tex[2] = D3DXVECTOR2(0.0f, 1.0f);
	Tex[3] = D3DXVECTOR2(1.0f, 1.0f);
	SetTexture(Tex);

	//頂点カラーセット
	SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));
	//位置更新
	SetPos(GetPos() + m_move);

	if (GetPos().y >= SCREEN_CENTER_Y)
	{
		m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CGameEndUi::Draw(void)
{
	CScene2d::Draw();
}
