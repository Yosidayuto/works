//====================================================
//
// titletransition_tileクラスの処理[titletransition_tile.cpp]
// Author:伊藤陽梧
//
//====================================================

//====================================================
// インクルード
//====================================================
#include "titletransition_tile.h"
#include "scene3d.h"
#include "resource_texture.h"
#include "tutorial.h"
#include "collision.h"
#include "player.h"
#include "chara_select.h"
#include "fade.h"

//====================================================
// マクロ定義
//====================================================
#define TILE_COLOR	(D3DXCOLOR(0.1f, 0.1f, 0.6f, 1.0f))

//====================================================
// コンストラクタ
//====================================================
CTitleTransitionTile::CTitleTransitionTile()
{
	m_nPlayerCount = 0;
}

//====================================================
// デストラクタ
//====================================================
CTitleTransitionTile::~CTitleTransitionTile()
{
}

//====================================================
// クラス生成
//====================================================
void CTitleTransitionTile::Create(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	// メモリの確保
	CTitleTransitionTile *pTile;
	pTile = new CTitleTransitionTile;

	// 初期化
	pTile->Init();

	// 各値の代入・セット
	pTile->SetPos(pos);
	pTile->SetPriority(OBJTYPE_TILE); // オブジェクトタイプ
	pTile->SetRide(true);			  // 載れないようにフラグを立てる

	// ×マークの生成
	//pTile->m_pCrossPolygon = CScene3d::Create(D3DXVECTOR3(pos.x, pos.y + (TILE_SIZE_Y / 2) + 1.0f, pos.z), D3DXVECTOR3(TILE_ONE_SIDE - 2, 0.0f, TILE_ONE_SIDE - 2));
	//pTile->m_pCrossPolygon->SetColor(col);
	//pTile->m_pCrossPolygon->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_CROSS_MARK));
	//pTile->m_pCrossPolygon->SetPriority(OBJTYPE_MAP);
}

//====================================================
// 初期化処理
//====================================================
HRESULT CTitleTransitionTile::Init(void)
{
	// タイルの初期化
	if (FAILED(CTile::Init()))
	{
		return E_FAIL;
	}

	// タイルの色のセット
	SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

	return S_OK;
}

//====================================================
// 終了処理
//====================================================
void CTitleTransitionTile::Uninit(void)
{
	// タイルの終了
	CTile::Uninit();
}

//====================================================
// 更新処理
//====================================================
void CTitleTransitionTile::Update(void)
{
	// タイルの更新
	CTile::Update();

	CTutorial * pTutorial = CManager::GetTutorial();
	if (pTutorial &&
		pTutorial->GetTutorialPhase() == CTutorial::PHASE_FINISH)
	{

		// タイルの色のセット
		SetColor(TILE_COLOR);

		// このタイルの当たり判定
		CPlayer * pPlayer = (CPlayer*)GetTop(OBJTYPE_PLAYER);
		while (pPlayer != NULL)
		{
			// このタイルに載ったら
			if (CCollision::CollisionSphere(GetCollision(), pPlayer->GetCollision()))
			{
				CManager::GetFade()->SetFade(CManager::MODE_TITLE);
			}
			pPlayer = (CPlayer*)pPlayer->GetNext();
		}

		// チュートリアル中だったら
		CTutorial * pTutrial = CManager::GetTutorial();
		if (pTutrial)
		{
			// フェーズがすべて終了したとき
			if (pTutrial->GetTutorialPhase() == CTutorial::PHASE_FINISH)
			{
				// 載れるようにする
				SetRide(false);
			}
		}
	}
}