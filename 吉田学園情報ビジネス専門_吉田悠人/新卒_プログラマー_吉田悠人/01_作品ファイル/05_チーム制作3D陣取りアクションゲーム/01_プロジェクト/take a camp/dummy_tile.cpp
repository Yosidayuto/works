//====================================================
//
// dummy_tileクラスの処理[dummy_tile.cpp]
// Author:伊藤陽梧
//
//====================================================

//====================================================
// インクルード
//====================================================
#include "dummy_tile.h"
#include "scene3d.h"
#include "resource_texture.h"

//====================================================
// コンストラクタ
//====================================================
CDummyTile::CDummyTile()
{
	m_pCrossPolygon = NULL;
}

//====================================================
// デストラクタ
//====================================================
CDummyTile::~CDummyTile()
{
}

//====================================================
// クラス生成
//====================================================
void CDummyTile::Create(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	// メモリの確保
	CDummyTile *pDummyTile;
	pDummyTile = new CDummyTile;

	// 初期化
	pDummyTile->Init();

	// 各値の代入・セット
	pDummyTile->SetPos(pos);
	pDummyTile->SetPriority(OBJTYPE_TILE); // オブジェクトタイプ
	pDummyTile->SetRide(true);			  // 載れないようにフラグを立てる

	// ×マークの生成
	pDummyTile->m_pCrossPolygon = CScene3d::Create(D3DXVECTOR3(pos.x, pos.y + (TILE_SIZE_Y / 2) + 1.0f, pos.z), D3DXVECTOR3(TILE_ONE_SIDE - 2, 0.0f, TILE_ONE_SIDE - 2));
	pDummyTile->m_pCrossPolygon->SetColor(col);
	pDummyTile->m_pCrossPolygon->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_CROSS_MARK));
	pDummyTile->m_pCrossPolygon->SetPriority(OBJTYPE_MAP);
}

//====================================================
// 初期化処理
//====================================================
HRESULT CDummyTile::Init(void)
{
	// タイルの初期化
	if (FAILED(CTile::Init()))
	{
		return E_FAIL;
	}

	// タイルの色のセット
	SetColor(TILE_DEFAULT_COLOR);

	return S_OK;
}

//====================================================
// 終了処理
//====================================================
void CDummyTile::Uninit(void)
{
	// タイルの終了
	CTile::Uninit();
}