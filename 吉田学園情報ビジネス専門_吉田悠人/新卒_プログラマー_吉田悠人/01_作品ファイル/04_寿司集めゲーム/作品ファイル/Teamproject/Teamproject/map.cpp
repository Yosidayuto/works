//=============================================================================
//
// ミニマップの処理 [map.cpp]
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
#include "map.h"
#include "resource manager.h"

//*****************************************************************************
// 静的メンバ変数初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CMap::CMap(int nPriority) : CScene2d(nPriority)
{
	m_nPatternAnim = 1;
	m_nCountAnim = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CMap::~CMap()
{

}

//=============================================================================
// 生成処理
//=============================================================================
CMap * CMap::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size)
{
	CMap *pMap = nullptr;

	pMap = new CMap;
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

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CMap::Init(void)
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
void CMap::Uninit(void)
{
	CScene2d::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CMap::Update(void)
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
}

//=============================================================================
// 描画処理
//=============================================================================
void CMap::Draw(void)
{
	CScene2d::Draw();
}
