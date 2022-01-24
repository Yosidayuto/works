//=============================================================================
//
// キラキラ✧エフェクト [glitter_effect.cpp]
// Author : 吉田 悠人
//
//=============================================================================

//*****************************
// インクルード
//*****************************
#include "glitter_effect.h"
#include "resource_texture.h"

//*****************************
//マクロ定義
//*****************************
#define MAX_SIZE	(D3DXVECTOR3(20.0f,20.0f,0.0f))	// 最大サイズ
#define MIN_SIZE	(D3DXVECTOR3(0.0f,0.0f,0.0f))	// 最小サイズ

//******************************
// コンストラクタ
//******************************
CGlitter::CGlitter()
{
	m_fLife = 0.0f;
	m_bDeath = false;
	m_fMidpoint = 0.0f;
	m_nSizeFps = 0;
}

//******************************
// デストラクタ
//******************************
CGlitter::~CGlitter()
{
}

//******************************
// 生成処理
//******************************
void CGlitter::Create(D3DXVECTOR3 pos,int nLife, D3DXCOLOR col)
{
	//メモリ確保
	CGlitter* pGlitter = nullptr;
	pGlitter = new CGlitter;

	//NULLチェック
	if (pGlitter != nullptr)
	{
		//初期化処理
		pGlitter->Init();
		
		//位置設定
		pGlitter->SetPos(pos);
		//ライフ設定
		pGlitter->m_fLife = (float)nLife;
		pGlitter->m_fMidpoint = (float)nLife / 2.0f;
		//カラー設定
		pGlitter->SetColor(col);
	}
}

//******************************
// 初期化処理
//******************************
HRESULT CGlitter::Init(void)
{
	//ビルボード初期化処理
	CBillboard::Init();
	//テクスチャ設定
	BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_PARTICLE_GLITTER));
	return S_OK;
}

//******************************
// 終了処理
//******************************
void CGlitter::Update(void)
{
	//ライフダウン処理
	LifeDown();

	//大きさの処理
	SizeChange();

	//死亡フラグが立っているとき
	if (m_bDeath)
	{
		//終了処理
		Uninit();
	}
}

//*****************************
//　大きさ設定処理関数
//*****************************
void CGlitter::SizeChange(void)
{
	//大きさ取得
	D3DXVECTOR3 size = GetSize();

	m_nSizeFps++;
	
	if (m_fLife>m_fMidpoint)
	{
		size += (MAX_SIZE - size) / ((m_fMidpoint) - (float)m_nSizeFps);
	}
	else 
	{
		size += (MIN_SIZE - size) / ((m_fMidpoint) - (float)m_nSizeFps);
	}
	SetSize(size);
}

//*****************************
//　ライフダウン処理関数
// 一秒に1ライフを引く
//*****************************
void CGlitter::LifeDown(void)
{
	//ライフを減らす
	m_fLife--;

	//ライフが半分になったら
	if (m_fLife <= m_fMidpoint + 1.0f
		&&m_fLife >= m_fMidpoint - 1.0f)
	{
		m_nSizeFps = 0;
	}

	//ライフが0以下になったら
	if (m_fLife <= 0.0f)
	{
		//死亡フラグを立てる
		m_bDeath = true;
	}
}
