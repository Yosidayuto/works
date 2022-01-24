////////////////////////////////////////////////////
//
//    前後に動くタイルの処理[move_around_tile.cpp]
//    Author:吉田 悠人
//
////////////////////////////////////////////////////

//******************************
// インクルード
//******************************
#include "move_around_tile.h"
#include "scene3d.h"
#include "resource_texture.h"

//******************************
// コンストラクタ
//******************************
CAroundTile::CAroundTile()
{
	m_Texture = nullptr;
}

//******************************
// デストラクタ
//******************************
CAroundTile::~CAroundTile()
{
}

//******************************
// クラス生成
//******************************
void CAroundTile::Create(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	// メモリの確保
	CAroundTile *pTile;
	pTile = new CAroundTile;

	//NULLチェック
	if (pTile != NULL)
	{
		// 初期化
		pTile->Init();

		// 各値の代入・セット
		pTile->SetPos(pos);					// 位置
		pTile->SetMove(pos);				// 移動量
		pTile->SetPriority(OBJTYPE_TILE); 	// オブジェクトタイプ
	}
}

//******************************
// 初期化処理
//******************************
HRESULT CAroundTile::Init(void)
{
	//初期化処理
	CMoveTile::Init();

	//テクスチャ用ポリゴン
	m_Texture = CScene3d::Create(GetPos(), D3DXVECTOR3(TILE_ONE_SIDE - 2, 0.0f, TILE_ONE_SIDE - 2));
	m_Texture->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_MOVE_TILE));
	D3DXVECTOR2 uv[NUM_VERTEX];
	uv[0] = D3DXVECTOR2(0,1);
	uv[1] = D3DXVECTOR2(0,0);
	uv[2] = D3DXVECTOR2(1,1);
	uv[3] = D3DXVECTOR2(1,0);
	m_Texture->SetTextureUV(uv);
	m_Texture->SetColor(TILE_DEFAULT_COLOR);
	m_Texture->SetPriority(OBJTYPE_MAP);

	return S_OK;
}

//******************************
// 更新処理
//******************************
void CAroundTile::Update(void)
{
	//移動床の処理
	CMoveTile::Update();

	//テクスチャの位置
	D3DXVECTOR3 effectPos = D3DXVECTOR3(GetPos().x, GetPos().y + (TILE_SIZE_Y / 2) + 0.1f, GetPos().z);
	m_Texture->SetPos(effectPos);
}

//******************************
// 移動方向処理
//******************************
void CAroundTile::MoveRot(bool bReversal)
{
	//現在位置
	D3DXVECTOR3 pos = GetPos();
	//移動量
	D3DXVECTOR3 move = GetMove();

	//反転しているか
	if (!bReversal)
	{
		//移動量計算
		move.z += TILE_ONE_SIDE;
	}
	else
	{
		move.z -= TILE_ONE_SIDE;
	}

	//移動量セット
	SetMove(move);
}

//******************************
// 周囲のブロック確認処理
//******************************
void CAroundTile::TileCheck(void)
{
	//現在位置
	D3DXVECTOR3 pos = GetPos();

	if (CTile::GetHitTile(D3DXVECTOR3(pos.x , pos.y, pos.z - TILE_ONE_SIDE)) != nullptr)
	{
		//移動方向反転
		SetReversal(false);
	}
	else
	{
		//移動方向反転
		SetReversal(true);
	}
}
