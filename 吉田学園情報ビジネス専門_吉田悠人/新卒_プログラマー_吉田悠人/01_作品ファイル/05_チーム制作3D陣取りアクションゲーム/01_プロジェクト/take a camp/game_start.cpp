//=============================================================================
//
// ゲーム開始の処理 [game_start.cpp]
// Author : 佐藤颯紀
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "game_start.h"
#include "polygon.h"
#include "resource_texture.h"
#include "player.h"
#include "time.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define SIZE_X		(360.0f)
#define SIZE_Y		(180.0f)
#define COUNT		(60)
//=============================================================================
// コンストラクタ
//=============================================================================
CGameStart::CGameStart() :CScene2d(OBJTYPE_UI_2)
{
	m_pos = VEC3_ZERO;							// 位置情報
	m_size = VEC3_ZERO;
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	// 色情報
	m_nCount = 0;								// カウンター
	m_type = START_TYPE_READEY;					// タイプ
	m_bStart = false;							// スタート使用してるかしてないか
}

//=============================================================================
// デストラクタ
//=============================================================================
CGameStart::~CGameStart()
{

}

//=============================================================================
// 生成処理
//=============================================================================
CGameStart * CGameStart::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CGameStart *pStart = NULL;

	// メモリの確保
	pStart = new CGameStart;

	// NULLチェック
	if (pStart != NULL)
	{
		// 初期化処理呼び出し
		pStart->Init();
		// 位置設定
		pStart->SetPos(pos);
		// サイズ設定
		pStart->SetSize(size);

		pStart->SetColor(pStart->m_col);

		// readyなら
		if (pStart->m_type == START_TYPE_READEY)
		{
			pStart->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_READEY));
		}
		// オブジェクトタイプ
		pStart->SetPriority(OBJTYPE_UI_2);
	}

	return pStart;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CGameStart::Init(void)
{
	// 初期化処理
	CScene2d::Init();

	// 色設定
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CGameStart::Uninit(void)
{
	// 終了処理
	CScene2d::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CGameStart::Update(void)
{
	// 更新処理
	CScene2d::Update();

	// サイズ情報の取得
	D3DXVECTOR3 size = GetSize();
	D3DXCOLOR col = GetColor();

	// readyの間の動き
	if (m_type == START_TYPE_READEY)
	{
		size.x += -10.0f;
		size.y += 0.25f * -10.0f;

		col.a += -0.01f;
	}

	// goのサイズを
	if (m_type == START_TYPE_GO)
	{
		// サイズ変更
		size.x = 360.0f;
		size.y = 180.0f;

		col.a = 1.0f;
	}

	// goを動かす
	if (m_type == START_TYPE_PLAY)
	{
		// サイズの大きさを毎フレームごとに変える
		size.x += 30.0f;
		size.y += 0.5f * 30.0f;

		col.a += -0.05f;
	}

	// 毎フレームごとにカウントを増やしていく
	m_nCount++;

	switch (m_type)
	{
	case START_TYPE_READEY:
		// readyなら
		GoChange();
		break;
	case START_TYPE_GO:
		// GOなら
		PlayChange();
		break;

	case START_TYPE_PLAY:
		//col.a = 1.0f;
		// プレイ状態にはいったら
		if (m_nCount == 15)
		{
			Uninit();
			return;
		}
		break;
	default:
		break;
	}

	// サイズ設定
	SetSize(size);

	// カラー設定
	SetColor(col);
}

//=============================================================================
// 描画処理
//=============================================================================
void CGameStart::Draw(void)
{
	// 描画処理
	CScene2d::Draw();
}

//=============================================================================
// 画像や大きさ変更処理
//=============================================================================
void CGameStart::GoChange(void)
{
	// サイズ情報の取得
	D3DXVECTOR3 size = GetSize();

	// カウントが一定値になったら
	if (size.x <= 0)
	{
		// goへ
		m_type = START_TYPE_GO;

		// テクスチャー変更
		BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_GO));

		// タイムを使用状態にする
		CTime::Create();

		// カウントの初期化
		m_nCount = 0;
	}

	// サイズ設定
	SetSize(size);
}

//=============================================================================
// プレイモードに状態変更
//=============================================================================
void CGameStart::PlayChange(void)
{
	// サイズ情報の取得
	D3DXVECTOR3 size = GetSize();
	D3DXCOLOR col = GetColor();

	// カウントが一定値になったら
	if (m_nCount == 5)
	{
		// プレイヤーの状態を通常状態に
		StartPlayer();

		// プレイタイプへ
		m_type = START_TYPE_PLAY;

		m_nCount = 0;
	}

	// サイズ設定
	SetSize(size);
	// カラー設定
	SetColor(col);
}

//=============================================================================
// プレイヤーを動けるようにする
//=============================================================================
void CGameStart::StartPlayer(void)
{
	CPlayer*pPlayer = (CPlayer*)GetTop(OBJTYPE_PLAYER);

	while (pPlayer != NULL)
	{
		pPlayer->SetUpdateFlag(true);

		pPlayer = (CPlayer*)pPlayer->GetNext();
	}
}
