//=============================================================================
//
// ボスタイプ1処理 [boss type1.cpp]
// Author : 吉田悠人
//
//=============================================================================
//=============================================================================
// インクルードファイル
//=============================================================================
#include "boss type1.h"
#include "manager.h"
#include "renderer.h"
#include "boss effect base.h"
#include "boss effect1.h"
#include "delete effect1.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define BOSS_TYPE1_SIZE		(500.0f)	// サイズ
#define BOSS_TYPE1_LIFE		(125)		// ライフ
#define BOSS_TYPE1_SCORE	(10000)		// スコア
#define BOSS_TYPE1_COOLTIME	(400)		// 攻撃のクールタイム
//=============================================================================
// 静的メンバー変数
//=============================================================================
TEXTURE_DATA CBossType1::m_TextureData = { NULL,"data/TEXTURE/Boss_1.png", };
//=============================================================================
// コンストラクト
//=============================================================================
CBossType1::CBossType1(int nPriorit)
{
	m_Effect = NULL;
}

//=============================================================================
// テクスチャロード処理
//=============================================================================
HRESULT CBossType1::Load(void)
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
void CBossType1::Unload(void)
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
CBossType1 * CBossType1::Create(D3DXVECTOR3 pos)
{
	//メモリ確保
	CBossType1* pBossType1 = NULL;
	pBossType1 = new CBossType1;

	//NULLチェック
	if (pBossType1 != NULL)
	{
		//位置設定
		pBossType1->SetPos(pos);
		//サイズ設定
		pBossType1->SetSize(D3DXVECTOR3(BOSS_TYPE1_SIZE / 2.0f, BOSS_TYPE1_SIZE / 2.0f, 0.0f));
		//ライフ設定
		pBossType1->SetLife(BOSS_TYPE1_LIFE);
		//スコア設定
		pBossType1->SetScore(BOSS_TYPE1_SCORE);
		//攻撃のクールタイム設定
		pBossType1->SetCoolTime(BOSS_TYPE1_COOLTIME);
		//テクスチャセット
		pBossType1->BindTexture(m_TextureData.m_Texture);
		//初期化処理
		pBossType1->Init();
	}
	return pBossType1;
}

//=============================================================================
// 更新処理
//=============================================================================
void CBossType1::Update(void)
{
	//攻撃処理
	Bullet();
	CBossBase::Update();
}

//=============================================================================
// エフェクト生成
//=============================================================================
void CBossType1::Effect(void)
{
	//位置取得
	D3DXVECTOR3 pos = GetPos();
	//サイズ取得
	D3DXVECTOR3 size = GetSize();

	//エフェクト生成
	m_Effect = CBossEffectType1::Create(pos, size);
}

//=============================================================================
// 描画処理
//=============================================================================
void CBossType1::DisEffect(void)
{
	//位置取得
	D3DXVECTOR3 pos = GetPos();
	//サイズ取得
	D3DXVECTOR3 size = GetSize();

	//エフェクト終了処理
	if (m_Effect!=NULL)
	{
		m_Effect->Uninit();
	}

	//やられたときのエフェクト生成
	CDeleteEffect1::Create(pos, size);
}
