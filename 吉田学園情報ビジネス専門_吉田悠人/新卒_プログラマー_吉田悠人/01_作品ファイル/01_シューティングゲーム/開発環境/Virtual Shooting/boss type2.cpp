//=============================================================================
//
// ボスタイプ2処理 [boss type2.cpp]
// Author : 吉田悠人
//
//=============================================================================
//=============================================================================
//インクルードファイル
//=============================================================================
#include "boss type2.h"
#include "manager.h"
#include "game.h"
#include "renderer.h"
#include "boss effect2.h"
#include "delete effect2.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define BOSS_TYPE2_SIZE		(500.0f)	//サイズ
#define BOSS_TYPE2_LIFE		(200)		//ライフ
#define BOSS_TYPE2_SCORE	(10000)		//スコア
#define BOSS_TYPE2_COOLTIME	(350)		//攻撃のクールタイム
//=============================================================================
// 静的メンバー変数
//=============================================================================
TEXTURE_DATA CBossType2::m_TextureData = { NULL,"data/TEXTURE/Boss_2.png", };
//=============================================================================
// コンストラクト
//=============================================================================
CBossType2::CBossType2()
{
}

//=============================================================================
// テクスチャロード処理
//=============================================================================
HRESULT CBossType2::Load(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, m_TextureData.m_cFileName, &m_TextureData.m_Texture);
	return S_OK;
}

//=============================================================================
// テクスチャ破棄処理
//=============================================================================
void CBossType2::Unload(void)
{
	//テクスチャの破棄
	if (m_TextureData.m_Texture != NULL)
	{
		m_TextureData.m_Texture->Release();
		m_TextureData.m_Texture = NULL;
	}
}

//=============================================================================
// 生成処理
//=============================================================================
CBossType2 * CBossType2::Create(D3DXVECTOR3 pos)
{
	//メモリ確保
	CBossType2* pBossType2 = NULL;
	pBossType2 = new CBossType2;
	
	//NULLチェック
	if (pBossType2 != NULL)
	{
		//位置設定
		pBossType2->SetPos(pos);
		//サイズ設定
		pBossType2->SetSize(D3DXVECTOR3(BOSS_TYPE2_SIZE / 2.0f, BOSS_TYPE2_SIZE / 2.0f, 0.0f));
		//ライフ設定
		pBossType2->SetLife(BOSS_TYPE2_LIFE);
		//スコア設定
		pBossType2->SetScore(BOSS_TYPE2_SCORE);
		//攻撃のクールタイム設定
		pBossType2->SetCoolTime(BOSS_TYPE2_COOLTIME);
		//テクスチャセット
		pBossType2->BindTexture(m_TextureData.m_Texture);
		//初期化処理
		pBossType2->Init();

	}
	return pBossType2;
}


//=============================================================================
// 更新処理
//=============================================================================
void CBossType2::Update(void)
{
	//攻撃処理
	Bullet();
	CBossBase::Update();
}

//=============================================================================
// エフェクト生成
//=============================================================================
void CBossType2::Effect(void)
{
	//位置取得
	D3DXVECTOR3 pos = GetPos();
	//サイズ取得
	D3DXVECTOR3 size = GetSize();

	//エフェクト生成
	m_Effect = CBossEffectType2::Create(pos, size);
}

//=============================================================================
// 描画処理
//=============================================================================
void CBossType2::DisEffect(void)
{
	//位置取得
	D3DXVECTOR3 pos = GetPos();
	//サイズ取得
	D3DXVECTOR3 size = GetSize();
	
	//エフェクト終了処理
	if (m_Effect != NULL)
	{
		m_Effect->Uninit();
	}

	//やられたときのエフェクト生成
	CDeleteEffect2::Create(D3DXVECTOR3(pos.x, SCREEN_HEIGHT / 2,0.0f), D3DXVECTOR3(STAGE_SIZE, SCREEN_HEIGHT,0.0f));
}
